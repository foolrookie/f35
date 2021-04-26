#include "debug_data.h"
#include "uart8_config.h"
#include "cbuf.h"

#include "stdarg.h"
#include "stdlib.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "stdint.h"

uint8_t rx_buf[RX_BUF_MAX] = {};


static cbuf_t uart8_rx_buf; //接收缓冲区
static cbuf_t uart8_tx_buf; //发送缓冲区


/*debug_printf_dma*/
void debug_printf_dma(const char *__restrict__ __format, ...)   
{
    va_list arg;
    va_start(arg, __format);

    char tx_buf[256] = {0};
    int len = vsnprintf(tx_buf, 256, __format, arg);
    va_end(arg);

    for(int i = 0; i < len; i++)
    {
        Cbuf_Push(&uart8_tx_buf, tx_buf[i]);
    }
}


/*开启一次DMA 接收 并且初始化接收数组*/
void uart8_receive_init(void)
{
    HAL_UART_Receive_DMA(&huart8, (uint8_t *)rx_buf, RX_BUF_MAX);
    Cbuf_Init(&uart8_rx_buf);
    Cbuf_Init(&uart8_tx_buf);
}


/*串口接收完成中断服务函数*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &huart8)
    {
        for(int i = 0; i < RX_BUF_MAX; i++)
        {
            Cbuf_Push(&uart8_rx_buf, rx_buf[i]);
        }
    }
}

/*用于从rxbuf获取小于16位的数据*/
void get_rxcbuf_data(void)
{
    int len = RX_BUF_MAX - __HAL_DMA_GET_COUNTER(&hdma_uart8_rx);
    if(len !=0)
    {
        HAL_UART_DMAStop(&huart8);
        for(int i = 0; i < len; i++)
        {
            Cbuf_Push(&uart8_rx_buf,rx_buf[i]);
        }
        HAL_UART_Receive_DMA(&huart8, (uint8_t *)rx_buf, RX_BUF_MAX);
    }
}

void uart8_transmit(void)
{
    int len = uart8_tx_buf._put_index - uart8_tx_buf._get_index;
    static uint8_t tx_buf[255] = {};
    if(len != 0)
    {
        for(int i = 0; i < len; i++)
        {
            tx_buf[i] = Cbuf_Pop(&uart8_tx_buf);
        }
        HAL_UART_Transmit_DMA(&huart8, (uint8_t *)tx_buf, len);
    }
}





