/*
 * @Author: your name
 * @Date: 2021-03-22 17:16:11
 * @LastEditTime: 2021-03-26 16:44:12
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/timber/mt_timber.h
 */

#include "mt_type.h"
#include "mt_tree.h"

#ifndef __MT_TIMBER_H__
#define __MT_TIMBER_H__

namespace timber
{
    #define TIMBER_LOG_FUNC_DEF( func ) \
            void func(const LeafPtr &leaf, const char *message, ...) { \
                va_list args; \
                va_start(args, message); \
                for (std::vector<std::shared_ptr<Tree> >::iterator it = Timber::shared()._trees.begin(); it != Timber::shared()._trees.end(); ++it) { \
                    if (message) it->get()->func(leaf, message, args); \
                } \
                va_end(args); \
            } \
            void func(const char *message, ...) { \
                va_list args; \
                va_start(args, message); \
                for (std::vector<std::shared_ptr<Tree> >::iterator it = Timber::shared()._trees.begin(); it != Timber::shared()._trees.end(); ++it) { \
                    if (message) it->get()->func(create_leaf(LogPriorityFromShort(#func)), message, args); \
                } \
                va_end(args); \
            }

    class Timber
    {
    private:
        std::string _tag;
        std::vector<std::shared_ptr<Tree> > _trees;

    public:
        Timber(const std::string &tag) { _tag = tag; };
        ~Timber() {};

    public:
        static Timber& shared() {
            static Timber instance("");
            return instance;
        }

        Timber tagged(const std::string &tag) {
            return Timber(tag);
        }
        
        void plant(std::shared_ptr<Tree> tree) {
            static std::mutex lock;
            lock.lock();

            Timber::shared()._trees.emplace_back(tree);

            lock.unlock();
        };

        TIMBER_LOG_FUNC_DEF(d)
        TIMBER_LOG_FUNC_DEF(i)
        TIMBER_LOG_FUNC_DEF(w)
        TIMBER_LOG_FUNC_DEF(e)
    };

    #ifndef __TAG__
    #define __TAG__      ""
    #endif // __TAG__

    static Timber logger = Timber::shared().tagged(__TAG__); // 每个引用的源文件，都会有它

    #define logd( message, ... ) logger.d(create_leaf(LogPriorityDebug, __TAG__, fileNameFromPath(__FILE__), __FUNCTION__, std::to_string(__LINE__)), message, ##__VA_ARGS__);
    #define logi( message, ... ) logger.i(create_leaf(LogPriorityInfo, __TAG__, fileNameFromPath(__FILE__), __FUNCTION__, std::to_string(__LINE__)), message, ##__VA_ARGS__);
    #define logw( message, ... ) logger.w(create_leaf(LogPriorityWarn, __TAG__, fileNameFromPath(__FILE__), __FUNCTION__, std::to_string(__LINE__)), message, ##__VA_ARGS__);
    #define loge( message, ... ) logger.e(create_leaf(LogPriorityError, __TAG__, fileNameFromPath(__FILE__), __FUNCTION__, std::to_string(__LINE__)), message, ##__VA_ARGS__);
    
} // namespace timber


#endif // __MT_TIMBER_H__