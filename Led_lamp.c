#define pin_out p1.2  /*data out pin for asembler (pX.n)*/
#define Touch P1_1    /*sensor in pin for "C" (PX_n)*/
#define Leds 12       /*number of leds*/

#include <at89x52.h>
#include "WS2812.h"
#include "color_utility.h"

int col = 1;                 /*start collor*/
char bright = 100;           /*set bright*/
unsigned long int mas[Leds]; /*leds array*/
char f = 1;                  /*turn flag*/
char mode = 0;               /*work mode*/
char touched = 0;            /*touch flag*/
int counter = 0;	     /*touch counter*/

void change_mode(void)
{
	if(mode == 0){mode=1;return;}
	else if (mode == 1)	{mode=2;return;}
	else if (mode == 2)	{mode=3;return;}
	else 	{mode=0;return;}
}

char change_bright(void)
{
	if (bright == 100)	{bright=250;return 0;}
	if (bright == 250)	{bright=100;return 0;}
}

void off(void)
{
	char i;
	for(i=0;i<Leds;i++) mas[i] = 0x000000;	
}

void white(void)
{
	char i;
	for(i=0;i<Leds;i++)mas[i] = 0xC0C0C0;	
}

void snake(void)
{	
	char i;
	for(i=0;i<Leds;i++){
		mas[i] = mWheel(col,bright);
		f = f ? (col++ < 1300) : (col-- == 1);
	}
	if(f==1 & col>1) col = col-(Leds-1);
	if(f==0) col = col+(Leds-1);
}	

void rainbow(void)
{
	static char counter = 0;
	int i;
	for (i = 0; i < Leds; i++) {
		mas[i] = mWheel8(counter + i * 255 / Leds,bright);   /*counter смещает цвет*/
	}
	counter += 3;
}

void main()
{
	char i;
	while(1)
	{
		/*====EXTERNAL CONTROL====*/
		if (Touch == 0) touched = 0;	
		if (Touch & touched == 0){
			change_mode();
			touched = 1;
		}
		if (counter++ == 100 & Touch) counter = change_bright();
		if (counter > 0 & Touch == 0) counter = 0;
		
		/*====SELECT MODE====*/
		switch (mode ) {
			case 0:
			  off();
			  break;
			case 1:
			  white();
			  break;
			case 2:
			  snake();
			  break;
			case 3:
			  rainbow();
			  break;
			default:
			   break;
		}
		
		/*====TRANSMIT DATA====*/	
		rse(1500);			/*use for restart before transmit and delay*/
		for(i=0;i<Leds;i++){
			Transmit(mas[i]);	/*transmit array*/
		}
  	}
}
