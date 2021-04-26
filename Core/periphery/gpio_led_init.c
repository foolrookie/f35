#include "gpio_led_init.h"


/*led init led_g PF14 led_r PE11*/
void gpio_led_init(void)
{   
    GPIO_InitTypeDef GPIOE_Structinit;
    GPIO_InitTypeDef GPIOF_Structinit;

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    GPIOE_Structinit.Mode = GPIO_MODE_OUTPUT_PP;
    GPIOE_Structinit.Pin = GPIO_R_PIN;
    GPIOE_Structinit.Pull = GPIO_PULLDOWN;
    GPIOE_Structinit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIO_R_PORT, &GPIOE_Structinit);

    GPIOF_Structinit.Mode = GPIO_MODE_OUTPUT_PP;
    GPIOF_Structinit.Pin = GPIO_G_PIN;
    GPIOF_Structinit.Pull = GPIO_PULLDOWN;
    GPIOF_Structinit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIO_G_PORT, &GPIOF_Structinit);

    HAL_GPIO_WritePin(GPIO_R_PORT, GPIO_R_PIN, 0);
    HAL_GPIO_WritePin(GPIO_G_PORT, GPIO_G_PIN, 1);
}


