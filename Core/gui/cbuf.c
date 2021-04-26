#include "cbuf.h"


/*缓冲区初始化*/
void Cbuf_Init(cbuf_t *cbuff)
{
    cbuff->_get_index = 0;
    cbuff->_put_index = 0;

    cbuff->buf_actual_size = CBUF_MAX_SIZE; //初始化时缓冲区设置为最大    
}

/*设置缓冲区大小*/
void Set_Cbuf_Size(cbuf_t *cbuff , uint32_t set_size)
{
    if(set_size <= CBUF_MAX_SIZE)
    {
        cbuff->buf_actual_size = set_size;
    }
    else
    {
        cbuff->buf_actual_size = CBUF_MAX_SIZE;
    }        
}

/*获取缓冲区长度*/
uint32_t Cbuf_Len(cbuf_t *cbuff)
{
    return (cbuff->_put_index - cbuff->_get_index) % (cbuff->buf_actual_size);
}

/*写入缓冲区一个字节*/
void Cbuf_Push(cbuf_t *cbuff , uint8_t ch)
{
    (cbuff->_buffer)[(cbuff->_put_index ++ ) % cbuff->buf_actual_size] = ch;
}

/*读出缓冲区一个字节*/
uint8_t Cbuf_Pop(cbuf_t *cbuff)
{     
     return (cbuff->_buffer)[(cbuff->_get_index ++ ) % cbuff->buf_actual_size];
}

/*判断缓冲区是否写满*/
uint8_t Cbuf_Isfull(cbuf_t *cbuff) //返回1表示满
{
    uint8_t len = Cbuf_Len(cbuff);
    return  (len == cbuff->buf_actual_size)? 1:0;
}

/*判断缓冲区是否为空*/
uint8_t Cbuf_Isempty(cbuf_t *cbuff) //返回1表示空
{
    uint8_t len = Cbuf_Len(cbuff);
    return  (len == 0)? 1:0;
}
