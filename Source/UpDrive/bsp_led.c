/*********************************************************************************************************
*
*   模块名称 : LED模块(For STM32F1XX)
*   文件名称 : bsp_led.c
*   说    明 : 初始化LED灯所需要的GPIO端口
*
*********************************************************************************************************/
#include "bsp.h"
/*********************************************************************************************************
*   函 数 名: LED_Init
*   功能说明: 初始化LED所对应的引脚，分别为PA11、PA12和PB0、PB1
*********************************************************************************************************/
void LED_Init(void)
{ 
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;
    GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
    GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
    GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
    GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);    
}

//STM32的PB3、PB4，分别是JTAG的JTDO和NJTRST引脚，在没关闭JTAG功能之前，在程序中是配置不了这些
//引脚的功能要配置这些引脚，首先要开启AFIO时钟，然后在AFIO的设置中，释放这些引脚。具体看STM32
//的参考手册中有关AFIO的部分。
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
