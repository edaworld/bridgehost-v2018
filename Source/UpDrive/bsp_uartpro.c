#include "bsp.h"

uint8_t g_uart1_timeout = 0;  //检测串口1接收数据超时的全局变量
uint8_t g_uart2_timeout = 0;  //检测串口2接收数据超时的全局变量
UARTDATATYPE g_tUart1;  //初始化从串口1，BLE接收数据结构体
UARTDATATYPE g_tUart2;  //初始化从串口2，Lora接收数据结构体
/*********************************************************************************************************
*   函 数 名: Uart1_RxTimeOut
*   功能说明: 超过3.5个字符时间后执行本函数。 设置全局变量 g_uart1_timeout = 1; 通知主程序开始解码。
*   形    参: 无
*   返 回 值: 无
*********************************************************************************************************/
static void Uart1_RxTimeOut(void)
{
    g_uart1_timeout = 1;
}
/*********************************************************************************************************
*   函 数 名: Uart2_RxTimeOut
*   功能说明: 超过3.5个字符时间后执行本函数。 设置全局变量 g_uart2_timeout = 1; 通知主程序开始解码。
*   形    参: 无
*   返 回 值: 无
*********************************************************************************************************/
static void Uart2_RxTimeOut(void)
{
    g_uart2_timeout = 1;
}
/*********************************************************************************************************
*   函 数 名: Uart1Callback_ReciveNew
*   功能说明: 串口接收中断服务程序会调用本函数。当收到一个字节时，执行一次本函数。
*   形    参: 无
*   返 回 值: 无
*********************************************************************************************************/
void Uart1Callback_ReciveNew(uint8_t _byte)
{
    /*
        3.5个字符的时间间隔，只是用在RTU模式下面，因为RTU模式没有开始符和结束符，
        两个数据包之间只能靠时间间隔来区分，Modbus定义在不同的波特率下，间隔时间是不一样的，
        所以就是3.5个字符的时间，波特率高，这个时间间隔就小，波特率低，这个时间间隔相应就大

        4800  = 7.297ms
        9600  = 3.646ms
        19200  = 1.771ms
        38400  = 0.885ms
    */
    uint32_t timeout;

    g_uart1_timeout = 0;

    timeout = 35000000 / 115200;            /* 计算超时时间，单位us 35000000*/

//  printf("%x\t",_byte);
//  硬件定时中断，定时精度us，使用定时器2用于检测接收超时
    bsp_StartHardTimer(1, timeout, (void *)Uart1_RxTimeOut);

    if (g_tUart1.RxCount < S_RX_BUF_SIZE)
    {
        g_tUart1.RxBuf[g_tUart1.RxCount++] = _byte;
    }
}

/*********************************************************************************************************
*   函 数 名: Uart2Callback_ReciveNew
*   功能说明: 串口接收中断服务程序会调用本函数。当收到一个字节时，执行一次本函数。
*   形    参: 无
*   返 回 值: 无
*********************************************************************************************************/
void Uart2Callback_ReciveNew(uint8_t _byte)
{
    /*
        3.5个字符的时间间隔，只是用在RTU模式下面，因为RTU模式没有开始符和结束符，
        两个数据包之间只能靠时间间隔来区分，Modbus定义在不同的波特率下，间隔时间是不一样的，
        所以就是3.5个字符的时间，波特率高，这个时间间隔就小，波特率低，这个时间间隔相应就大

        4800  = 7.297ms
        9600  = 3.646ms
        19200  = 1.771ms
        38400  = 0.885ms
    */
    uint32_t timeout;

    g_uart2_timeout = 0; 

    timeout = 35000000 / 115200;            /* 计算超时时间，单位us 35000000*/

//  printf("%x\t",_byte);
//  硬件定时中断，定时精度us，使用定时器2用于检测接收超时
    bsp_StartHardTimer(2, timeout, (void *)Uart2_RxTimeOut);

    if (g_tUart2.RxCount < S_RX_BUF_SIZE)
    {
        g_tUart2.RxBuf[g_tUart2.RxCount++] = _byte;
    }
}
