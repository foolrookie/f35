
/*基于TIM6定时器的系统调度器*/

#include "tim_scheduing.h"
#include "gpio_led_init.h"

TIM_HandleTypeDef Tim3initStruct;


static uint32_t system_time = 0;

/*init tim6*/
void tim3_init(void)
{   
    uint32_t sysclock = HAL_RCC_GetPCLK1Freq();

    Tim3initStruct.Instance = TIM3;
    Tim3initStruct.Init.Period = (1000 - 1);
    Tim3initStruct.Init.Prescaler = (((sysclock / 1000000) * 2) - 1);
    Tim3initStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
    Tim3initStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&Tim3initStruct);

    HAL_TIM_Base_Start_IT(&Tim3initStruct);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    __HAL_RCC_TIM3_CLK_ENABLE();

    HAL_NVIC_SetPriority(TIM3_IRQn,2,2);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&Tim3initStruct);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == (&Tim3initStruct))
    {
        system_time++;
    }
}

/*返回TIM3生成的系统时钟戳*/
uint32_t get_system_time(void)
{
    return system_time;
}