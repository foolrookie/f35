#ifndef _DEBUG_DATA_H_ 
#define _DEBUG_DATA_H_

#include "main.h"

extern UART_HandleTypeDef huart8;
extern DMA_HandleTypeDef hdma_uart8_rx;
extern DMA_HandleTypeDef hdma_uart8_tx;

#define RX_BUF_MAX   16

/*debug_printf_dma*/
void debug_printf_dma(const char *__restrict__ __format, ...);

/*开启一次DMA 接收*/
void uart8_receive_init(void);

/*用于获取DMA不满足触发条件的数据*/
void get_rxcbuf_data(void);


void uart8_transmit(void);
#endif