#include "bsp.h" 

uint8_t IsEnterIRQ = FALSE;

extern UARTDATATYPE g_tUart1; //��ʼ���Ӵ���1
static uint8_t recvlength;
extern unsigned char  revBuf[128];    //���ջ�����



//��ʼ���������Ź�
//prer����Ƶ����0~7��ֻ�е� 3 λ��Ч����
//��Ƶ����=4*2^prer.�����ֵֻ���� 256��
//rlr����װ�ؼĴ���ֵ���� 11 λ��Ч��
//ʱ����㣨��ţ���Tout=����4*2^prer��*rlr��/40 ��ms����
void IWDG_Init(uint8_t prer, uint16_t rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //��ʹ�ܶԼĴ��� I д����
	IWDG_SetPrescaler(prer); //������ IWDG Ԥ��Ƶֵ������ IWDG Ԥ��Ƶֵ
	IWDG_SetReload(rlr); //������ IWDG ��װ��ֵ
	IWDG_ReloadCounter(); //�۰��� IWDG ��װ�ؼĴ�����ֵ��װ�� IWDG ������
	IWDG_Enable(); //��ʹ�� IWDG
}

//ι�������Ź�
void IWDG_Feed(void)
{
	IWDG_ReloadCounter();//reload
}


int main(void)
{
	bsp_Init();  //��ʼ��Ӳ���豸
	bsp_DelayMS(10); 
	IWDG_Init(4,625); //���Ƶ��Ϊ 64������ֵΪ 625�����ʱ��Ϊ 1s
	while (1)
	{
		IWDG_Feed();
		if(g_tUart1.RxCount >= 12 && g_tUart1.RxBuf[0] == '%' && g_tUart1.RxBuf[8] == '&')//��PC��λ�����ڽ��յ�����
		{
			RFSendData(g_tUart1.RxBuf,g_tUart1.RxCount);
			g_tUart1.RxCount = 0;
		}
		
		if(GPIO_ReadInputDataBit(GPIOB, RF_IRQ_PIN))//����λ�����յ�����
		{
			recvlength = RFRevData();				
			if(recvlength >= 12)
			{				
				COMx_SendBuf(COM1,revBuf,recvlength);
				recvlength = 0;
			}
			else
			{
				recvlength = 0;
			}
		}
	}
}
