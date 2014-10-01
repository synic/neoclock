#include "gpio.h"

void setup_gpio(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    // set up pin 5 for the status LED
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // set up pin 6 for the timer
    GPIO_InitTypeDef GPIO_InitStructure2;
    GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure2.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure2);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_2);

}

