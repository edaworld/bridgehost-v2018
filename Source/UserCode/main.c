#include "bsp.h" 

uint8_t IsEnterIRQ = FALSE;
static uint8_t slavedataisReady = FALSE;

extern UARTDATATYPE g_tUart1; //��ʼ���Ӵ���1
static uint8_t recvlength;
extern unsigned char  revBuf[128];    //���ջ�����
int main(void)
{
	bsp_Init();  //��ʼ��Ӳ���豸
	bsp_DelayMS(10);
	TaskInit(); //��ʼ������,���ǻ�ȡ�������������������bsp_idle�е���task_processʵ��    
	while (1)
	{
//		if (GPIO_ReadInputDataBit(GPIOB, RF_IRQ_PIN)) //SPI��SX1278�����յ�����ʱ��IRQ����Ϊ��
//		{
//			IsEnterIRQ = TRUE;
//		} 

//		if (IsEnterIRQ  == TRUE)
//		{
//				u8 length = 0;
//				length = RFM96_LoRaRxPacket(recvSlavedatbuf);
//				RFRxMode();
//				if ((recvSlavedatbuf[0] == '&') && (recvSlavedatbuf[8] == '%')) //������ݰ�ͷ�Ƿ���ȷ
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
		if(g_tUart1.RxCount >= 5 && g_tUart1.RxBuf[0] == 'S')//��PC��λ�����ڽ��յ�����
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
