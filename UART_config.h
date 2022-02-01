/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	UART			***********************/
/**********************************************************************/
/**********************************************************************/
#ifndef _UART_CONFIG_H_
#define _UART_CONFIG_H_

/*Stop bits Selection:
 	 	 	 	 	  1- ONE_BIT
 	 	 	 	 	  2- TWO_BITS*/
#define STOP_BITS	ONE_BIT
/*Parity Control:
 	 	 	 	 1- ODD_PARITY
 	 	 	 	 2- EVEN_PARITY
 	 	 	 	 3- NO_PARITY*/
#define Parity		NO_PARITY
/*Transmission speed:
 	 	 	 	 	 1- NORMAL
 	 	 	 	 	 2- DOUBLE*/
#define TRANS_SPEED		NORMAL
/*Data bits Selection:
 	 	 	 	 	  1- FIVE_BITS
 	 	 	 	 	  2- SIX_BITS
 	 	 	 	 	  3- SEVEN_BITS
 	 	 	 	 	  4- EIGHT_BITS
 	 	 	 	 	  5- NINE_BITS*/
#define DATA_SEL	EIGHT_BITS
/*Interrupt control:
 	 	 	 	 	 1- ENABLE
 	 	 	 	 	 2- DISABLE*/
#define INTERR_CONTROL	DISABLE
/*Select Asynchronous or Synchronous:
 	 	 	 	 	 	 	 	 	 1- ASYNCHRONOUS
 	 	 	 	 	 	 	 	 	 2- SYNCHRONOUS*/
#define UART_MODE	ASYNCHRONOUS
/*IF MODE IS SYNCHRONOUS:
 	 	 	 	 	 	 1- TRANS_RIS
 	 	 	 	 	 	 2- TRANS_FAL*/
#define SYNCH_MODE	TRANS_RIS
/*Baud rate*/
#define BAUDRATE	51 //9600 bps
#endif
