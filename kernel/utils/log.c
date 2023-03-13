#include <utils/log.h>

void log(bool verbose, u8 type, const char* file, const char* function, u32 line, const char* format, ...)
{
	va_list list;
	va_start(list, format);
	switch (type)
	{
    case 0:
		printf("%02d:%02d:%02d", rtc_hours(), rtc_minutes(), rtc_seconds());
		if (verbose)
			printf(" %s:%s:%u", file, function, line);
		printf(" \x1b[32mDEBUG\x1b[0m ");
		vprintf(format, list);
		break;
	case 1:
		printf("%02d:%02d:%02d", rtc_hours(), rtc_minutes(), rtc_seconds());
		if (verbose)
			printf(" %s:%s:%u", file, function, line);
		printf(" \x1b[93mWARN\x1b[0m  ");
		vprintf(format, list);
		break;
	case 2:
		printf("%02d:%02d:%02d", rtc_hours(), rtc_minutes(), rtc_seconds());
		if (verbose)
			printf(" %s:%s:%u", file, function, line);
		printf(" \x1b[91mERROR\x1b[0m ");
		vprintf(format, list);
		break;
	case 3:
		printf("%02d:%02d:%02d", rtc_hours(), rtc_minutes(), rtc_seconds());
		if (verbose)
			printf(" %s:%s:%u", file, function, line);
		printf(" \x1b[94mINFO\x1b[0m  ");
		vprintf(format, list);
		break;
	default:
		break;
	}
	va_end(list);
}
