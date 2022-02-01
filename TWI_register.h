/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	TWI				***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/
#ifndef _TWI_REGISTER_H_
#define _TWI_REGISTER_H_

#define TWI_TWCR			*((volatile uint8_t*)0x56)
#define TWCR_TWINT				7
#define TWCR_TWEA				6
#define TWCR_TWSTA				5
#define TWCR_TWSTO				4
#define TWCR_TWWC				3
#define TWCR_TWEN				2
#define TWCR_TWIE				0

#define TWI_TWAR			*((volatile uint8_t*)0x22)
#define TWAR_TWGCE				0

#define TWI_TWSR			*((volatile uint8_t*)0x21)
#define TWSR_TWPS0				0
#define TWSR_TWPS1				1

#define TWI_TWBR			*((volatile uint8_t*)0x20)
#define TWI_TWDR			*((volatile uint8_t*)0x23)
#define TWDR_TWD0				0

#endif
