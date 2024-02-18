/*
 * EXTI_reg.h
 *
 * Created: 9/12/2023 10:42:36 PM
 *  Author: mahmo
 */ 


#ifndef EXTI_REG_H_
#define EXTI_REG_H_


/*@brief MCU control register*/
#define MCUCR				*((volatile uint8*) 0x55)

/*Interrupt sense control*/
#define MCUCR_ISC00			   0u   
#define MCUCR_ISC01			   1u   
#define MCUCR_ISC10			   2u   
#define MCUCR_ISC11			   3u   

/*MCU control and status register*/
#define MCUCSR				*((volatile uint8*) 0x54)
#define MCUCSR_ISC2			6u

/*@brief Global interrupt control register */
#define GICR				*((volatile uint8*) 0x5B)   
#define GICR_INT1			7u							/*@brief INT1 control pin */
#define GICR_INT0			6u                          /*@brief INT0 control pin */
#define GICR_INT2			5u							/*@brief INT2 control pin */					
														




#endif /* EXTI_REG_H_ */