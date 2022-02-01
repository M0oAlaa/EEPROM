/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	TWI				***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_register.h"
#include "TWI_private.h"
#include "TWI_config.h"
#include "TWI_interface.h"

void TWI_MasterInit(void)
{
	/*Set clock freq to 400 kbps by TWBR=2 & TWPS=0*/
	TWI_TWBR=TWI_BitRate;

	/*Set Prescalar*/
#if TWI_PRESCALAR == PRE_ZERO
	CLR_BIT(TWI_TWSR,TWSR_TWPS0);
	CLR_BIT(TWI_TWSR,TWSR_TWPS1);
#elif TWI_PRESCALAR == PRE_ONE
	SET_BIT(TWI_TWSR,TWSR_TWPS0);
	CLR_BIT(TWI_TWSR,TWSR_TWPS1);
#elif TWI_PRESCALAR == PRE_TWO
	CLR_BIT(TWI_TWSR,TWSR_TWPS0);
	SET_BIT(TWI_TWSR,TWSR_TWPS1);
#elif TWI_PRESCALAR == PRE_THREE
	SET_BIT(TWI_TWSR,TWSR_TWPS0);
	SET_BIT(TWI_TWSR,TWSR_TWPS1);
#endif

	/*Set Master Address*/
	if(TWI_MASTADD != NULL)
	{
		TWI_TWAR=TWI_MASTADD<<1;//write in the MSB (7 bits)
	}

	/*Set global call*/
#if TWI_GENARALCALL == ENABLE
	SET_BIT(TWI_TWAR,TWAR_TWGCE);
#elif TWI_GENARALCALL == DISABLE
	CLR_BIT(TWI_TWAR,TWAR_TWGCE);
#endif

	/*Enable TWI*/
	SET_BIT(TWI_TWCR,TWCR_TWEN);
}

void TWI_SlaveInit(uint8_t u8_SlaveAddress)
{
	TWI_TWAR = (1<<u8_SlaveAddress);    // my address = MY_SLAVE_ADDRESS
	TWI_TWCR = (1<<TWCR_TWEN);                //enable I2C
	//	/*Set the slave address*/
	//	TWI_TWAR=u8_SlaveAddress<<1;
	//
	//	/*Enable TWI*/
	//	SET_BIT(TWI_TWCR,TWCR_TWEN);
}

TWI_ErrorStat TWI_startCond(void)
{
	/*initialize error element*/
	TWI_ErrorStat local_ErrorState=NO_ERROR;

	/*Send Start Condition*/
	SET_BIT(TWI_TWCR,TWCR_TWSTA);

	/*Clear the interrupt flag*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Enable TWI*/
	SET_BIT(TWI_TWCR,TWCR_TWEN);

	/*Wait until the previous operation is complete*/
	while((GET_BIT(TWI_TWCR,TWCR_TWINT)==0));

	while((TWI_TWSR & STATUS_MASK) != START_ACK);

	/*Check the status register*/
	if((TWI_TWSR & STATUS_MASK) != START_ACK)
	{
		local_ErrorState = StartCondError;
	}
	else
	{
		//do nothing
	}

	return local_ErrorState;
}

TWI_ErrorStat TWI_RepstartCond(void)
{
	/*initialize error element*/
	TWI_ErrorStat local_ErrorState=NO_ERROR;

	/*Send Start Condition*/
	SET_BIT(TWI_TWCR,TWCR_TWSTA);

	/*Clear the interrupt flag*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Wait until the previous operation is complete*/
	while((GET_BIT(TWI_TWCR,TWCR_TWINT)==0));

	while((TWI_TWSR & STATUS_MASK) != REP_START_ACK);

	/*Check the status register*/
	if((TWI_TWSR & STATUS_MASK) != REP_START_ACK)
	{
		local_ErrorState = REPStartCondError;
	}
	else
	{
		//do nothing
	}

	return local_ErrorState;
}

