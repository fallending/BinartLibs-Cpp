/*
 * @Author: your name
 * @Date: 2021-03-25 18:42:34
 * @LastEditTime: 2021-03-25 18:53:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/timber/mt_leaf.h
 */

#include "mt_type.h"

#ifndef __MT_LEAF_H__
#define __MT_LEAF_H__

// https://blog.csdn.net/u014755412/article/details/79334572

namespace timber
{
    /**
     * @description: 获取线程ID
     * @param {return} std
     * @return {*}
     */
    inline std::thread::id getThreadID() { return std::this_thread::get_id(); }

    /**
     * @description: 叶子
     * @param {*}
     * @return {*}
     */
    typedef struct Leaf
    {
    public:
        std::string tag;    // 标记
        std::string ts;     // 时间戳
        std::string file;   // 文件名
        std::string func;   // 函数名
        std::string line;   // 文件行数
        std::string tid;    // 线程ID

        Leaf(
            const std::string &tag,
            const std::string &ts,
            const std::string &file,
            const std::string &func,
            const std::string &line,
            const std::string &tid
        ) {
            this->tag = tag;
            this->ts = ts;
            this->file = file;
            this->func = func;
            this->line = line;
            this->tid = tid;
        };
        ~Leaf() {};

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
    
    /**
     * @description: 一片叶子
     * @param {*}
     * @return {*}
     */
    inline Leaf make_leaf() {  
        return Leaf();
    };
} // namespace timber


#endif // __MT_LEAF_H__