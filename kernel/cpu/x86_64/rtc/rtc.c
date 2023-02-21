#include <cpu/x86_64/rtc/rtc.h>

bool binary;

/**
 * @brief Reads a value from the RTC register.
 *
 * @param reg the register to read from.
 * @return the value read from the register.
 */
static inline u8 rtc_read(u8 reg) {
	outb(rtc_write_port, reg);
	return inb(rtc_read_port);
}
/**
 * @brief Converts a BCD value to binary.
 *
 * @param bcd the BCD value to convert.
 * @return the equivalent binary value.
 */
static inline u8 rtc_to_binary(u8 bcd) {
	return (((bcd & 0xF0) >> 1) + ((bcd & 0xF0) >> 3) + (bcd & 0xf));
}
u8 rtc_seconds(void) {
	u8 ret = rtc_read(rtc_seconds_reg);
	return binary ? rtc_to_binary(ret) : ret;
}
u8 rtc_minutes(void) {
	u8 ret = rtc_read(rtc_minutes_reg);
	return binary ? rtc_to_binary(ret) : ret;
}
u8 rtc_hours(void) {
	u8 ret = rtc_read(rtc_hours_reg);
	return binary ? rtc_to_binary(ret) : ret;
}
u8 rtc_weekday(void) {
	u8 ret = rtc_read(rtc_weekday_reg);
	return binary ? rtc_to_binary(ret) : ret;
}
u8 rtc_day(void) {
	u8 ret = rtc_read(rtc_day_reg);
	return binary ? rtc_to_binary(ret) : ret;
}
u8 rtc_month(void) {
	u8 ret = rtc_read(rtc_month_reg);
	return binary ? rtc_to_binary(ret) : ret;
}
u8 rtc_year(void) {
	u8 ret = rtc_read(rtc_century_reg);
	return binary ? rtc_to_binary(ret) : ret;
}
u8 rtc_century(void) {
	u8 ret = rtc_read(rtc_seconds_reg);
	return binary ? rtc_to_binary(ret) : ret;
}
void rtc_init(bool set_binary) {
	u8 status = rtc_read(rtc_status_reg_b);
	binary = set_binary;
	vlog_info("Real Time Clock (RTC) has been initialized\n");
}