#ifndef _GPIO_LED_INIT_H_
#define _GPIO_LED_INIT_H_

#include "main.h"

#define GPIO_R_PORT GPIOE
#define GPIO_G_PORT GPIOF

#define GPIO_R_PIN GPIO_PIN_11
#define GPIO_G_PIN GPIO_PIN_14



/*led init*/
void gpio_led_init(void);


#endif  