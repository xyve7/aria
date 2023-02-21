#ifndef LOG_H
#define LOG_H

#include <libc/stdio.h>
#include <stdarg.h>
#include <cpu/x86_64/rtc/rtc.h>

#define TEST

#define log_debug(format, ...) log(false, 0, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define log_warn(format, ...) log(false, 1, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define log_error(format, ...) log(false, 2, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define log_info(format, ...) log(false, 3, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)

#define vlog_debug(format, ...) log(true, 0, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define vlog_warn(format, ...) log(true, 1, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define vlog_error(format, ...) log(true, 2, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define vlog_info(format, ...) log(true, 3, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)

void log(bool verbose, u8 type, const char* file, const char* function, u32 line, const char* format, ...);

#endif