TWI_ErrorStat TWI_SendSlaveAddWrite(uint8_t u8_SlaveAddress)
{
	/*initialize error element*/
	TWI_ErrorStat local_ErrorState=NO_ERROR;

	/*Set the slave address in the 7 MSB of data register TWDR*/
	TWI_TWDR = u8_SlaveAddress<<1;

	/*Send write to the bus*/
	CLR_BIT(TWI_TWDR,TWDR_TWD0);

	/*Clear the start condition bit*/
	CLR_BIT(TWI_TWCR,TWCR_TWSTA);

	/*Clear the interrupt flag*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Wait until the previous operation is complete*/
	while((GET_BIT(TWI_TWCR,TWCR_TWINT)==0));

	while((TWI_TWSR & STATUS_MASK) != SLAVE_ADD_AND_WR_ACK);

	/*Check the status register*/
	if((TWI_TWSR & STATUS_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		local_ErrorState = SlaveADD_WriteError;
	}
	else
	{
		//do nothing
	}

	return local_ErrorState;
}

TWI_ErrorStat TWI_SendSlaveAddRead(uint8_t u8_SlaveAddress)
{
	/*initialize error element*/
	TWI_ErrorStat local_ErrorState=NO_ERROR;

	/*Set the slave address in the 7 MSB of data register TWDR*/
	TWI_TWDR = u8_SlaveAddress<<1;

	/*Send Read to the bus*/
	SET_BIT(TWI_TWDR,TWDR_TWD0);

	/*Clear the start condition bit*/
	CLR_BIT(TWI_TWCR,TWCR_TWSTA);

	/*Clear the interrupt flag*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Wait until the previous operation is complete*/
	while((GET_BIT(TWI_TWCR,TWCR_TWINT)==0));

	while((TWI_TWSR & STATUS_MASK) != SLAVE_ADD_AND_RD_ACK);
	/*Check the status register*/
	if((TWI_TWSR & STATUS_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		local_ErrorState = SlaveADD_ReadError;
	}
	else
	{
		//do nothing
	}
	return local_ErrorState;
}

TWI_ErrorStat TWI_MasterSendData(uint8_t u8_Data)
{
	/*initialize error element*/
	TWI_ErrorStat local_ErrorState=NO_ERROR;

	/*Send data*/
	TWI_TWDR = u8_Data;

	/*Clear the interrupt flag*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Wait until the previous operation is complete*/
	while((GET_BIT(TWI_TWCR,TWCR_TWINT)==0));

	while((TWI_TWSR & STATUS_MASK) != MSTR_WR_BYTE_ACK);

	/*Check the status register*/
	if((TWI_TWSR & STATUS_MASK) != MSTR_WR_BYTE_ACK)
	{
		local_ErrorState = MasterSendData;
	}
	else
	{
		//do nothing
	}

	return local_ErrorState;
}

TWI_ErrorStat TWI_MasterReadDataWithACK(uint8_t* u8_Data)
{
	/*initialize error element*/
	TWI_ErrorStat local_ErrorState=NO_ERROR;

	/*Enable Acknowledge*/
	SET_BIT(TWI_TWCR,TWCR_TWEA);

	/*Clear the interrupt flag*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Wait until the previous operation is complete*/
	while((GET_BIT(TWI_TWCR,TWCR_TWINT)==0));

	/*Check the status register*/
	if((TWI_TWSR & STATUS_MASK) != MSTR_RD_BYTE_WITH_ACK)
	{
		local_ErrorState = MasterReceiveDatawithACK;
	}
	else
	{
		/*Receive data*/
		*u8_Data = TWI_TWDR;
	}

	return local_ErrorState;
}

TWI_ErrorStat TWI_MasterReadDataNACK(uint8_t* u8_Data)
{
	uint8_t local_ErrorState=NO_ERROR;

	/*Clear the interrupt flag*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);

	/*Wait until the previous operation is complete*/
	while((GET_BIT(TWI_TWCR,TWCR_TWINT)==0));

	/*Check the status register*/
	if((TWI_TWSR & STATUS_MASK) != MSTR_RD_BYTE_WITH_NACK)
	{
		local_ErrorState = MasterReceiveDataNAK;
	}
	else
	{
		/*Receive data*/
		*u8_Data = TWI_TWDR;
	}

	return local_ErrorState;
}

void TWI_slave_check_slave_address_received_with_write_req(void)
{
	TWI_TWCR = (1<<TWCR_TWEA) | (1<<TWCR_TWEN) | (1<<TWCR_TWINT);       // enable acknowledgment after receive, Enable TWI, Clear TWI interrupt flag
	while((GET_BIT(TWI_TWCR,TWCR_TWINT)) == 0 );                    // Wait for TWINT flag
	while((TWI_TWSR & STATUS_MASK) != SLAVE_ADD_RCVD_WR_REQ) ;
}

void TWI_slave_check_slave_address_received_with_read_req(void)
{
	TWI_TWCR = (1<<TWCR_TWEA) | (1<<TWCR_TWEN) | (1<<TWCR_TWINT); // enable acknowledgment after receive, Enable TWI, Clear TWI interrupt flag
	while((GET_BIT(TWI_TWCR,TWCR_TWINT)) == 0 );             // Wait for TWINT flag
	while((TWI_TWSR & STATUS_MASK) != SLAVE_ADD_RCVD_RD_REQ);
}

uint8_t TWI_slave_read_byte(void)
{
	TWI_TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEA) | (1<<TWCR_TWEN);     // Clear TWI interrupt flag,Get enable acknowledgment, Enable TWI
	while((GET_BIT(TWI_TWCR,TWCR_TWINT))== 0 );                   // Wait for TWINT flag
	while((TWI_TWSR & STATUS_MASK) != SLAVE_DATA_RECEIVED);
	return TWI_TWDR;
}

void TWI_slave_write_byte(uint8_t byte)
{
	TWI_TWDR = byte;
	TWI_TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEA) | (1<<TWCR_TWEN);         // Clear TWI interrupt flag,Get enable acknowledgment, Enable TWI
	while((GET_BIT(TWI_TWCR,TWCR_TWINT)) == 0 );                     // Wait for TWINT flag
	while((TWI_TWSR & STATUS_MASK) != SLAVE_BYTE_TRANSMITTED);    // Data byte in TWDR has been transmitted
}

void TWI_SendStopCond(void)
{
	//TWI_TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN) | (1<<TWCR_TWSTO); // Clear TWI interrupt flag, Put stop condition on SDA,Enable TWI
	/*Set the stop condition bit*/
	SET_BIT(TWI_TWCR,TWCR_TWSTO);

	/*Clear the interrupt flag*/
	SET_BIT(TWI_TWCR,TWCR_TWINT);
}
