#ifndef  __TASK__H__
#define  __TASK__H__
#include "bsp_tpc.h"
#pragma anon_unions             //ʹ�������ṹ��

typedef union
{
    uint8_t msg[8];
    struct
    {
        uint8_t head;//��ͷ
        uint8_t devID;//�豸id
        uint8_t Heartdata;//����ֵ
        uint8_t HrtPowerdata;//���ʴ�����      
        uint8_t BatPowerdata;//��ص���
        uint8_t tail;//��β      
    };
} SLVMSG_T; //�ӻ���Ϣ�ṹ��

typedef union
{
    uint8_t msg[8];
    struct
    {
        uint8_t N1STATUS;//�ڵ�1�Ƿ��յ�����״̬
        uint8_t N2STATUS;//�ڵ�2�Ƿ��յ�����״̬
        uint8_t N3STATUS;//�ڵ�3�Ƿ��յ�����״̬
        uint8_t N4STATUS;//�ڵ�4�Ƿ��յ�����״̬     
        uint8_t N5STATUS;//�ڵ�5�Ƿ��յ�����״̬
        uint8_t N6STATUS;//�ڵ�6�Ƿ��յ�����״̬
        uint8_t N7STATUS;//�ڵ�7�Ƿ��յ�����״̬
        uint8_t N8STATUS;//�ڵ�8�Ƿ��յ�����״̬    
    };
} M_STSTUS; //�ӻ���Ϣ�ṹ��
/********************************************************************************************************
* Variable definition
********************************************************************************************************/
extern TPC_TASK TaskComps[];

/********************************************************************************************************
* �ڲ�����
********************************************************************************************************/
static void Task_BroadCast(void);  // �㲥����
static void Task_LEDDisplay(void);  //LED��˸����
static void Task_SendToPC(void); //����������PC��
static void Task_RecvfromPC(void);
static void Task_RecvfromSlave(void); //��Lora��SX1278�������ӵĴ���2��ȡ��������
static void Task_SendToSlave(void);
/********************************************************************************************************
* ȫ�ֺ���
********************************************************************************************************/
extern void TaskInit(void); // ��ʼ��

/*******************************************************************************************************/
#endif

