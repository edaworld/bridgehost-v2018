#include "bsp.h"

//#define NULL 0

extern uint8_t g_uart1_timeout; //检测串口1接收数据超时的全局变量

extern UARTDATATYPE g_tUart1; //初始化从串口1

extern uint8_t TPCTaskNum; //任务数量，在bsp_task.c中被初始化，bsp_tpc.c中使用
extern uint8_t IsEnterIRQ;  //main.c的主函数中检测SPI接口的lora芯片是否进入中断标志位


TPC_TASK TaskComps[3] =
{
	//添加新任务时，请注意单个任务中改变任务属性的代码，否则将新添加的任务放到最后
	{ 0, 0, 1, 1000, Task_LEDDisplay }, //测试LED程序  
	{ 0, 0, 1, 5, Task_RecvfromPC }, //从主机接收数据     
	{ 1, 0, 1, 5, Task_SendToSlave }, //发送至下位机

};

/*********************************************************************************************************
*   函 数 名: Task_LEDDisplay
*   功能说明: LED闪烁代码
*********************************************************************************************************/
void Task_LEDDisplay(void)
{
	LED1_TOGGLE();
	return;
}

/*********************************************************************************************************
*   函 数 名: Task_RecvfromPC
*   功能说明: 
*********************************************************************************************************/
static uint8_t HostdataisReady = FALSE;
void Task_RecvfromPC(void)
{
//   超过3.5个字符时间后执行Uart1_RxTimeOut函数。全局变量 g_uart1_timeout = 1; 通知主程序开始解码
	if (g_uart1_timeout == 0)
	{
		return; // 没有超时，继续接收。不要清零 g_tUart1.RxCount
	}
	if (g_tUart1.RxCount < 12)    // 接收到的数据小于3个字节就认为错误
	{
		return;
	}
	g_uart1_timeout = 0; // 超时清标志
	if ((g_tUart1.RxBuf[0] != '%') && (g_tUart1.RxBuf[8] != '&')) //检测数据包头是否正确
	{
		printf("error in head!");
	} 
	else //检测数据包是否都正确
	{
    //数据包接收正确
		HostdataisReady = TRUE;
		TaskComps[2].attrb = 0;
	} 
	g_tUart1.RxCount = 0; // 必须清零计数器，方便下次帧同步    
	return;
}

/*********************************************************************************************************
*   函 数 名: Task_BroadCast
*   功能说明: 发送广播信号的任务
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
*   函 数 名: TaskInit
*   功能说明: 任务初始化
*********************************************************************************************************/
void TaskInit(void)
{
	TPCTaskNum = (sizeof(TaskComps) / sizeof(TaskComps[0])); // 获取任务数
}
