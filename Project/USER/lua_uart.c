#include "stdio.h"
#include "stm32f10x.h"
#include "lua_uart.h"

typedef int FILEHANDLE;


const char __stdin_name[150];
const char __stdout_name[150];
const char __stderr_name[150];
void Uart1_Init(int Bandrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
    /***TXD**/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /***RXD**/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /********初始化串口*******/
    USART_InitStructure.USART_BaudRate = Bandrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
    USART_Init(USART1, &USART_InitStructure);
    /********使能UART4****/
    USART_Cmd(USART1, ENABLE);
    /*******开中断*********/
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /*******设置嵌套中断优先级***********/
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	
}

FILEHANDLE _sys_open(const char *name, int openmode) {
	return 0;
}

int _sys_close(FILEHANDLE fh) {
	return 0;
}

int _sys_write(FILEHANDLE fh, const unsigned char *buf, unsigned len, int mode) {
	return 0;
}

int _sys_read(FILEHANDLE fh, unsigned char*buf, unsigned len, int mode) {
	return 0;
}

//检查句柄是否为终端
int _sys_istty(FILEHANDLE fh) {
	return 0;
}

int _sys_seek(FILEHANDLE fh, long pos) {
	return 0;
}

//刷新句柄关联的缓冲区
int _sys_ensure(FILEHANDLE fh) {
	return 0;
}

 

//返回文件当前长度
long _sys_flen(FILEHANDLE fh) {
	return 0;
}

void _sys_exit(int status) {
	//while(1);
}

int _sys_tmpnam(char *name, int fileno, unsigned maxlength) {
	return 0;
}

//将一个字符写入控制台
void _ttywrch(int ch) {
	
}

int remove(const char *filename) {
	return 0;
}

char *_sys_command_string(char *cmd, int len) {
	return NULL;
}

int fputc(int ch, FILE *f)  
{
    USART1->DR = (unsigned char) ch;
    /* Loop until the end of transmission */  
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {
    }
    
    return ch;  
}