#ifndef _TIM_SCHEDUING_H_
#define _TIM_SCHEDUING_H_

#include "main.h"


/*init tim6*/
void tim3_init(void);
/*返回TIM3生成的系统时钟戳*/
uint32_t get_system_time(void);

#endif
