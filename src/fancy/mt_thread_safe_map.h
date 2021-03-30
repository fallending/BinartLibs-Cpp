/*
 * @Author: your name
 * @Date: 2021-03-29 18:05:08
 * @LastEditTime: 2021-03-29 18:07:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/fancy/mt_thread_safe_map.h
 */

#include <map>
#include <memory>
#include <mutex>

#ifndef __MT_THREAD_SAFE_MAP_H__
#define __MT_THREAD_SAFE_MAP_H__

namespace mt {
    namespace threadsafe {
        //thread safe map, need to free data youself
        template<typename TKey, typename TValue>
        class map
        {
        public:
            map() 
            {
            }

            virtual ~map() 
            { 
                std::lock_guard<std::mutex> locker(m_mutexMap);
                m_map.clear(); 
            }

            bool insert(const TKey &key, const TValue &value, bool cover = false)
            {
                std::lock_guard<std::mutex> locker(m_mutexMap);

                auto find = m_map.find(key);
                if (find != m_map.end() && cover)
                {
                    m_map.erase(find);
                }

                auto result = m_map.insert(std::pair<TKey, TValue>(key, value));
                return result.second;
            }

            void remove(const TKey &key)
            {
                std::lock_guard<std::mutex> locker(m_mutexMap);

                auto find = m_map.find(key);
                if (find != m_map.end())
                {
                    m_map.erase(find);
                }
            }

            bool lookup(const TKey &key, TValue &value)
            {
                std::lock_guard<std::mutex> locker(m_mutexMap);

                auto find = m_map.find(key);
                if (find != m_map.end())
                {
                    value = (*find).second;
                    return true;
                }
                else
                {
                    return false;
                }
            }

            int size()
            {
                std::lock_guard<std::mutex> locker(m_mutexMap);
                return m_map.size();
            }

        public:
            std::mutex m_mutexMap;
            std::map<TKey, TValue> m_map;
        };
    }
} // namespace mt

#endif // __MT_THREAD_SAFE_MAP_H__
