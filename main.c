#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "TWI_interface.h"

#include "EEPROM_interface.h"

#include "util/delay.h"
uint8_t Check_sentData(uint8_t* data,uint8_t* Order);

unint16_t convert_string_toNum(uint8_t* str);

void main(void)
{
	uint8_t local_u8UARTRead[50];
	uint8_t local_u8UARTReceiveRead[50];
	uint8_t local_u8UARTconvertRead;
	uint8_t local_u8WRITE[]="WRITE";
	uint8_t local_u8READ[]="READ";
	uint8_t local_u8CheckRead;
	uint8_t local_u8EEPROM_Read;
	uint8_t u8_data;
	UART_init();
	EEPROM_init();

	UART_AsynchReceiveStr(&local_u8UARTRead);
	local_u8CheckRead=Check_sentData(&local_u8UARTRead,&local_u8WRITE);
	if(local_u8CheckRead==OK)
	{
		UART_AsynchSendStr("Write Address:\r\n");
		UART_AsynchReceiveStr(&local_u8UARTReceiveRead);
		local_u8UARTconvertRead=convert_string_toNum(&local_u8UARTReceiveRead);
		UART_AsynchSendStr("OK1\r\n");
		u8_data=UART_ASynchReceive();
		EEPROM_SendData(u8_data,local_u8UARTconvertRead);
		UART_AsynchSendStr("OK2\r\n");
	}
	else if(local_u8CheckRead==NOK)
	{
		UART_AsynchSendStr("NOT Write\r\n");
	}

	local_u8CheckRead=Check_sentData(&local_u8UARTRead,&local_u8READ);
	if(local_u8CheckRead==OK)
	{
		UART_AsynchSendStr("OK\r\n");
		EEPROM_ReadData(local_u8UARTconvertRead,&local_u8EEPROM_Read);
		UART_AsynchSendStr("Data Stored is:\r\n");
		UART_AsynchSendStr(&local_u8EEPROM_Read);
	}
	else if(local_u8CheckRead==NOK)
	{
		UART_AsynchSendStr("NOT Read");
	}
	while(1)
	{

	}
}

uint8_t Check_sentData(uint8_t* data,uint8_t* Order)
{
	uint8_t local_u8Return=NOK;
	uint8_t local_u8counter=0;
	while(*(Order+local_u8counter) != '\0')
	{
		if(*(Order+local_u8counter) == *(data+local_u8counter))
		{
			local_u8Return=OK;
		}
		else
		{
			local_u8Return=NOK;
			break;
		}
		local_u8counter++;
	}
	return local_u8Return;
}

unint16_t convert_string_toNum(uint8_t* str)
{
  unint16_t result = 0;
  uint8_t index = 0;
  uint8_t size = 0;
  uint8_t digit = 0;
  while (str[size] != '\0' && str[size] != '\n' && str[size] != '\r')
  {
    size++;
  }
  for (index = 0; index < size; index++)
  {
    result *= 10;
    digit = str[index] - '0';
    result = result + digit;
  }

  return result;
}
