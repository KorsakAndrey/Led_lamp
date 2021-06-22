#ifndef WS2812_h
#define WS2812_h
#include <at89x52.h>
#ifndef pin_out
#define pin_out p0.0
#endif

/*Timings Set0 and Set1 tested only on 27.000 Mhz*/

void Transmit(unsigned long int c);
void Set0( void );
void Set1( void );
void rse(int delay);

void Transmit(unsigned long int c)
{
unsigned long int a = 0x1000000;
unsigned int i;
	for (i=0;i<24;i++){
		a=a>>1;	
		if ((c&a)==0x00000000) {
			Set0();				
			}  else {
			Set1(); 
		} 
	}
}

void Set0( void ) 
{
__asm
setb pin_out
clr pin_out
__endasm;

}

void Set1( void ) 
{
__asm
setb pin_out
nop
nop
clr pin_out
__endasm;
}

void rse(int delay)
{
unsigned long i;
__asm
clr pin_out
__endasm;
	for(i=0;i<delay;i++){
		__asm
		nop
		nop
		nop
		__endasm;	
	}
}

#endif 