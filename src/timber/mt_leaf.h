/* 
#Copyright (c) 2021 Sevenli. All rights reserved.
*/
#include <pthread.h>
#include <unistd.h>

#include "mt_type.h"

#ifndef __MT_LEAF_H__
#define __MT_LEAF_H__

// https://blog.csdn.net/u014755412/article/details/79334572

namespace timber
{

    /**
     * @description: 叶子
     * @param {*}
     * @return {*}
     */
    typedef struct Leaf
    {
    private:
        int _ver;

    public:
        LogPriority p;
        std::string tag;  // 标记
        std::string ts;   // 时间戳
        std::string file; // 文件名
        std::string func; // 函数名
        std::string line; // 文件行数

#ifndef __MT_TIMBER_PID__
        std::string pid; // 进程ID
#endif                   // __MT_TIMBER_PID__

        std::string tid; // 线程ID

        Leaf(){};
        Leaf(LogPriority p)
        {
            this->p = p;

            this->ts = getCurTime();
            this->tid = getThreadID();
#ifdef __MT_TIMBER_PID__
            this->pid = getProcessID();
#endif // __MT_TIMBER_PID__
        };
        Leaf(LogPriority p, const std::string &tag, const std::string &file,
             const std::string &func, const std::string &line)
        {
            this->p = p;
            this->tag = tag;
            this->file = file;
            this->func = func;
            this->line = line;

            this->ts = getCurTime();
            this->tid = getThreadID();
#ifdef __MT_TIMBER_PID__
            this->pid = getProcessID();
#endif // __MT_TIMBER_PID__
        };
        ~Leaf(){};

        const std::string toString()
        {
            std::stringstream ss;
            ss << "Leaf(";
            ss << "tag=" << this->tag << ",ts=" << this->ts << ",file=" << this->file
               << ",func=" << this->func << ",line=" << this->line
               << ",tid=" << this->tid;
            ss << ")";

            return ss.str();
        }

        // [timestamp]               [threadid]   [priority] [tag]   [file:line]
        // [func] [msg]
        const std::string toLoggingPrefix()
        {
            std::stringstream ss;
            if (this->ts.length() > 0)
                ss << this->ts << " ";
            if (this->pid.length() > 0)
                ss << "[" << this->pid << "] ";
            if (this->tid.length() > 0)
                ss << "[" << this->tid << "] ";
            ss << "[" << this->getPriority() << "] ";
            if (this->tag.length() > 0)
                ss << "[" << this->tag << "] ";
            if (this->file.length() > 0)
                ss << "[" << this->file << ":" << this->line << "] ";
            if (this->func.length() > 0)
                ss << "[" << this->func << "] ";

            return ss.str();
        }

    private:
        std::string getCurTime()
        {
            time_t now = time(0);
            struct tm tstruct;
            char buf[80];
            tstruct = *localtime(&now);
            strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

            return buf;
        }

        std::string getProcessID()
        {
            static __thread int __pid = 0;

            if (__pid == 0)
            {
                __pid = getpid();
            }
            return std::to_string(__pid);
        }

        std::string getThreadID()
        {
            // int id = syscall(SYS_thread_selfid);
            // return std::to_string(id);

            // Windows : GetCurrentThreadId()

            // Linux :
            // #include <unistd.h>       // for syscall()
            // #include <sys/syscall.h>  // for SYS_xxx definitions
            // int id = syscall(SYS_gettid);

            // Mac :
            // #include <unistd.h>       // for syscall()
            // #include <sys/syscall.h>  // for SYS_xxx definitions
            // int id = syscall(SYS_thread_selfid); // for mac os x

            static __thread pid_t __tid = 0;

            if (__tid == 0)
            {
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_12
                uint64_t tid64;
                pthread_threadid_np(NULL, &tid64);
                __tid = (pid_t)tid64;
#else
                __tid = syscall(SYS_gettid);
#endif
            }

            return std::to_string(__tid);
        }

        const std::string getPriority()
        {
            std::string priorityDesc;
            switch (this->p)
            {
            case LogPriorityDebug:
                priorityDesc = "D";
                break;

            case LogPriorityInfo:
                priorityDesc = "I";
                break;

            case LogPriorityWarn:
                priorityDesc = "W";
                break;

            case LogPriorityError:
                priorityDesc = "E";
                break;

            default:
                priorityDesc = "S";
                break;
            }

            return priorityDesc;
        }
    } Leaf;

    typedef std::shared_ptr<Leaf> LeafPtr;

    inline LogPriority LogPriorityFromShort(const char *ps)
    {
        const std::string pss = ps;
        LogPriority p = LogPriorityDebug;

        if (pss == "d")
        {
            p = LogPriorityDebug;
        }
        else if (pss == "i")
        {
            p = LogPriorityInfo;
        }
        else if (pss == "w")
        {
            p = LogPriorityWarn;
        }
        else if (pss == "e")
        {
            p = LogPriorityError;
        }

        return p;
    }
    inline const std::string fileNameFromPath(const char *cpath)
    {
        std::string path = cpath;
        int pos = path.find_last_of('/');
        if (pos >= 0)
        {
            std::string s(path.substr(pos + 1));
            return s;
        }
        else
        {
            return cpath;
        }
    }
    inline LeafPtr create_leaf(LogPriority p, const std::string &tag,
                               const std::string &file, const std::string &func,
                               const std::string &line)
    {
        return std::make_shared<Leaf>(p, tag, file, func, line);
    };
    inline LeafPtr create_leaf(LogPriority p) { return std::make_shared<Leaf>(p); };
    inline LeafPtr create_leaf() { return std::make_shared<Leaf>(); };

    // /**
    //  * @description: 一片叶子
    //  * @param {*}
    //  * @return {*}
    //  */
    // inline LeafPtr make_leaf(const std::string &tag, const std::string &file,
    // const std::string &func, const std::string &line) {
    //     LeafPtr leaf = create_leaf(tag, file, func, file);

    //     return leaf;
    // };
} // namespace timber

#endif // __MT_LEAF_H__