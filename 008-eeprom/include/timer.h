#ifndef __TIMER_H__
#define __TIMER_H__

#include <avr/io.h>

void timer_init();
void timer_delay_ms(int time_ms);

#endif
