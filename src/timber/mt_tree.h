/*
 * @Author: your name
 * @Date: 2021-03-22 18:22:11
 * @LastEditTime: 2021-03-26 17:13:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/timber/mt_tree.h
 */

#include "mt_type.h"
#include "mt_leaf.h"

#ifndef MT_TREE_H_
#define MT_TREE_H_

namespace timber
{
#define TIMBER_TREE_LOG_F(func, priority)                                    \
    void func(const LeafPtr &leaf, const std::string &message, va_list args) \
    {                                                                        \
        PrepareLog(leaf, message, args);                                     \
    };

class Tree
{
public:
    Tree(/* args */) = default;
    ~Tree()          = default;

    TIMBER_TREE_LOG_F(d, LogPriorityDebug)
    TIMBER_TREE_LOG_F(i, LogPriorityInfo)
    TIMBER_TREE_LOG_F(w, LogPriorityWarn)
    TIMBER_TREE_LOG_F(e, LogPriorityError)

    virtual bool IsLoggable(const std::string &tag, LogPriority priority)
    {
        return true;
    };

    virtual void Log(LogPriority        priority,
                     const std::string &tag,
                     const std::string &message) = 0;

private:
    void PrepareLog(const LeafPtr &    leaf,
                    const std::string &message,
                    va_list            args)
    {
        if (!IsLoggable(leaf.get()->tag, leaf.get()->p))
        {
            return;
        }

        if (message.length() == 0)
        {  // swallow emppty message
            return;
        }

        // TODO: getStackTraceString

        // if (args != null && args.length > 0) {
        //     message = formatMessage(message, args);
        //     }
        //     if (t != null) {
        //     message += "\n" + getStackTraceString(t);
        //     }
        Log(leaf.get()->p,
            leaf.get()->tag,
            FormatMessage(GetFormatString(message, args), leaf));
    }

    static std::string GetFormatString(const std::string &message, va_list args)
    {
        char buf[4096];
        memset(buf, 0, sizeof(buf));
        vsprintf(buf, message.c_str(), args);

        return buf;
    }

    /**
     * @description: 日志格式化
     * @param {const} std
     * @param {constLeaf} &leaf
     * @return {*}
     *
     * @example
     *  [timestamp]               [threadid]   [priority] [tag]   [file:line]
     * [func] [msg] [2016-09-11 15:05:30.510] [4246443808] [ERROR]    [login]
     * [/home/Github/dlog/example/LogTest.cpp:11]  [main]  Hello everyone
     */
    static std::string FormatMessage(const std::string &message,
                                     const LeafPtr &    leaf)
    {
        return leaf.get()->ToLoggingPrefix() + message;
    }
};

using TreePtr = std::shared_ptr<Tree>;

class DebugTree : public Tree
{
public:
    bool IsLoggable(const std::string &tag, LogPriority priority) override
    {
        return true;
    }

    void Log(LogPriority        priority,
             const std::string &tag,
             const std::string &message) override
    {
        switch (priority)
        {
            case LogPriorityDebug:
                std::cout << Green << message << Reset << std::endl;
                break;

            case LogPriorityInfo:
                std::cout << White << message << Reset << std::endl;
                break;

            case LogPriorityWarn:
                std::cout << Yellow << message << Reset << std::endl;
                break;

            case LogPriorityError:
                std::cout << Red << message << Reset << std::endl;
                break;

            default:
                break;
        }
    }
};
}  // namespace timber

#endif  // MT_TREE_H_