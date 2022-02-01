/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	HAL				***********************/
/*****************		SWC:	EEPROM			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/
#include "STD_TYPES.h"

#include "TWI_interface.h"

#include "EEPROM_private.h"
#include "EEPROM_config.h"
#include "EEPROM_interface.h"

#include <util/delay.h>

void EEPROM_init(void)
{
	/*initialize MCU controls EEPROM as Master to write or read from it*/
	TWI_MasterInit();
}

void EEPROM_SendData(uint8_t u8_Data,unint16_t u16_EEPROM_Address)
{

	/*Call Start Condition to start communication*/
	TWI_startCond();

	/*Select page and Write in TWI to send data*/
	TWI_SendSlaveAddWrite(EEPROM_ADDRESS_MASK);

	/*Send EEPROM target address*/
	TWI_MasterSendData(u16_EEPROM_Address>>8);

	/*Send EEPROM target address*/
	TWI_MasterSendData((uint8_t)u16_EEPROM_Address);

	/*Send Data to EEPROM*/
	TWI_MasterSendData(u8_Data);

	/*Stop Condition to stop communication*/
	TWI_SendStopCond();

}

void EEPROM_ReadData(unint16_t EEPROM_Address, uint8_t* u8_data)
{
	/*Start Condition to start communication*/
	TWI_startCond();

	/*Select page and Write in TWI to send data*/
	TWI_SendSlaveAddWrite(EEPROM_ADDRESS_MASK);

	/*Send EEPROM target address*/
	TWI_MasterSendData(EEPROM_Address>>8);

	/*Send EEPROM target address*/
	TWI_MasterSendData((uint8_t)EEPROM_Address);

	/*Send repeated start*/
	TWI_RepstartCond();

	/*Select page and Read in TWI to send data*/
	TWI_SendSlaveAddRead(EEPROM_ADDRESS_MASK);

	/*Read Data*/
	TWI_MasterReadDataNACK(&u8_data);

	/*Stop Condition to stop communication*/
	TWI_SendStopCond();
}
