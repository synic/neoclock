#ifndef _NEOCLOCK_RTC_H
#define _NEOCLOCK_RTC_H

#include <stdio.h>
#include "stm32f30x.h"

#define RTC_CLOCK_SOURCE_LSI

void set_time(RTC_TimeTypeDef RTC_TimeStructure);
void rtc_config(void);
void setup_rtc(void);

#endif
