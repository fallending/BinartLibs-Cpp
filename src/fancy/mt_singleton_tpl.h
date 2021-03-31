/*
 * @Author: your name
 * @Date: 2021-03-29 18:08:55
 * @LastEditTime: 2021-03-29 18:10:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/fancy/mt_singleton_tpl.h
 */

#include <mutex>
#include <memory>

#ifndef __MT_SINGTON_TPL_H__
#define __MT_SINGTON_TPL_H__

namespace mt {

    namespace tpl {
        template <typename T>
        class singleton
        {
        public:
            // 创建单例实例
            template<typename ...Args>
            static std::shared_ptr<T> initial(Args&& ...args)
            {
                std::call_once(m_flag, [&] {m_instance = std::make_shared<T>(std::forward<Args>(args)...); });
                return m_instance;
            }

            // 获取单例
            static std::shared_ptr<T> get()
            {
                return m_instance;
            }

        private:
            singleton() = default;
            ~singleton() = default;
            singleton(const singleton &) = delete;
            singleton(singleton &&) = delete;
            singleton &operator=(const singleton &) = delete;
            singleton &operator=(singleton &&) = delete;

        private:
            static std::shared_ptr<T> m_instance;
            static std::once_flag m_flag;
        };

        template<typename T> std::once_flag singleton<T>::m_flag;
        template<typename T> std::shared_ptr<T> singleton<T>::m_instance;
    }
}

#endif // __MT_SINGTON_TPL_H__