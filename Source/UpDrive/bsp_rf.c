#include "bsp.h"

const char *rfName = "SX1278";

uint8_t	sendBuf[64];    //���ͻ�����
uint8_t	revBuf[128];    //���ջ�����

//��ʼ��SX1278���ĸ�IO��,PA8,PB12,PB10,PB11.
//PA8-----------RF_CE��RF_NREST����
//PB12----------RF_Csn
//PB10----------RF_IRQ
//PB11----------RF_SDN��û������
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

//��Ƶģ���ʼ��
void RFInit(void)
{
	SPI2_Init();
	RFM96_LoRaEntryRx(); //�������ģʽ
}

//��Ƶģ��������ģʽ
void RFRxMode(void)
{
	RFM96_LoRaEntryRx(); //�������ģʽ
}

//��Ƶģ���������
uint8_t RFRevData(void)
{
	uint8_t length = 0;
	length = RFM96_LoRaRxPacket(revBuf);
	RFRxMode();
	return (length);
}
//��Ƶģ�鷢������
uint8_t RFSendData(uint8_t *buf, uint8_t size)
{
	int ret = 0;
	ret = RFM96_LoRaEntryTx(size); //���ط����ֽ���
	ret = RFM96_LoRaTxPacket(buf, size); //���ط����ֽ���

	bsp_DelayMS(5);
	RFRxMode(); //�������ģʽ

	return (ret); //�ɹ������0��ֵ
}

