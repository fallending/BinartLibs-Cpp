/*
 * @Author: your name
 * @Date: 2021-03-22 17:16:11
 * @LastEditTime: 2021-03-25 18:40:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/timber/mt_timber.h
 */

#include "mt_type.h"
#include "mt_tree.h"

// #define __MT_TAG__ "tracking-name"

// LOG(INFO) << "easylogging++ test!"; // __FILE__ __LINE__ __FUNC__

#ifndef __MT_TIMBER_H__
#define __MT_TIMBER_H__

namespace timber
{
    #define TIMBER_ENUMARATE( code ) \
            for (auto tree : Timber::shared()._trees) \
            code
    #define TIMBER_VAARGS( code ) \
            va_list args; \
            va_start(args, message); \
            for (auto tree : Timber::shared()._trees) \
            code; \
            va_end(args); 

    #define TIMBER_LOG_FUNC_DEF( func ) \
            void func(const char *message, ...) { \
                va_list args; \
                va_start(args, message); \
                for (std::vector<std::shared_ptr<Tree> >::iterator it = Timber::shared()._trees.begin(); it != Timber::shared()._trees.end(); ++it) { \
                    if (message) it->get()->func(message, args); \
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

    #ifndef __MT_TAG__
    #define __MT_TAG__      ""
    #endif // __MT_TAG__

    static Timber logger = Timber::shared().tagged(__MT_TAG__);
    
} // namespace timber


#endif // __MT_TIMBER_H__