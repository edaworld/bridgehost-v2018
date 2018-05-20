/********************************************************************************************************
*   ģ������ : BSPģ��
*   �ļ����� : bsp.h
*   ˵    �� : ���ǵײ�����ģ�����е�h�ļ��Ļ����ļ��� Ӧ�ó���ֻ�� #include bsp.h ���ɣ�
*             ����Ҫ#include ÿ��ģ��� h �ļ�
*
*   Copyright (C), 2013-2014, ���������� www.armfly.com
*********************************************************************************************************/
#ifndef _BSP_H_
#define _BSP_H

/* ����ȫ���жϵĺ� */
#define ENABLE_INT()    __set_PRIMASK(0)    /* ʹ��ȫ���ж� */
#define DISABLE_INT()   __set_PRIMASK(1)    /* ��ֹȫ���ж� */

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

/* ͨ��ȡ��ע�ͻ������ע�͵ķ�ʽ�����Ƿ�����ײ�����ģ�� */

#include "bsp_led.h"
//#include "bsp_spi1.h"
#include "bsp_spi2.h"
#include "bsp_tpc.h"
#include "bsp_task.h"
#include "bsp_uartpro.h"
#include "bsp_uart_fifo.h"
#include "bsp_timer.h"
//#include "bsp_oledio.h"
#include "bsp_userlib.h"
#include "bsp_sx1276-LoRa.h"
#include "bsp_rf.h"
#include "bsp_systimer.h"

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* �ṩ������C�ļ����õĺ��� */
void bsp_Init(void);
void bsp_Idle(void);

#endif

