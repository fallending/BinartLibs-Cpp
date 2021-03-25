/*
 * @Author: your name
 * @Date: 2021-03-22 18:22:11
 * @LastEditTime: 2021-03-25 14:29:10
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/timber/mt_tree.h
 */

#include "mt_type.h"

#ifndef __MT_TREE_H__
#define __MT_TREE_H__

namespace timber
{
    inline std::thread::id getThreadID() { return std::this_thread::get_id(); }

    typedef struct Leaf
    {
    public:
        std::string timestamp;
        std::string filename;
        std::string funcname;
        std::string linenum;
        std::string message;
        std::string threadid;

        static struct Leaf pickone () {
            struct Leaf leaf;

            // leaf.timestamp = currentDateTime();

        }

    private:
        std::string currentDateTime() {
            time_t     now = time(0);
            struct tm  tstruct;
            char       buf[80];
            tstruct = *localtime(&now);
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

            return buf;
        }
    } Leaf;
    

    class Tree
    {
    private:
        /* data */
        std::string tag;
        
    public:
        Tree(/* args */) {};
        ~Tree() {};

    public:
        void d(const std::string &message, va_list args) { prepareLog(LogPriorityDebug, message, args); };
        void i(const std::string &message, va_list args) { prepareLog(LogPriorityInfo, message, args); };
        void w(const std::string &message, va_list args) { prepareLog(LogPriorityWarn, message, args); };
        void e(const std::string &message, va_list args) { prepareLog(LogPriorityError, message, args); };

        /** Stubs */
    public:
        virtual bool isLoggable(const std::string &tag, LogPriority priority) { return true; };

        virtual void log(LogPriority priority, const std::string &tag, const std::string &message) = 0;

    private:
        void prepareLog(LogPriority priority, const std::string &message, va_list args) {
            if (!isLoggable(tag, priority)) {
                return;
            }

            if (message.length() == 0) { // swallow emppty message
                return;
            }

            // TODO: getStackTraceString

            // if (args != null && args.length > 0) {
            //     message = formatMessage(message, args);
            //     }
            //     if (t != null) {
            //     message += "\n" + getStackTraceString(t);
            //     }
            Leaf leaf;
            log(priority, tag, formatMessage(getFormatString(message, args), leaf));
        }

        const std::string getFormatString(const std::string &message, va_list args) {
            char buf[4096];
            memset(buf, 0, sizeof(buf));
            vsprintf(buf, message.c_str(), args);

            return buf;
        }

        const std::string formatMessage(const std::string &message, const Leaf &leaf) {
            return message;
        }
    }; 

    class DebugTree : Tree {

    };

    class Forest : Tree {

    };
} // namespace timber


#endif // __MT_TREE_H__