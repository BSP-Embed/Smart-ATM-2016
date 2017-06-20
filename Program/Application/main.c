#include "main.h"

const char *MSG[] = {	"Your high security password for the transaction is:",
						"Your Transaction is completed. To know balance Dial CC",
						"Person is in dangerous condition. Please take immediate action at canara bank  ATM, VidyaNagar, Mandya",
						"No Money in ATM, VidyaNagar, Mandya"
					};

struct  {
	volatile int8u PIR:1;
	volatile int8u NoMny:1;
	volatile int8u PTmr:1;
	volatile int8u LOff:1;
	volatile int8u Tran:1;
}Flag;

extern int8u lcdptr;
volatile extern int8u OTP[5];

int main(void)
{
	
	init();
	
	while (TRUE) {
		
		switch (readtag()) {
			case 1: 
					lcdclrr(1);
					beep(1,150);
					if (Flag.Tran == TRUE) {
						lcdws("    Pallavi");
						SendOTP(UPhNum,MSG[0]);
						tran();
					} else {
						lcdclrr(1);
						lcdws("Your Tran Bloc'd");
						beep(1,500);
						dlyms(500);
						disptitl();
					}
					
					break;
			case 2:
					lcdclrr(1);
					lcdws("  UnAuthorised");
					beep(1,250);
					dlyms(1000);
					disptitl();
					break;
		}
		
		if (IR_SENS_PPIN & _BV(IR_PIN)) {
			GLEDOn();
			Flag.NoMny = TRUE;
		} else {
			if (Flag.NoMny) {
				RLEDOn();
				GSMEn();
				GSMsndmsg(MPhNum, MSG[3]);
				Flag.NoMny = FALSE;
				disptitl();
			}
		}
	
		sleep();
	}
	return 0;
}

static void init(void)
{
	char pass[5];
	
	buzinit();
	beep(2,100);
	
	GSM_RFID_DDR  |= _BV(GSM_RFID_PIN);
	GSM_RFID_PORT &= ~_BV(GSM_RFID_PIN);
	
	ALED_DDR |= _BV(RLED_PIN) | _BV(GLED_PIN);
	ALED_PORT &= ~(_BV(RLED_PIN) | _BV(GLED_PIN));
		
	lcdinit();
	ledinit();
	motorinit();			
	uartinit();
	EXTINTinit();
	chkEEPROM();
	GSMEn();
	GSMinit();
	tmr1init();
	PWMinit();
	varinit(); 
	disptitl();
	PWMDC(MIN_INT);
	sei();
	StartTmr();
	beep(1,100);
}

static void varinit(void) 
{
	Flag.Tran= TRUE;
	Flag.PIR = FALSE;
	Flag.NoMny = TRUE;	
	Flag.PTmr = FALSE;
	Flag.LOff = FALSE;
}

static void EXTINTinit(void)
{
	INTDDR 	&= ~_BV(INT0_PIN);
	INTPORT |= _BV(INT0_PIN);
	
	GICR |= _BV(INT0) ;			//ENABLE EXTERNAL INTERRUPT
	MCUCR |= _BV(ISC01);		//FALLING EDGE INTERRUPT

}
static void disptitl(void)
{
	lcdclr();
	lcdws(" S-ATM ACC & SS");
}
		
static void tmr1init(void)
{
	TCNT1H   = 0xD3;
	TCNT1L   = 0x00;
	TIMSK   |= _BV(TOIE1);			//ENABLE OVERFLOW INTERRUPT
	TCCR1A   = 0x00;					
	TCCR1B  |= _BV(CS10) | _BV(CS11); /* PRESCALAR BY 16 */
}

/* overflows at every 100msec */
ISR(TIMER1_OVF_vect) 
{ 
	static int8u i,j,k;

	TCNT1H = 0xD3;
	TCNT1L = 0x00;
	
	if (++i >= 50)
		i = 0;
	
	switch(i) {
		case 0: case 2: ledon(); break;
		case 1: case 3: ledoff(); break;
	} 
	
	if (Flag.PTmr == TRUE && ++j >= 100) {
		Flag.LOff = TRUE;
		Flag.PTmr = FALSE;
		j = 0;
		k = MAX_INT;
	}
	
	if (Flag.LOff) {
		 k -= 5;
		if (k > 10)
			PWMDC(k);
		else
			Flag.LOff = FALSE;
	}
	
}
ISR(INT0_vect) 
{ 
	Flag.PIR = TRUE;
	PWMDC(MAX_INT);
	Flag.PTmr = TRUE;
	Flag.LOff = FALSE;
	
	GICR |= _BV(INT0);
}
static void tran(void)
{
	char pass[5];
	static int8u i = 0;
	
	lcdclrr(1);
	lcdws("E OTP:");
	read_pass(1,pass);
	switch (VeriPass(pass)) {
		case 1:
				lcdclrr(1);
				lcdws("Enter Amt: ");
				ReadAMT(pass);
				DispCash();
				lcdclrr(1);
				lcdws("  Collect CASH");
				dlyms(2000);
				lcdclrr(1);
				lcdws("   THANK YOU!");
				GSMEn();
				GSMsndmsg(UPhNum, MSG[1]);
				disptitl();
				i = 0;
				break;
		case 2:
				buzon();
				ShutOpen();
				GSMEn();
				GSMsndmsg(MPhNum, MSG[2]);
				lcdclrr(2);
				lcdws("**ATM BLOCKED***");
				for (;;) 
					FlashLED();
				break;	
				
		default:
				lcdclrr(1);
				lcdws("Invalid Password");
				beep(2,250);
				dlyms(500);
				if (++i < MAX_TRN_CNT) 
					tran();
				else {
					lcdclrr(1);
					lcdws("Transa'n BLOCKED");
					beep(2,500);
					Flag.Tran = FALSE;
					disptitl();
				}
				break;
	}
}

static int8u VeriPass(char *pass)
{
	if (verpass(OTP,pass))
		return 1;
	else {
		reverse(OTP);
		if (verpass(OTP,pass)) 
			return 2;
		reverse(OTP);
	}
	
	return 0;
}