#ifndef LOG_H
#define LOG_H

#include <libc/stdio.h>
#include <stdarg.h>
#include <cpu/x86_64/rtc/rtc.h>

#define log_debug(format, ...) log(0, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define log_warn(format, ...) log(1, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define log_error(format, ...) log(2, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define log_info(format, ...) log(3, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)

void log(u8 type, const char* file, const char* function, u32 line, const char* format, ...);

#endif