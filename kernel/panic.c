#include <kernel.h>

noreturn void kernel_panic(const char * format, const char * file, const char * function, u32 line, ...) {
    va_list list;
	va_start(list, format);
    printf("%02d:%02d:%02d", rtc_hours(), rtc_minutes(), rtc_seconds());
    printf(" %s:%s:%u", file, function, line);
    printf(" \x1b[91mPANIC\x1b[0m ");
    vprintf(format, list);
	va_end(list);

    hang();
}