#include "bsp.h" 

uint8_t IsEnterIRQ = FALSE;
static uint8_t slavedataisReady = FALSE;

extern UARTDATATYPE g_tUart1; //初始化从串口1
static uint8_t recvlength;
extern unsigned char  revBuf[128];    //接收缓冲区
int main(void)
{
	bsp_Init();  //初始化硬件设备
	bsp_DelayMS(10);
	TaskInit(); //初始化任务,仅是获取任务数量，任务调度在bsp_idle中调用task_process实现    
	while (1)
	{
//		if (GPIO_ReadInputDataBit(GPIOB, RF_IRQ_PIN)) //SPI的SX1278，接收到数据时，IRQ引脚为高
//		{
//			IsEnterIRQ = TRUE;
//		} 

//		if (IsEnterIRQ  == TRUE)
//		{
//				u8 length = 0;
//				length = RFM96_LoRaRxPacket(recvSlavedatbuf);
//				RFRxMode();
//				if ((recvSlavedatbuf[0] == '&') && (recvSlavedatbuf[8] == '%')) //检测数据包头是否正确
//				{
//						slavedataisReady = TRUE;
//				}
//		}
//		if(slavedataisReady == TRUE)
//		{
//				COMx_SendBuf(COM1,recvSlavedatbuf,12);
//				memset(recvSlavedatbuf,0,12);
//				slavedataisReady = FALSE;
//				IsEnterIRQ = FALSE;            
//		}      
//		bsp_Idle(); 
		if(g_tUart1.RxCount >= 5 && g_tUart1.RxBuf[0] == 'S')//从PC上位机串口接收到数据
		{
			RFSendData(g_tUart1.RxBuf,g_tUart1.RxCount);
			g_tUart1.RxCount = 0;
		}
		if(GPIO_ReadInputDataBit(GPIOB, RF_IRQ_PIN))
		{
			recvlength = RFRevData();			
			COMx_SendBuf(COM1,revBuf,recvlength);
			recvlength = 0;
		}
	}
}
