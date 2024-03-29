/****************************************************************************/
/****************************************************************************/
/********************** Autor: Mahmoud Magdy ********************************/
/**********************  File: KPD_config.h ********************************/
/**********************    Version: 1.00     ********************************/
/****************************************************************************/
/****************************************************************************/



#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KDP_u8NO_PRESSED_KEY_VAL            0xff

#define KPD_u8ROW_NUM                       4u
#define KPD_u8COL_NUM                       3u
							               
#define KPD_u8ROW_PORT                      DIO_u8PORTC
#define KPD_u8ROW0_PIN                      DIO_u8PIN0
#define KPD_u8ROW1_PIN                      DIO_u8PIN1
#define KPD_u8ROW2_PIN                      DIO_u8PIN2
#define KPD_u8ROW3_PIN                      DIO_u8PIN3
							               
#define KPD_u8COL_PORT                      DIO_u8PORTC
#define KPD_u8COL0_PIN                      DIO_u8PIN4
#define KPD_u8COL1_PIN                      DIO_u8PIN5
#define KPD_u8COL2_PIN                      DIO_u8PIN6
#define KPD_u8COL3_PIN                      DIO_u8PIN7
							               
#define KPD_u8BUTTON_ARR                    {{1,2,3},{4,5,6},{7,8,9},{'*',0,'#'}}
#endif /* KPD_CONFIG_H_ */