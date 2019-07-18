#include "bsp.h"

const char *rfName = "SX1278";

uint8_t	sendBuf[64];    //发送缓冲区
uint8_t	revBuf[128];    //接收缓冲区

//初始化SX1278的四个IO口,PA8,PB12,PB10,PB11.
//PA8-----------RF_CE，RF_NREST引脚
//PB12----------RF_Csn
//PB10----------RF_IRQ
//PB11----------RF_SDN，没有用上
void RFGPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );
	/* Configure PA8 RF_CE/RF_NREST as Output push-pull -------------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure PB12 RF_Csn as Output push-pull -------------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure PB10 RF_IRQ as input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure PB11 RF_SDN as Output push-pull -------------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

//射频模块初始化
void RFInit(void)
{
	SPI2_Init();
	RFM96_LoRaEntryRx(); //进入接收模式
}

//射频模块进入接收模式
void RFRxMode(void)
{
	RFM96_LoRaEntryRx(); //进入接收模式
}

//射频模块接收数据
uint8_t RFRevData(void)
{
	uint8_t length = 0;
	length = RFM96_LoRaRxPacket(revBuf);
	RFRxMode();
	return (length);
}
//射频模块发射数据
uint8_t RFSendData(uint8_t *buf, uint8_t size)
{
	int ret = 0;
	ret = RFM96_LoRaEntryTx(size); //返回发送字节数
	ret = RFM96_LoRaTxPacket(buf, size); //返回发送字节数

	bsp_DelayMS(5);
	RFRxMode(); //进入接收模式

	return (ret); //成功后大于0的值
}

