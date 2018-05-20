#ifndef __OLED_H__
#define __OLED_H__

/*----------------------------------------------------------------------------*
 * ����ͷ�ļ�                                                                 *
 *----------------------------------------------------------------------------*/

#include "stm32f10x.h"
/*----------------------------------------------------------------------------*
 * �궨��                                                                     *
 *----------------------------------------------------------------------------*/
#define LED_IMAGE_WHITE       1
#define LED_IMAGE_BLACK       0

#define LED_MAX_ROW_NUM      64
#define LED_MAX_COLUMN_NUM  128

/*----------------------------------------------------------------------------*
 * ȫ�ֱ���                                                                   *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ڲ�����ԭ��                                                               *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ⲿ����ԭ��                                                               *
 *----------------------------------------------------------------------------*/
extern void OLEDIO_Init(void); 
extern void OLED_Init(void);
extern void OLED_Fill(uint8_t ucData);
extern void OLED_SetPos(uint8_t ucIdxX, uint8_t ucIdxY); 
extern void OLED_P6x8Char(uint8_t ucIdxX,uint8_t ucIdxY,uint8_t ucData);   //��ʾһ��6x8��׼ASCII�ַ�
extern void OLED_P6x8Str(uint8_t ucIdxX,uint8_t ucIdxY,int8_t ucDataStr[]);
extern void OLED_P8x16Str(uint8_t ucIdxX,uint8_t ucIdxY,int8_t ucDataStr[]);  //д��һ��8x16��׼ASCII�ַ���
extern void OLED_P14x16Str(uint8_t ucIdxX,uint8_t ucIdxY,int8_t ucDataStr[]);	  //д��һ��14x16�������ַ������ַ���������躬�д��֣�
extern void OLED_PXx16MixStr(uint8_t ucIdxX, uint8_t ucIdxY, int8_t ucDataStr[]); //���14x16���ֺ��ַ�����ַ��� ���ַ���������躬�д��֣�
extern void OLED_Fill(uint8_t ucData);
extern void OLED_PrintChar(uint8_t ucIdxX, uint8_t ucIdxY, int8_t cData);
extern void OLED_PrintShort(uint8_t ucIdxX, uint8_t ucIdxY, int16_t sData);
extern void OLED_PrintImage(uint8_t *pucTable, uint16_t usRowNum, uint16_t usColumnNum);

extern void OLEDPrint(int x,int y,char *msg);
#endif

