/*
 * @Author: your name
 * @Date: 2021-03-25 16:15:35
 * @LastEditTime: 2021-03-25 16:52:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/log/file_log.cc
 */

#include "file_log.h"

namespace mt
{
    namespace log
    {
        int apple = 0;

        enum FruitType {
            FruitTypeApple = 0,
        };

        const char *getFruitName() {
            return "";
        };

        struct Fruit {
            FruitType type;
            const char *name;
        };

        void FruitFactory::buildFruit () {

        }
    } // namespace log
    
} // namespace mt