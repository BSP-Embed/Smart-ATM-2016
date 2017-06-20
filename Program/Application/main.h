#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define INTDDR					DDRD
#define INTPORT					PORTD
#define INT0_PIN				PD2
#define INT1_PIN				PD3

#define IR_SENS_DDR				DDRD
#define IR_SENS_PORT			PORTD
#define IR_SENS_PPIN			PIND
#define IR_PIN					PD3

#define ALED_DDR				DDRD
#define ALED_PORT				PORTD
#define GLED_PIN				PD6
#define RLED_PIN				PD5

//DEFINE CONSTANT
#define MAX_TRN_CNT				3
#define MIN_INT					5
#define MAX_INT					100

//DEFINE MACROS

#define StartTmr()			TCCR0  	|= _BV(CS01)
#define StopTmr()			TCCR0  	&= ~_BV(CS01)

#define FlashLED()			do {												\
								ALED_PORT |= _BV(RLED_PIN) | _BV(GLED_PIN);		\
								dlyms(250);										\
								ALED_PORT &= ~(_BV(RLED_PIN) | _BV(GLED_PIN));	\
								dlyms(250);										\
							} while (FALSE)
							
#define GLEDOn()			ALED_PORT |= _BV(GLED_PIN); ALED_PORT &= ~_BV(RLED_PIN)
#define RLEDOn()			ALED_PORT |= _BV(RLED_PIN); ALED_PORT &= ~_BV(GLED_PIN)

#define ShutOpen()			do {				\
								mot2on();		\
								dlyms(3000);	\
								mot2off();		\
							} while (FALSE)		
							
#define DispCash()			do {				\
								mot1on();		\
								dlyms(500);	\
								mot1off();		\
							} while (FALSE)	

#define ReadAMT(x)			read_pass(0,(x))

//FUNCTION PROTOTYPES
static void		init		(void);
static void 	disptitl 	(void);
static void 	tmr1init	(void);
static void 	EXTINTinit	(void);
static void		varinit		(void); 
static int8u	VeriPass	(char *pass);
static void		tran		(void);

#endif
