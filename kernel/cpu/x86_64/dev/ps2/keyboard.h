#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <cpu/x86_64/cpu.h>
#include <cpu/x86_64/int/irq.h>
#include <cpu/x86_64/dev/ps2/ps2.h>

void keyboard_init();
void keyboard_handler(interrupt_frame* sf);

#endif/* KEYBOARD_H */
