/*
 * @Author: your name
 * @Date: 2021-03-23 20:02:45
 * @LastEditTime: 2021-03-26 16:40:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/timber/mt_type.h
 */

#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#ifndef MT_TYPE_H_
#define MT_TYPE_H_

namespace timber
{
// MARK: - Log Priority
enum LogPriority
{
    LogPriorityBegin = 0,

    // LogPriorityVerbose      = 1, // useless
    LogPriorityDebug = 2,
    LogPriorityInfo  = 3,
    LogPriorityWarn  = 4,
    LogPriorityError = 5,
    // LogPriorityAssert       = 6, // useless

    LogPriorityEnd
};

#define IS_LOG_PRIORITY_VALID(t) \
    (((t) < LogPriorityEnd) && ((t) > LogPriorityBegin))

// MARK: - Logger Color

// #define WINDOWS
// #define LINUX

#ifdef WINDOWS
#include <windows.h>

#include <iostream>

inline std::ostream& blue(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(
        hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& red(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& green(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& yellow(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(
        hStdout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& white(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(
        hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return s;
}

struct color
{
    color(WORD attribute) : m_color(attribute){};
    WORD m_color;
};

template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>& operator<<(
    std::basic_ostream<_Elem, _Traits>& i, const color& c)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, c.m_color);
    return i;
}

#else

const std::vector<std::string> terminal_control = {
    std::string("\033[0m"),    // 关闭属性
    std::string("\033[1m"),    // 设置高亮
    std::string("\033[3m"),    // 斜体
    std::string("\033[4m"),    // 下划线
    std::string("\033[5m"),    // 闪烁（无效）
    std::string("\033[7m"),    // 反显
    std::string("\033[8m"),    // 消隐
    std::string("\033[30m"),   // 设置前景色:黑色
    std::string("\033[40m"),   // 设置背景色:黑色
    std::string("\033[31m"),   // 设置前景色:深红
    std::string("\033[41m"),   // 设置背景色:深红
    std::string("\033[32m"),   // 设置前景色:绿色
    std::string("\033[42m"),   // 设置背景色:绿色
    std::string("\033[33m"),   // 设置前景色:黄色
    std::string("\033[43m"),   // 设置背景色:黄色
    std::string("\033[34m"),   // 设置前景色:蓝色
    std::string("\033[44m"),   // 设置背景色:蓝色
    std::string("\033[35m"),   // 设置前景色:紫色
    std::string("\033[45m"),   // 设置背景色:紫色
    std::string("\033[36m"),   // 设置前景色:深绿色
    std::string("\033[46m"),   // 设置背景色:深绿色
    std::string("\033[37m"),   // 设置前景色:白色
    std::string("\033[47m"),   // 设置背景色:白色
    std::string("\033[nA"),    // 光标上移n行
    std::string("\033[nB"),    // 光标下移n行
    std::string("\033[nC"),    // 光标右移n列
    std::string("\033[nD"),    // 光标左移n列
    std::string("\033[y;xH"),  // 设置光标位置(无效)
    std::string("\033[2J"),    // 清屏
    std::string("\033[K"),     // 清除从光标道行尾的内容
    std::string("\033[s"),     // 保存光标位置
    std::string("\033[u"),     // 恢复光标位置
    std::string("\033[?25l"),  // 隐藏光标
    std::string("\033[?25h"),  // 显示光标
};

inline std::ostream& Blue(std::ostream& s)
{
    //    s << "\033[0m\033[34m\033[1m"; // ok
    s << "\033[0;1;34m";
    return s;
}

inline std::ostream& Red(std::ostream& s)
{
    //    s << "\033[0m\033[31m\033[1m"; // ok
    s << "\033[0;1;31m";
    return s;
}

inline std::ostream& Green(std::ostream& s)
{
    //    s << "\033[0m\033[32m\033[1m"; // ok
    s << "\033[0;1;32m";
    return s;
}

inline std::ostream& Yellow(std::ostream& s)
{
    //    s << "\033[0m\033[33m\033[1m"; // ok
    s << "\033[0;1;33m";
    return s;
}

inline std::ostream& White(std::ostream& s)
{
    //    s << "\033[0m\033[37m\033[1m"; // ok
    s << "\033[0;1;37m";
    return s;
}

inline std::ostream& Reset(std::ostream& s)
{
    s << "\033[0m";
    return s;
}

#endif

}  // namespace timber

#endif  // MT_TYPE_H_