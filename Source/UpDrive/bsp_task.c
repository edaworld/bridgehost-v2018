#include "bsp.h"

//#define NULL 0

extern uint8_t g_uart1_timeout; //��⴮��1�������ݳ�ʱ��ȫ�ֱ���

extern UARTDATATYPE g_tUart1; //��ʼ���Ӵ���1

extern uint8_t TPCTaskNum; //������������bsp_task.c�б���ʼ����bsp_tpc.c��ʹ��
extern uint8_t IsEnterIRQ;  //main.c���������м��SPI�ӿڵ�loraоƬ�Ƿ�����жϱ�־λ


TPC_TASK TaskComps[3] =
{
	//���������ʱ����ע�ⵥ�������иı��������ԵĴ��룬��������ӵ�����ŵ����
	{ 0, 0, 1, 1000, Task_LEDDisplay }, //����LED����  
	{ 0, 0, 1, 5, Task_RecvfromPC }, //��������������     
	{ 1, 0, 1, 5, Task_SendToSlave }, //��������λ��

};

/*********************************************************************************************************
*   �� �� ��: Task_LEDDisplay
*   ����˵��: LED��˸����
*********************************************************************************************************/
void Task_LEDDisplay(void)
{
	LED1_TOGGLE();
	return;
}

/*********************************************************************************************************
*   �� �� ��: Task_RecvfromPC
*   ����˵��: 
*********************************************************************************************************/
static uint8_t HostdataisReady = FALSE;
void Task_RecvfromPC(void)
{
//   ����3.5���ַ�ʱ���ִ��Uart1_RxTimeOut������ȫ�ֱ��� g_uart1_timeout = 1; ֪ͨ������ʼ����
	if (g_uart1_timeout == 0)
	{
		return; // û�г�ʱ���������ա���Ҫ���� g_tUart1.RxCount
	}
	if (g_tUart1.RxCount < 12)    // ���յ�������С��3���ֽھ���Ϊ����
	{
		return;
	}
	g_uart1_timeout = 0; // ��ʱ���־
	if ((g_tUart1.RxBuf[0] != '%') && (g_tUart1.RxBuf[8] != '&')) //������ݰ�ͷ�Ƿ���ȷ
	{
		printf("error in head!");
	} 
	else //������ݰ��Ƿ���ȷ
	{
    //���ݰ�������ȷ
		HostdataisReady = TRUE;
		TaskComps[2].attrb = 0;
	} 
	g_tUart1.RxCount = 0; // ��������������������´�֡ͬ��    
	return;
}

/*********************************************************************************************************
*   �� �� ��: Task_BroadCast
*   ����˵��: ���͹㲥�źŵ�����
*********************************************************************************************************/
void Task_SendToSlave(void)
{
	if(HostdataisReady == TRUE)
	{    
		RFSendData(g_tUart1.RxBuf, 12);
		TaskComps[2].attrb = 1;
		HostdataisReady = FALSE;
	}
}

/*********************************************************************************************************
*   �� �� ��: TaskInit
*   ����˵��: �����ʼ��
*********************************************************************************************************/
void TaskInit(void)
{
	TPCTaskNum = (sizeof(TaskComps) / sizeof(TaskComps[0])); // ��ȡ������
}
