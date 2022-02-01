/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	UART			***********************/
/**********************************************************************/
/**********************************************************************/
#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_

/*Declaration of initialization of UART function*/
void UART_init(void);

/*Declaration of synchronous transmit*/
uint8_t UART_SynchTransmitt(uint8_t u8_Tdata);

/*Declaration of Asynchronous transmit*/
void UART_AsynchTransmitt(uint8_t u8_Tdata);

/*Declaration of synchronous receive*/
unint16_t UART_SynchReceive(void);

/*Declaration of Asynchronous receive*/
uint8_t UART_ASynchReceive(void);

/*Declaration of Asynchronous transmit string*/
uint8_t UART_AsynchSendStr(char* u8_Tdata);

/*Declaration of Asynchronous receive string*/
uint8_t UART_AsynchReceiveStr(char* u8_Tdata);

#endif
