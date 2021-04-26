#ifndef _CBUF_H_
#define _CBUF_H_

#include "main.h"

#define CBUF_MAX_SIZE       4096

typedef struct cbuf
{
    uint32_t _put_index;
    uint32_t _get_index;    
    uint8_t _buffer[CBUF_MAX_SIZE];
    uint32_t buf_actual_size; //缓冲区的实际使用大小，最大不超过CBUF_MAX_SIZE
}cbuf_t;

/*缓冲区初始化*/
void Cbuf_Init(cbuf_t *cbuff);
/*设置缓冲区大小*/
void Set_Cbuf_Size(cbuf_t *cbuff , uint32_t set_size);
/*获取缓冲区长度*/
uint32_t Cbuf_Len(cbuf_t *cbuff);
/*写入缓冲区一个字节*/
void Cbuf_Push(cbuf_t *cbuff , uint8_t ch);
/*读出缓冲区一个字节*/
uint8_t Cbuf_Pop(cbuf_t *cbuff);
/*判断缓冲区是否写满*/
uint8_t Cbuf_Isfull(cbuf_t *cbuff);
/*判断缓冲区是否为空*/
uint8_t Cbuf_Isempty(cbuf_t *cbuff);




#endif