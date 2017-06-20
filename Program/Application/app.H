#ifndef _APP_H
#define _APP_H

/******** EEPORM CONFIGURATION BEGINS ****************/
#define EEPROM_DISPLAY				0
/******** EEPORM CONFIGURATION ENDS ****************/

/* LCD CONFIGURATION */
#define LCD_DDR           	   		DDRB 
#define LCD_DATA_PORT          		PORTB
#define LCD_ENABLE_PIN        		PB3 
#define LCD_REGISTER_SELECT_PIN     PB2
#define DISPLAY_INIT				1
#define LCD_NSCRL					3
#define FLOAT_T0_STRING				1
#define DECIMAL_PRECISION			100

/******** LCD CONFIGURATION ENDS ****************/

/* BUZZER: CONFIGURATION */
#define	BUZ_DDR						DDRC
#define	BUZ_PORT					PORTC
#define	BUZ_PIN						PC1
#define OFF_TIME					100
/******** BUZZER CONFIGURATION ENDS ****************/

/* LED: CONFIGURATION */
#define	LED_DDR			DDRC
#define	LED_PORT		PORTC
#define	LED_PIN			PC0
#define OFF_TIME		100
/******** LED CONFIGURATION ENDS ****************/

/* GSM: CONFIGURATION */
#define GSM_RFID_DDR			DDRC
#define GSM_RFID_PORT			PORTC
#define	GSM_RFID_PIN			PC3

#define GSMEn()					do {										\
									GSM_RFID_PORT |= _BV(GSM_RFID_PIN);		\
									dlyms(500);								\
								} while(0)

#define RFIDEn()				do {										\
									GSM_RFID_PORT &= ~(_BV(GSM_RFID_PIN));		\
									dlyms(500);								\
								} while(0)


#define MSG_START					""
#define MSG_END						". Automated SMS By: S-ATM A & SS"


/******** SMS CONFIGURATION ****************/
/*comment below line for release*/
#define TESTING

#ifdef TESTING
	#define UPhNum		 "9980237552"
	#define	MPhNum		 "9980237552"
#else
	#define UPhNum		 "8867320909"
	#define	MPhNum		 "9535178113"
#endif
/******** SMS CONFIGURATION ENDS ****************/


/******** MOTOR CONFIGURATION   ****************/
#define MOT_PORT			PORTC
#define MOT_DDR				DDRC
#define MOT1_AN				PC4
#define MOT1_CA				PC5
#define MOT2_AN				PC6
#define MOT2_CA				PC7

/******** MOTOR CONFIGURATION ENDS  ****************/

/******** PWM CONFIGURATION  *******************/
#define PWM_DDR				DDRD
#define PWM_PIN				PD7
/********  PWM CONFIGURATION ENDS **************/

/******* SERVO CONFIGURATION ********************/
#define SERVO_DDR			DDRD
#define SERVO_PORT			PORTD
#define SERVO1				PD5
/******** SERVO CONFIGURATION ENDS **************/

/********* RELAY CONFIGURATION ******************/
#define RELAY_PORT			PORTC
#define RELAY_DDR			DDRC
#define RELAY				PC7
/********* RELAY CONFIGURATION ENDS ************/

/*********  RFID CONFIGURATION   ***************/
//#define		DISPLAY_TAGNUMBER		0
/*********** RFID CONFIGURATION ENDS ***********/

#endif
