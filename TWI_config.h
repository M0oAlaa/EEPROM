/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	TWI				***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/
#ifndef _TWI_CONFIG_H_
#define _TWI_CONFIG_H_

/*Set master Address*/
#define TWI_MASTADD		1
/*Write the bit rate according to equation in data sheet*/
#define TWI_BitRate		0x02

/*Select PRESCALAR:
 	 	 	 	 	1- PRE_ZERO
 	 	 	 	 	2- PRE_ONE
 	 	 	 	 	3- PRE_TWO
 	 	 	 	 	4- PRE_THREE*/
#define TWI_PRESCALAR	PRE_ZERO

/*Enable or Disable thw general call:
 	 	 	 	 	 	 	 	 	 1- ENABLE
 	 	 	 	 	 	 	 	 	 2- DISABLE*/
#define TWI_GENARALCALL		DISABLE
#endif
