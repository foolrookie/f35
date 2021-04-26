#ifndef _UART8_CONFIG_H_
#define _UART8_CONFIG_H_

#include "main.h"

#define BAUDRATE        115200
#define UART8_PORT      GPIOE
#define UART8_TX_PIN    GPIO_PIN_1
#define UART8_RX_PIN    GPIO_PIN_0


void uart8_init(void);

#endif