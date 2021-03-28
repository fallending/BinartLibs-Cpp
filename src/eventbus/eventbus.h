/*
 * @Author: your name
 * @Date: 2021-03-27 16:20:27
 * @LastEditTime: 2021-03-27 16:24:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/eventbus/eventbus.h
 */

#ifndef __MT_EVENTBUS_H__
#define __MT_EVENTBUS_H__

#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <unordered_map>
#include <algorithm>

namespace eventbus {
    class  BaseMessage {
    public:
        BaseMessage(std::string id) {
            std::hash<std::string>  hash;
            
            m_id = hash(id);
        };
        virtual ~BaseMessage() {};
        
        unsigned int getId() const { return m_id; }
        
    protected:
        unsigned int    m_id;
    };

    template<typename T>
    class Message : public BaseMessage
    {
    public:
        Message(std::string id, T* data) : BaseMessage(id), m_data(data) {};
        virtual ~Message() {};
        
        T *getData() const { return m_data.get(); }
        
    protected:
        std::auto_ptr<T>    m_data;
    };
    
    class Bus
    {
    public:
        Bus() {};
        ~Bus() {};
        
        void addListener(std::string id, std::function<void(BaseMessage*)> function) {
            std::hash<std::string>  hash;
            listeners.insert(std::pair<unsigned int, std::function<void(BaseMessage *)> >(hash(id), function));
        };
        
        template<typename U>
        Message<U> *sendMessage(Message<U> *message) {
            auto range = listeners.equal_range(message->getId());
            for_each(range.first, range.second, [message] (std::unordered_multimap<unsigned int, std::function<void(BaseMessage*)> >::value_type& i) {
                i.second(message);
            });
            return message;
        }
        
    protected:
        std::unordered_multimap<unsigned int, std::function<void(BaseMessage *)> > listeners;
    };

}
#endif // __MT_EVENTBUS_H__