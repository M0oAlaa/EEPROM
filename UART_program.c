/**********************************************************************/
/**********************************************************************/
/*****************		Author: Mohamed Alaa	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	UART			***********************/
/**********************************************************************/
/**********************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_register.h"
#include "UART_private.h"
#include "UART_config.h"
#include "UART_interface.h"

#include<util/delay.h>

void UART_init(void)
{
	uint8_t local_UCSRC=0;

	/*Select to write in UCSRC Register*/
	SET_BIT(local_UCSRC,UCSRC_URSEL);

	/*Stop bits Selection*/
#if STOP_BITS == ONE_BIT
	CLR_BIT(local_UCSRC,UCSRC_USBS);//Select one stop bit
#elif STOP_BITS == TWO_BITS
	SET_BIT(local_UCSRC,UCSRC_USBS);//Select two stop bits
#endif

	/*Parity Control*/
#if Parity == EVEN_PARITY
	CLR_BIT(local_UCSRC,UCSRC_UPM0);
	SET_BIT(local_UCSRC,UCSRC_UPM1);
#elif Parity == ODD_PARITY
	SET_BIT(local_UCSRC,UCSRC_UPM0);
	SET_BIT(local_UCSRC,UCSRC_UPM1);
#elif Parity == NO_PARITY
	CLR_BIT(local_UCSRC,UCSRC_UPM0);
	CLR_BIT(local_UCSRC,UCSRC_UPM1);
#endif

	/*Data bits Selection*/
#if DATA_SEL == FIVE_BITS
	CLR_BIT(local_UCSRC,UCSRC_UCSZ0);
	CLR_BIT(local_UCSRC,UCSRC_UCSZ1);
	CLR_BIT(UART_UCSRB,UCSRB_UCSZ2);
#elif DATA_SEL == SIX_BITS
	SET_BIT(local_UCSRC,UCSRC_UCSZ0);
	CLR_BIT(local_UCSRC,UCSRC_UCSZ1);
	CLR_BIT(local_UCSRB,UCSRB_UCSZ2);
#elif DATA_SEL == SEVEN_BITS
	CLR_BIT(local_UCSRC,UCSRC_UCSZ0);
	SET_BIT(local_UCSRC,UCSRC_UCSZ1);
	CLR_BIT(UART_UCSRB,UCSRB_UCSZ2);
#elif DATA_SEL == EIGHT_BITS
	SET_BIT(local_UCSRC,UCSRC_UCSZ0);
	SET_BIT(local_UCSRC,UCSRC_UCSZ1);
	CLR_BIT(UART_UCSRB,UCSRB_UCSZ2);
#elif DATA_SEL == NINE_BITS
	SET_BIT(local_UCSRC,UCSRC_UCSZ0);
	SET_BIT(local_UCSRC,UCSRC_UCSZ1);
	SET_BIT(UART_UCSRB,UCSRB_UCSZ2);
#endif

	/*UART MODE*/
#if UART_MODE == ASYNCHRONOUS
	CLR_BIT(local_UCSRC,UCSRC_UMSEL);
#elif UART_MODE == SYNCHRONOUS
	SET_BIT(UART_UCSRC,UCSRC_UMSEL);
	/*Select Action on Clock*/
#if SYNCH_MODE == TRANS_RIS
	CLR_BIT(UART_UCSRC,UCSRC_UCPOL);
#elif SYNCH_MODE == TRANS_FAL
	SET_BIT(UART_UCSRC,UCSRC_UCPOL);
#endif
#endif
	/*Accessing UCSRC Register*/
	UART_UCSRC=local_UCSRC;
	/*Interrupt control*/
#if INTERR_CONTROL == ENABLE
	/*Enable receive interrupt*/
	SET_BIT(UART_UCSRB,UCSRB_RXCIE);
	/*Enable Transmit interrupt*/
	SET_BIT(UART_UCSRB,UCSRB_TXCIE);
	/*Enable data register empty interrupt*/
	SET_BIT(UART_UCSRB,UCSRB_UDRIE);
#elif INTERR_CONTROL == DISABLE
	/*Disable receive interrupt*/
	CLR_BIT(UART_UCSRB,UCSRB_RXCIE);
	/*Disable Transmit interrupt*/
	CLR_BIT(UART_UCSRB,UCSRB_TXCIE);
	/*Disable data register empty interrupt*/
	CLR_BIT(UART_UCSRB,UCSRB_UDRIE);
#endif
	/*Baud rate*/
	/*Baud rate Selection = 9600 bit per second*/
	UART_UBRRL=BAUDRATE;

	/*Enable Transmission mode*/
	SET_BIT(UART_UCSRB,UCSRB_TXEN);
	/*Enable Receiver mode*/
	SET_BIT(UART_UCSRB,UCSRB_RXEN);
}

void UART_ASynchTransmitt(uint8_t u8_Tdata)
{

		/*Wait until the flag is set*/
		while((GET_BIT(UART_UCSRA,UCSRA_UDRE) == 0));

		/*Put the datat into data register*/
		UART_UDR=u8_Tdata;

}

uint8_t UART_AsynchSendStr(char* u8_Tdata)
{
	uint8_t local_u8Error=OK;//A local variable to check error
	uint8_t local_u8Index=0;//A local variable to check timeout
	/*If no data*/
	if(u8_Tdata == NULL)
	{
		local_u8Error= NOK;
	}
	else{
		/*iterate until the end of the string*/
		while(*(u8_Tdata+local_u8Index) != '\0')
		{
			/*Transmit it element by element*/
			UART_ASynchTransmitt(*(u8_Tdata+local_u8Index));
			local_u8Index++;
			/*delay for hardware error*/
			_delay_ms(50);
		}
	}
	return local_u8Error;
}

uint8_t UART_ASynchReceive(void)
{
	/*Waiting until the flag is set*/
	while(GET_BIT(UART_UCSRA,UCSRA_RXC)==0);
	/*return the data received*/
	return UART_UDR;
}

uint8_t UART_AsynchReceiveStr(char* u8_Tdata)
{
	uint8_t local_u8data=0;//local variable to hold data
	uint8_t local_u8Index=0;//iteration index
	/*Receive the data and assign it into variable*/
	local_u8data=UART_ASynchReceive();
	/*waiting until the received data be (enter) button*/
	while((local_u8data != '\n') && (local_u8data != '\r'))
	{
		/*Assign the received char into array*/
		*(u8_Tdata+local_u8Index)=local_u8data;
		local_u8Index++;
		/*delay for hardware error*/
		_delay_ms(50);
		local_u8data=UART_ASynchReceive();
	}
	*(u8_Tdata+local_u8Index)='\0';
	/*Return string size*/
	return local_u8Index;
}
