#ifndef RTC_H
#define RTC_H

#include <cpu/x86_64/cpu.h>
#include <stdbool.h>

#define rtc_seconds_reg   0x00
#define rtc_minutes_reg   0x02
#define rtc_hours_reg 	  0x04
#define rtc_weekday_reg   0x06
#define rtc_day_reg 	  0x07
#define rtc_month_reg 	  0x08
#define rtc_year_reg 	  0x09
#define rtc_century_reg   0x32
#define rtc_status_reg_a  0x0A
#define rtc_status_reg_b  0x0B

#define rtc_write_port    0x70
#define rtc_read_port     0x71

#define rtc_12_24_hour	  0x02
#define rtc_binary_bcd	  0x04

typedef struct {
	bool is_24_hour;
	bool is_binary;
} rtc_response;

u8 rtc_seconds(void);
u8 rtc_minutes(void);
u8 rtc_hours(void);
u8 rtc_weekday(void);
u8 rtc_day(void);
u8 rtc_month(void);
u8 rtc_year(void);
u8 rtc_century(void);
rtc_response rtc_init(bool set_binary);

#endif // RTC_H