#include "bsp.h" 

uint8_t IsEnterIRQ = FALSE;

extern UARTDATATYPE g_tUart1; //初始化从串口1
static uint8_t recvlength;
extern unsigned char  revBuf[128];    //接收缓冲区



//初始化独立看门狗
//prer：分频数：0~7（只有低 3 位有效！）
//分频因子=4*2^prer.但最大值只能是 256！
//rlr：重装载寄存器值：低 11 位有效。
//时间计算（大概）：Tout=（（4*2^prer）*rlr）/40 （ms）。
void IWDG_Init(uint8_t prer, uint16_t rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //①使能对寄存器 I 写操作
	IWDG_SetPrescaler(prer); //②设置 IWDG 预分频值：设置 IWDG 预分频值
	IWDG_SetReload(rlr); //②设置 IWDG 重装载值
	IWDG_ReloadCounter(); //③按照 IWDG 重装载寄存器的值重装载 IWDG 计数器
	IWDG_Enable(); //④使能 IWDG
}

//喂独立看门狗
void IWDG_Feed(void)
{
	IWDG_ReloadCounter();//reload
}


int main(void)
{
	bsp_Init();  //初始化硬件设备
	bsp_DelayMS(10); 
	IWDG_Init(4,625); //与分频数为 64，重载值为 625，溢出时间为 1s
	while (1)
	{
		IWDG_Feed();
		if(g_tUart1.RxCount >= 12 && g_tUart1.RxBuf[0] == '%' && g_tUart1.RxBuf[8] == '&')//从PC上位机串口接收到数据
		{
			RFSendData(g_tUart1.RxBuf,g_tUart1.RxCount);
			g_tUart1.RxCount = 0;
		}
		
		if(GPIO_ReadInputDataBit(GPIOB, RF_IRQ_PIN))//从下位机接收到数据
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
