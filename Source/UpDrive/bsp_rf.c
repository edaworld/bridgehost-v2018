#include "bsp.h"

const char *rfName = "SX1278";

u16	iSend, iRev;    //���߷��ͺͽ��ռ���
u8	sendBuf[64];    //���ͻ�����
u8	revBuf[128];    //���ջ�����

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
u8 RFRevData(void)
{
	u8 length = 0;
//	if (GPIO_ReadInputDataBit(GPIOB, RF_IRQ_PIN)) //�յ����ݸߵ�ƽ�ж�
//	{
		length = RFM96_LoRaRxPacket(revBuf);
		RFRxMode();
//	}
//	if (length > 0) 
//		iRev++; //�������ݸ���
	return (length);
}
//��Ƶģ�鷢������
u8 RFSendData(u8 *buf, u8 size)
{
	int ret = 0;
	ret = RFM96_LoRaEntryTx(size); //���ط����ֽ���
	ret = RFM96_LoRaTxPacket(buf, size); //���ط����ֽ���

	bsp_DelayMS(5);
	RFRxMode(); //�������ģʽ
    
//	if (ret > 0) 
//		iSend++;    //�������ݸ���
	return (ret); //�ɹ������0��ֵ
}

