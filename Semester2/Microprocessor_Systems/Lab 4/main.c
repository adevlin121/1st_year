/* This program presents a counter on a 4 digit seven segment display.
 * The display is refreshed in the by the systick interrupt service
 * routine that runs at 1kHz.
 * 
 * Operation:
 * A global array represents the 'video' memory for the display.  
 * In order to display a number, the DisplayNumber function must be 
 * called which breaks the number into its component digits and then
 * translates these to the bit patterns that cause the appropriate
 * display segments to turn on. These patterns are stored in the 
 * global DisplayMemory array.
 * The SysTick handler takes the contents of the DisplayMemory
 * array and copies them out to the port pins driving the display 
 * segments.  Each display digit is activated in turn, its are 
 * turned on (or not) and there is a slight pause which fools our
 * eyes into thinking that all display digits are on all of the time.
 * 
 * Wiring.
 * The display is wired to Port 0.  Segments are wired to bits 5-11
 * and digits are wired to bits 1-4.  The display in question is a 
 * 4 digit common cathode device.  In order to place a number on a 
 * digit the segments must be driven high (through a resistor to limit
 * current) and the common cathode for that display must be driven
 * low.  
 * 
 */

#include "lpc111x.h"
// Association of bits to segments due to wiring
// Display is on Port 0
#define SEG_A BIT5
#define SEG_B BIT6
#define SEG_C BIT7
#define SEG_D BIT8
#define SEG_E BIT9
#define SEG_F BIT10
#define SEG_G BIT11
#define DIG_1 BIT1
#define DIG_2 BIT2
#define DIG_3 BIT3
#define DIG_4 BIT4
volatile int milliseconds=0;
int seconds = 0;
int minutes = 24;

void initSysTick(void);

// Digit segment definitions
const short digits[]={ 																						\
						SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F        ,\
					  SEG_B | SEG_C                                			,\
					  SEG_A | SEG_B |         SEG_D | SEG_E |         SEG_G,\
					  SEG_A | SEG_B | SEG_C | SEG_D |       	        SEG_G,\
					          SEG_B | SEG_C |                 SEG_F | SEG_G,\
					  SEG_A |         SEG_C | SEG_D |         SEG_F | SEG_G,\
					  SEG_A |         SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,\
					  SEG_A | SEG_B | SEG_C                                ,\
					  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,\
					  SEG_A | SEG_B | SEG_C | SEG_D |         SEG_F | SEG_G,\
					   SEG_D | SEG_E | SEG_F | SEG_G,\
					  SEG_A |  SEG_E | SEG_F | SEG_G,\
					  SEG_A | SEG_B | SEG_C |  SEG_E | SEG_F | SEG_G,\
					   SEG_E |  SEG_G ,\
					   SEG_C ,\
					    SEG_C |  SEG_E |  SEG_G,\
						SEG_B | SEG_C | SEG_D |  SEG_F | SEG_G,\
						 SEG_C | SEG_D | SEG_E,\
						 SEG_A |  SEG_D | SEG_E | SEG_F ,\
						 SEG_A | SEG_D | SEG_E | SEG_F | SEG_G ,\
						  SEG_C | SEG_D | SEG_E |  SEG_G\
						 
					  };
volatile int DisplayMemory[4];


