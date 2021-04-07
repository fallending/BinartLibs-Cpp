/* #Copyright (c) 2021 Sevenli. All rights reserved. */
#include <pthread.h>
#include <unistd.h>

#include "mt_type.h"

#ifndef MT_LEAF_H_
#define MT_LEAF_H_

// https://blog.csdn.net/u014755412/article/details/79334572

namespace timber
{
/**
 * @description: 叶子
 * @param {*}
 * @return {*}
 */
struct Leaf
{
    LogPriority p{LogPriorityDebug};
    std::string tag;   // 标记
    std::string ts;    // 时间戳
    std::string file;  // 文件名
    std::string func;  // 函数名
    std::string line;  // 文件行数

#ifndef __MT_TIMBER_PID__
    std::string pid;  // 进程ID
#endif                // __MT_TIMBER_PID__

    std::string tid;  // 线程ID

    Leaf() = default;
    explicit Leaf(LogPriority p)
    {
        this->p = p;

        ts  = GetCurTime();
        tid = GetThreadID();
#ifdef __MT_TIMBER_PID__
        pid = getProcessID();
#endif  // __MT_TIMBER_PID__
    };
    Leaf(LogPriority        p,
         const std::string &tag,
         const std::string &file,
         const std::string &func,
         const std::string &line)
    {
        this->p    = p;
        this->tag  = tag;
        this->file = file;
        this->func = func;
        this->line = line;

        ts  = GetCurTime();
        tid = GetThreadID();
#ifdef __MT_TIMBER_PID__
        pid = getProcessID();
#endif  // __MT_TIMBER_PID__
    };
    ~Leaf() = default;

    std::string ToString() const
    {
        std::stringstream ss;
        ss << "Leaf(";
        ss << "tag=" << tag << ",ts=" << ts << ",file=" << file
           << ",func=" << func << ",line=" << line << ",tid=" << tid;
        ss << ")";

        return ss.str();
    }

    // [timestamp]               [threadid]   [priority] [tag]   [file:line]
    // [func] [msg]
    std::string ToLoggingPrefix()
    {
        std::stringstream ss;
        if (ts.length() > 0)
        {
            ss << ts << " ";
        }

        if (pid.length() > 0)
        {
            ss << "[" << pid << "] ";
        }
        if (tid.length() > 0)
        {
            ss << "[" << tid << "] ";
        }
        ss << "[" << GetPriority() << "] ";
        if (tag.length() > 0)
        {
            ss << "[" << tag << "] ";
        }
        if (file.length() > 0)
        {
            ss << "[" << file << ":" << line << "] ";
        }
        if (func.length() > 0)
        {
            ss << "[" << func << "] ";
        }

        return ss.str();
    }

private:
    static std::string GetCurTime()
    {
        time_t    now     = time(nullptr);
        struct tm tstruct = *localtime(&now);
        char      buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

        return buf;
    }

    static std::string GetProcessID()
    {
        static __thread int pid = 0;

        if (pid == 0)
        {
            pid = getpid();
        }
        return std::to_string(pid);
    }

    static std::string GetThreadID()
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

        static __thread pid_t tid = 0;

        if (tid == 0)
        {
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_12
            uint64_t tid64;
            pthread_threadid_np(NULL, &tid64);
            tid = (pid_t)tid64;
#else
            tid = syscall(SYS_gettid);
#endif
        }

        return std::to_string(tid);
    }

    std::string GetPriority() const
    {
        std::string priority_desc;
        switch (p)
        {
            case LogPriorityDebug:
                priority_desc = "D";
                break;

            case LogPriorityInfo:
                priority_desc = "I";
                break;

            case LogPriorityWarn:
                priority_desc = "W";
                break;

            case LogPriorityError:
                priority_desc = "E";
                break;

            default:
                priority_desc = "S";
                break;
        }

        return priority_desc;
    }
};

using LeafPtr = std::shared_ptr<Leaf>;

inline LogPriority LogPriorityFromShort(const char *ps)
{
    const std::string pss = ps;
    LogPriority       p   = LogPriorityDebug;

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
inline std::string FileNameFromPath(const char *cpath)
{
    std::string path = cpath;
    int         pos  = path.find_last_of('/');
    if (pos >= 0)
    {
        std::string s(path.substr(pos + 1));
        return s;
    }

    return cpath;
}
inline LeafPtr CreateLeaf(LogPriority        p,
                          const std::string &tag,
                          const std::string &file,
                          const std::string &func,
                          const std::string &line)
{
    return std::make_shared<Leaf>(p, tag, file, func, line);
};
inline LeafPtr CreateLeaf(LogPriority p) { return std::make_shared<Leaf>(p); };
inline LeafPtr CreateLeaf() { return std::make_shared<Leaf>(); };

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
}  // namespace timber

#endif  // MT_LEAF_H_