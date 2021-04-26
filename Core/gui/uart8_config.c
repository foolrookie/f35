#include "uart8_config.h"

UART_HandleTypeDef huart8;
DMA_HandleTypeDef hdma_uart8_rx;
DMA_HandleTypeDef hdma_uart8_tx;

void uart8_init(void)
{
    huart8.Instance = UART8;
    huart8.Init.BaudRate = BAUDRATE;
    huart8.Init.HwFlowCtl = UART_HWCONTROL_NONE; //硬件流控制
    huart8.Init.Mode = UART_MODE_TX_RX;
    huart8.Init.OverSampling = UART_OVERSAMPLING_8;
    huart8.Init.Parity = UART_PARITY_NONE;       //无奇偶校验
    huart8.Init.StopBits = UART_STOPBITS_1;
    huart8.Init.WordLength = UART_WORDLENGTH_8B;
    
    if (HAL_UART_Init(&huart8) != HAL_OK)
    {
        Error_Handler();
    }
}




void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
    GPIO_InitTypeDef GPIO_Initstruct;

    if(uartHandle->Instance == UART8)
    {
        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_UART8_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();


        GPIO_Initstruct.Alternate = GPIO_AF8_UART8;
        GPIO_Initstruct.Mode = GPIO_MODE_AF_PP;
        GPIO_Initstruct.Pin = UART8_TX_PIN | UART8_RX_PIN;
        GPIO_Initstruct.Pull = GPIO_PULLDOWN;
        GPIO_Initstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(GPIOE, &GPIO_Initstruct);

        hdma_uart8_rx.Instance = DMA1_Stream6;
        hdma_uart8_rx.Init.Channel = DMA_CHANNEL_5;
        hdma_uart8_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_uart8_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        // hdma_uart8_rx.Init.MemBurst = DMA_MBURST_SINGLE; //存储器单次突发模式
        hdma_uart8_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_uart8_rx.Init.MemInc = DMA_MINC_ENABLE;     //存储器地址自加
        hdma_uart8_rx.Init.Mode = DMA_CIRCULAR;
        // hdma_uart8_rx.Init.PeriphBurst = DMA_PBURST_SINGLE;
        hdma_uart8_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_uart8_rx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_uart8_rx.Init.Priority = DMA_PRIORITY_HIGH;
        HAL_DMA_Init(&hdma_uart8_rx);

        __HAL_LINKDMA(uartHandle, hdmarx, hdma_uart8_rx);

        hdma_uart8_tx.Instance = DMA1_Stream0;
        hdma_uart8_tx.Init.Channel = DMA_CHANNEL_5;
        hdma_uart8_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_uart8_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        // hdma_uart8_tx.Init.MemBurst = DMA_MBURST_SINGLE;
        hdma_uart8_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_uart8_tx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_uart8_tx.Init.Mode = DMA_NORMAL;
        // hdma_uart8_tx.Init.PeriphBurst = DMA_PBURST_SINGLE;
        hdma_uart8_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_uart8_tx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_uart8_tx.Init.Priority = DMA_PRIORITY_LOW;
        HAL_DMA_Init(&hdma_uart8_tx);

        __HAL_LINKDMA(uartHandle, hdmatx, hdma_uart8_tx);

        HAL_NVIC_EnableIRQ(UART8_IRQn);
        HAL_NVIC_SetPriority(UART8_IRQn, 3, 3);


        HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
        HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 2, 3);
    
        HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
        HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 2, 3);

        
    }
}


void UART8_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart8);
}

void DMA1_Stream0_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_uart8_tx);
}

void DMA1_Stream6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_uart8_rx);
}