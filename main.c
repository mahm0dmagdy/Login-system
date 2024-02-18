/*
 * Login_EXTI.c
 *
 * Created: 11/24/2023 10:48:47 PM
 * Author : mahmo
 */ 
#include <util/delay.h>

#include "Library/\BIT_MATH.h"
#include "Library/STD_TYPES.h"
#include "Library/defines.h"

#include "MCAL/1- DIO/DIO_interface.h"
#include "MCAL/2- PORT/PORT_interface.h"
#include "MCAL/3- EXTI/EXTI_interface.h"
#include "MCAL/4- GIE/GIE_interface.h"

#include "ECUAL/1- CLCD/CLCD_interface.h"
#include "ECUAL/2- KPD/KPD_interface.h"
#include "ECUAL/2- KPD/KPD_config.h"

void Motor(void);
void stop(void);
int main(void)
{
	uint8 Local_SSD[10]= {0b0111111,0b0000110,0b1011011,0b1001111,0b1100110,0b1101101,0b1111101,0b0000111,0b1111111,0b1101111};
	uint8 Local_u8PressedKey = KDP_u8NO_PRESSED_KEY_VAL;
	uint8 Local_u8IdCounter;
	uint8 Local_u8PassCounter;
	uint8 Local_u8RightPassCounter;
	uint8 Local_u8TriesCounter=1;

	uint16 Local_u16Id=0;
	uint16 Local_u16Pass=0;
	uint16 Local_u16RightPass=0;
	
	PORT_voidInit();
	CLCD_voidInit();
	
	EXTI_voidinit0();
	EXTI_u8SetCallBack(EXTI_u8INT0,&stop);
	GIE_voidEnableGlobal();
	
		CLCD_u8Send_String("Welcome");
		_delay_ms(1500);
		CLCD_voidSendCmd(1);
	
		while(Local_u8TriesCounter < 4 ){
	    DIO_u8SetPortValue(DIO_u8PORTB,Local_SSD[Local_u8TriesCounter]);
	    Local_u8IdCounter = 0;
	    Local_u8PassCounter = 0;
	    
	    CLCD_u8Send_String("Enter ID:");
	    while(Local_u8IdCounter < 4){
		    Local_u8PressedKey = KPD_u8GetPressedKey();
		    if(Local_u8PressedKey != KDP_u8NO_PRESSED_KEY_VAL){
			    CLCD_voidSendNumber(Local_u8PressedKey);
			    Local_u16Id = Local_u16Id*10 + Local_u8PressedKey;
			    Local_u8IdCounter++;
		    }
	    }
	    
	    for(Local_u8RightPassCounter = 0 ; Local_u8RightPassCounter < 4 ; Local_u8RightPassCounter++ ){
		    Local_u16RightPass = Local_u16RightPass*10 + (Local_u16Id%10) ;
		    Local_u16Id = Local_u16Id /10;
	    }
	    
	    CLCD_voidGoToXY(0,1);
	    CLCD_u8Send_String("Enter Pass:");
	    while(Local_u8PassCounter < 4){
		    Local_u8PressedKey = KPD_u8GetPressedKey();
		    if(Local_u8PressedKey != KDP_u8NO_PRESSED_KEY_VAL){
			    CLCD_voidSendNumber(Local_u8PressedKey);
			    Local_u16Pass = Local_u16Pass*10 + Local_u8PressedKey;
			    _delay_ms(500);
			    CLCD_voidGoToXY(11+Local_u8PassCounter,1);
			    CLCD_voidSendData('*');
			    Local_u8PassCounter++;
		    }
	    }
	    Local_u8TriesCounter++;
	    if(Local_u16RightPass != Local_u16Pass && Local_u8TriesCounter < 4){
		    CLCD_voidSendCmd(1);
		    CLCD_u8Send_String("Wrong input,");
		    CLCD_voidGoToXY(0,1);
		    CLCD_u8Send_String("Please try again");
		    _delay_ms(2000);
		    CLCD_voidSendCmd(1);
		   Local_u16Id=0;
		   Local_u16Pass=0;
		   Local_u16RightPass=0;
	    }
	    
	    else{
		    break;
	    }
    }
    if(Local_u8TriesCounter == 4 && Local_u16RightPass != Local_u16Pass){
	    CLCD_voidSendCmd(1);
	    CLCD_voidGoToXY(0,0);
	    CLCD_u8Send_String("Locked,");
	    CLCD_voidGoToXY(0,1);
	    CLCD_u8Send_String("Call 13659");
    }
    else{
		while(1){
			Motor();
			}		
	    }
	}
	
	void stop(void){
		while(1){
		CLCD_voidSendCmd(1);
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
		DIO_u8SetPortValue(DIO_u8PORTB,0x00);
		    }
		}
	/*
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void) {
	while(1){
	CLCD_voidSendCmd(1);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
	DIO_u8SetPortValue(DIO_u8PORTB,0x00);
	}
}
*/
void Motor(void){
	CLCD_voidSendCmd(1);
	CLCD_u8Send_String("Motor on,");
	CLCD_voidGoToXY(0,1);
	CLCD_u8Send_String("Rotating CCW");
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_HIGH);
	_delay_ms(3000);

	CLCD_voidSendCmd(1);
	CLCD_u8Send_String("Motor stop");
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
	_delay_ms(1500);
	
	CLCD_voidSendCmd(1);
	CLCD_u8Send_String("Motor on,");
	CLCD_voidGoToXY(0,1);
	CLCD_u8Send_String("Rotating CW");
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
	_delay_ms(3000);
	
	CLCD_voidSendCmd(1);
	CLCD_u8Send_String("Motor stop");
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
	_delay_ms(1500);
}