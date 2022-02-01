/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	TWI				***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/
#ifndef _TWI_INTERFACE_H_
#define _TWI_INTERFACE_H_

typedef enum
{
	NO_ERROR=0,
	StartCondError,
	REPStartCondError,
	SlaveADD_WriteError,
	SlaveADD_ReadError,
	MasterSendData,
	MasterReceiveDatawithACK,
	MasterReceiveDataNAK,
	SlaveReceivedData,
	SlaveReadAcknowledge,
	SlaveReceivedDataAcknowledge
}TWI_ErrorStat;

void TWI_MasterInit(void);

void TWI_SlaveInit(uint8_t u8_SlaveAddress);

TWI_ErrorStat TWI_startCond(void);

TWI_ErrorStat TWI_RepstartCond(void);

TWI_ErrorStat TWI_SendSlaveAddWrite(uint8_t u8_SlaveAddress);

TWI_ErrorStat TWI_SendSlaveAddRead(uint8_t u8_SlaveAddress);

TWI_ErrorStat TWI_MasterSendData(uint8_t u8_Data);

TWI_ErrorStat TWI_MasterReadDataWithACK(uint8_t* u8_Data);

uint8_t TWI_MasterReadDataNACK(uint8_t* u8_Data);

void TWI_slave_check_slave_address_received_with_write_req(void);

void TWI_slave_check_slave_address_received_with_read_req(void);

uint8_t TWI_slave_read_byte(void);

void TWI_slave_write_byte(uint8_t byte);

void TWI_SendStopCond(void);

#endif
