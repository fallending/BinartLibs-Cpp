/*
 * @Author: your name
 * @Date: 2021-03-25 16:15:02
 * @LastEditTime: 2021-03-25 16:51:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/log/log.h
 */


#ifndef __MT_LOG_H__
#define __MT_LOG_H__

namespace mt
{
    namespace log
    {
        const char *getFruitName();

        class FruitFactory {
            void buildFruit();
        };
    } // namespace log
    
} // namespace mt


#endif // __MT_LOG_H__