#include <utils/log.h>

void log(u8 type, const char* file, const char* function, u32 line, const char* format, ...)
{
	va_list list;
	va_start(list, format);
	switch (type)
	{
    case 0:
		printf("\x1b[90m%02d:%02d:%02d\x1b[0m \x1b[32mDEBUG\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_hours(), rtc_minutes(), rtc_seconds(), file, function, line);
		vprintf(format, list);
		break;
	case 1:
		printf("\x1b[90m%02d:%02d:%02d\x1b[0m \x1b[95mWARN\x1b[0m  \x1b[90m%s:%s:%u\x1b[0m ", rtc_hours(), rtc_minutes(), rtc_seconds(), file, function, line);
		vprintf(format, list);
		break;
	case 2:
		printf("\x1b[90m%02d:%02d:%02d\x1b[0m \x1b[91mERROR\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_hours(), rtc_minutes(), rtc_seconds(), file, function, line);
		vprintf(format, list);
		break;
	case 3:
		printf("\x1b[90m%02d:%02d:%02d\x1b[0m \x1b[36mINFO\x1b[0m  \x1b[90m%s:%s:%u\x1b[0m ", rtc_hours(), rtc_minutes(), rtc_seconds(), file, function, line);
		vprintf(format, list);
		break;
	default:
		break;
	}
	va_end(list);
}
