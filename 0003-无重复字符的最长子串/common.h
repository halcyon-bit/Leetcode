#pragma once

#include <cstdio>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
// define something for Windows (32-bit and 64-bit, this part is common)
#ifdef _WIN64
    // define something for Windows (64-bit only)
#define WINDOWS
#else 
    // define something for Windows (32-bit only)
#define WINDOWS
#endif
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#elif __linux__
// linux
#define LINUX
#elif __unix__ // all unices not caught above
// Unix
#define UNIX
#elif defined(_POSIX_VERSION)
// POSIX
#else
#   error "Unknown compiler"
#endif

#if defined WINDOWS
#include <windows.h>

// 0 = 黑色 8 = 灰色
// 1 = 蓝色 9 = 淡蓝色
// 2 = 绿色 10 = 淡绿色
// 3 = 浅绿色 11 = 淡浅绿色
// 4 = 红色 12 = 淡红色
// 5 = 紫色 13 = 淡紫色
// 6 = 黄色 14 = 淡黄色
// 7 = 白色 15 = 亮白色
inline void colorPrint(const char* s, int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
    printf(s);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}
#elif defined LINUX
// Black       0;30     Dark Gray     1;30
// Blue        0;34     Light Blue    1;34
// Green       0;32     Light Green   1;32
// Cyan        0;36     Light Cyan    1;36
// Red         0;31     Light Red     1;31
// Purple      0;35     Light Purple  1;35
// Brown       0;33     Yellow        1;33
// Light Gray  0;37     White         1;37
inline void colorPrint(const char* s, int color)
{
    // \033[0m 是恢复颜色到默认状态
    switch (color) {
    case 1:  // 蓝色
        printf("\033[0;34m%s\033[0m", s);
        break;
    case 2:  // 绿色
        printf("\033[0;32m%s\033[0m", s);
        break;
    case 4:  // 红色
        printf("\033[0;31m%s\033[0m", s);
        break;
    case 6:  // 黄色
        printf("\033[1;33m%s\033[0m", s);
        break;
    case 7:  // 白色
        printf("\033[1;37m%s\033[0m", s);
        break;
    }
}
#endif