#include "rtc.h"

__IO uint32_t AsynchPrediv = 0, SynchPrediv = 0;


void set_time(RTC_TimeTypeDef RTC_TimeStructure) {
    if(RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure) != ERROR) {
        RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
    }
}

void rtc_config(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    PWR_BackupAccessCmd(ENABLE);

    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);

#if defined (RTC_CLOCK_SOURCE_LSI)
    RCC_LSICmd(ENABLE);

    while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET) { }

    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

    SynchPrediv = 0x18F;
    AsynchPrediv = 0x63;

#elif defined (RTC_CLOCK_SOURCE_LSE)
    RCC_LSEConfig(RCC_LSE_ON);

    while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) { }

    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

    AsynchPrediv = 0x7F;
    SynchPrediv = 0xFF;

#else
  #error Please select the RTC Clock source inside the main.c file
#endif

    RCC_RTCCLKCmd(ENABLE);

    RTC_WaitForSynchro();
}

void setup_rtc(void) {
    RTC_InitTypeDef RTC_InitStructure;
#if defined (RTC_CLOCK_SOURCE_LSI)
    RCC_LSICmd(ENABLE);
#endif

    if(RTC_ReadBackupRegister(RTC_BKP_DR0) != 0x32F2) {
        rtc_config();

        RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
        RTC_InitStructure.RTC_SynchPrediv = SynchPrediv;
        RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;

        if(RTC_Init(&RTC_InitStructure) == ERROR) {
            printf("RTC Prescaler Config Failed");
        }

        RTC_TimeTypeDef RTC_TimeStructure;
        RTC_TimeStructure.RTC_H12 = RTC_H12_AM;
        RTC_TimeStructure.RTC_Hours = 0;
        RTC_TimeStructure.RTC_Minutes = 0;
        RTC_TimeStructure.RTC_Seconds = 1;
        set_time(RTC_TimeStructure);
    }
    else {
        if(RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET) {
            printf("\r\n Power On Reset occurred....\n\r");
        }
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET) {
            printf("\r\n External Reset occurred....\n\r");
        }

        printf("\n\r No need to configure RTC....\n\r");

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
        PWR_BackupAccessCmd(ENABLE);
        RTC_WaitForSynchro();
        RTC_ClearFlag(RTC_FLAG_ALRAF);
        EXTI_ClearITPendingBit(EXTI_Line17);
    }
}
