/*
 * @Author: your name
 * @Date: 2021-03-25 16:15:29
 * @LastEditTime: 2021-03-29 15:28:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/log/file_log.h
 */

#pragma once

#include <stdio.h>
#include <atomic>
#include <string>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include <utility>

#ifndef __MT_FILE_LOG_H__
#define __MT_FILE_LOG_H__

namespace mt
{
    namespace log
    {
        struct noncopyable {
        protected:
            noncopyable() = default;
            virtual ~noncopyable() = default;

            noncopyable(const noncopyable &) = delete;
            noncopyable &operator=(const noncopyable &) = delete;
        };

#ifdef OS_LINUX
        inline uint64_t gettid() { return syscall(SYS_gettid); };
#elif defined(OS_MACOSX)
        inline uint64_t gettid() {
            pthread_t tid = pthread_self();
            uint64_t uid = 0;
            memcpy(&uid, &tid, std::min(sizeof(tid), sizeof(uid)));
            return uid;
        }
#endif

        static thread_local uint64_t tid;
        
        struct Logger : private noncopyable {
            enum LogLevel { LFATAL = 0, LERROR, LUERR, LWARN, LINFO, LDEBUG, LTRACE, LALL };
            Logger()  : level_(LINFO), lastRotate_(time(NULL)), rotateInterval_(86400) {
                tzset();
                fd_ = -1;
                realRotate_ = lastRotate_;
            };
            ~Logger() {
                if (fd_ != -1) {
                    close(fd_);
                }
            };
            void logv(int level, const char *file, int line, const char *func, const char *fmt...) {
                if (tid == 0) {
                    tid = port::gettid();
                }
                if (level > level_) {
                    return;
                }
                maybeRotate();
                char buffer[4 * 1024];
                char *p = buffer;
                char *limit = buffer + sizeof(buffer);

                struct timeval now_tv;
                gettimeofday(&now_tv, NULL);
                const time_t seconds = now_tv.tv_sec;
                struct tm t;
                localtime_r(&seconds, &t);
                p += snprintf(p, limit - p, "%04d/%02d/%02d-%02d:%02d:%02d.%06d %lx %s %s:%d ", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
                            static_cast<int>(now_tv.tv_usec), (long) tid, levelStrs_[level], file, line);
                va_list args;
                va_start(args, fmt);
                p += vsnprintf(p, limit - p, fmt, args);
                va_end(args);
                p = std::min(p, limit - 2);
                // trim the ending \n
                while (*--p == '\n') {
                }
                *++p = '\n';
                *++p = '\0';
                int fd = fd_ == -1 ? 1 : fd_;
                int err = ::write(fd, buffer, p - buffer);
                if (err != p - buffer) {
                    fprintf(stderr, "write log file %s failed. written %d errmsg: %s\n", filename_.c_str(), err, strerror(errno));
                }
                if (level <= LERROR) {
                    syslog(LOG_ERR, "%s", buffer + 27);
                }
                if (level == LFATAL) {
                    fprintf(stderr, "%s", buffer);
                    assert(0);
                }
            }

            void setFileName(const std::string &filename) {
                int fd = open(filename.c_str(), O_APPEND | O_CREAT | O_WRONLY | O_CLOEXEC, DEFFILEMODE);
                if (fd < 0) {
                    fprintf(stderr, "open log file %s failed. msg: %s ignored\n", filename.c_str(), strerror(errno));
                    return;
                }
                filename_ = filename;
                if (fd_ == -1) {
                    fd_ = fd;
                } else {
                    int r = dup2(fd, fd_);
                    fatalif(r < 0, "dup2 failed");
                    close(fd);
                }
            }
            void setLogLevel(const std::string &level) {
                LogLevel ilevel = LINFO;
                for (size_t i = 0; i < sizeof(levelStrs_) / sizeof(const char *); i++) {
                    if (strcasecmp(levelStrs_[i], level.c_str()) == 0) {
                        ilevel = (LogLevel) i;
                        break;
                    }
                }
                setLogLevel(ilevel);
            }
            void setLogLevel(LogLevel level) { level_ = std::min(LALL, std::max(LFATAL, level)); }

            LogLevel getLogLevel() { return level_; }
            const char *getLogLevelStr() { return levelStrs_[level_]; }
            int getFd() { return fd_; }

            void adjustLogLevel(int adjust) { setLogLevel(LogLevel(level_ + adjust)); }
            void setRotateInterval(long rotateInterval) { rotateInterval_ = rotateInterval; }
            static Logger &getLogger() {
                static Logger logger;
                return logger;
            }

        private:
            void maybeRotate() {
                time_t now = time(NULL);
                if (filename_.empty() || (now - timezone) / rotateInterval_ == (lastRotate_ - timezone) / rotateInterval_) {
                    return;
                }
                lastRotate_ = now;
                long old = realRotate_.exchange(now);
                //如果realRotate的值是新的，那么返回，否则，获得了旧值，进行rotate
                if ((old - timezone) / rotateInterval_ == (lastRotate_ - timezone) / rotateInterval_) {
                    return;
                }
                struct tm ntm;
                localtime_r(&now, &ntm);
                char newname[4096];
                snprintf(newname, sizeof(newname), "%s.%d%02d%02d%02d%02d", filename_.c_str(), ntm.tm_year + 1900, ntm.tm_mon + 1, ntm.tm_mday, ntm.tm_hour, ntm.tm_min);
                const char *oldname = filename_.c_str();
                int err = rename(oldname, newname);
                if (err != 0) {
                    fprintf(stderr, "rename logfile %s -> %s failed msg: %s\n", oldname, newname, strerror(errno));
                    return;
                }
                int fd = open(filename_.c_str(), O_APPEND | O_CREAT | O_WRONLY | O_CLOEXEC, DEFFILEMODE);
                if (fd < 0) {
                    fprintf(stderr, "open log file %s failed. msg: %s ignored\n", newname, strerror(errno));
                    return;
                }
                dup2(fd, fd_);
                close(fd);
            }
            static const char *levelStrs_[LALL + 1] = {
                "FATAL", "ERROR", "UERR", "WARN", "INFO", "DEBUG", "TRACE", "ALL",
            };

            int fd_;
            LogLevel level_;
            long lastRotate_;
            std::atomic<int64_t> realRotate_;
            long rotateInterval_;
            std::string filename_;
        };

    } // namespace log
    
} // namespace mt

#endif // __MT_FILE_LOG_H__