void SysTick(void)
{
	
	static int DigitNumber=1;
	milliseconds++;
	if (milliseconds>=10)
	{	
		// A second has passed to reset the millisecond counter
		milliseconds = 0;
		seconds--;
	}
	if (seconds<0&&minutes>=1)
	{
		
		minutes--;
		seconds = 59;
		
	}
	switch (DigitNumber) 
	{
		case 1: {
			// Turn on (make low) the desired digit and blank all segments
			GPIO0DATA = DIG_1 | DIG_2 | DIG_3;
			// Set the relevant segment bits
			GPIO0DATA |= DisplayMemory[0];
			// Wait for display to light up
			break;
		}
		case 2: {
			// Turn on (make low) the desired digit and blank all segments
			GPIO0DATA = DIG_1 | DIG_2 | DIG_4;
			// Set the relevant segment bits
			GPIO0DATA |= DisplayMemory[1];
			// Wait for display to light up
			break;
		}
		case 3: {
			// Turn on (make low) the desired digit and blank all segments
			GPIO0DATA = DIG_1 | DIG_3 | DIG_4;
			// Set the relevant segment bits
			GPIO0DATA |= DisplayMemory[2];
			// Wait for display to light up
			break;
		}
		case 4: {
			// Turn on (make low) the desired digit and blank all segments
			GPIO0DATA = DIG_2 | DIG_3 | DIG_4;
			// Set the relevant segment bits
			GPIO0DATA |= DisplayMemory[3];
			// Wait for display to light up
			break;
		}
	}
	DigitNumber++;
	if (DigitNumber > 4)
		DigitNumber = 1;
}
void initSysTick()
{
	
	// The systick timer is driven by a 48MHz clock
	// Divide this down to achieve a 1ms timebase
	// Divisor = 48MHz/1000Hz
	// Reload value = 48000-1
	// enable systick and its interrupts
	SYST_CSR |=(BIT0+BIT1+BIT2); 
	SYST_RVR=48000-1; // generate 1 millisecond time base
	SYST_CVR=5;
	enable_interrupts();
}
void delay(int dly)
{
  while (dly--);
}

void DisplayNumber(int Number)
{
	DisplayMemory[0]=digits[Number % 10];
	Number = Number / 10;
	DisplayMemory[1]=digits[Number % 10];
	Number = Number / 10;
	DisplayMemory[2]=digits[Number % 10];
	Number = Number / 10;
	DisplayMemory[3]=digits[Number % 10];
}
void DisplayFart()
{
	//t
	DisplayMemory[0]=digits[10];
	//r
	DisplayMemory[1]=digits[13];
	//a
	DisplayMemory[2]=digits[12];
	//this is where f goes
	DisplayMemory[3]=digits[11];
}
void DisplayIn()
{
	//bl
	DisplayMemory[0]=digits[21];
	//bl
	DisplayMemory[1]=digits[21];
	//n
	DisplayMemory[2]=digits[15];
	//i
	DisplayMemory[3]=digits[14];
}
void DisplayYour()
{
	//bl
	DisplayMemory[0]=digits[13];
	//bl
	DisplayMemory[1]=digits[17];
	//n
	DisplayMemory[2]=digits[20];
	//i
	DisplayMemory[3]=digits[16];
}
void DisplayFace()
{
	//e
	DisplayMemory[0]=digits[19];
	//c
	DisplayMemory[1]=digits[18];
	//a
	DisplayMemory[2]=digits[12];
	//f
	DisplayMemory[3]=digits[11];
}
void DisplayBlank()
{
	//e
	DisplayMemory[0]=digits[21];
	//c
	DisplayMemory[1]=digits[21];
	//a
	DisplayMemory[2]=digits[21];
	//f
	DisplayMemory[3]=digits[21];
}
void ConfigPins()
{
	SYSAHBCLKCTRL |= BIT6 + BIT16; // Turn on clock for GPIO and IOCON 
	// Make all of the segment and digit bits outputs
	GPIO0DIR = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | DIG_1 | DIG_2 | DIG_3 | DIG_4;
	// Turn off (make high) all display digits
	GPIO0DATA = DIG_1 | DIG_2 | DIG_3  | DIG_4;
	// Make Port 0 bit 5 behave as a generic output port (open drain)
	IOCON_PIO0_5 |= BIT8;
	// Make Port 0 bit 10 behave as a generic I/O port
	IOCON_SWCLK_PIO0_10  = 1; 
	// Make Port 0 bit 11 behave as a generic I/O port
	IOCON_R_PIO0_11  = 1; 
	
}

int main()
{	
	int count=1250000;
	initSysTick();
	ConfigPins();
	while(1) 
	{	
		
		DisplayNumber(minutes*100+seconds);
		if (minutes+seconds==0)
		{
			
			while(1)
			{
				if(count>1000000)
				{
					DisplayFart();
					count--;
				}
				else if(count>750000 && count<=1000000)
				{
					DisplayIn();
					count--;
					
				}
				else if(count>500000 && count<=7500000)
				{
					DisplayYour();
					count--;
				}
				else if(count>250000 && count<=500000)
				{
					DisplayFace();
					count--;
					if(count<245000)
					{
						count=1250000;
					}
					
				}
				
			}
		}
		
	}    
}