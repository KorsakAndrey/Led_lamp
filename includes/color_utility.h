#ifndef color_utility_h
#define color_utility_h

/*Part of library microLED from Alex Gyver - https://github.com/GyverLibs/microLED*/

char fade8(char x, char b);
unsigned long int mRGB(int r, int g, int b);		/* RGB 255, 255, 255*/
unsigned long int mWheel(int color,char bright);		 /*цвета 0-1530 + яркость */
unsigned long int mWheel8(char c, char br);	/* цвета 0-255 + яркость */




/* ============================================== COLOR FUNC ===============================================*/
char fade8(char x, char b)
{
long f = x * (b+1);
f = f>>8;
	return f;
}

unsigned long int mRGB(int r, int g, int b) 
{
unsigned long int mergeRGB = (g<<8) | r;
mergeRGB = (mergeRGB<<8) | b;
	return mergeRGB;
}

unsigned long int mWheel(int color, char bright) {
	int r, g, b;
	if (color <= 255) {           			  /* красный макс, зелёный растёт*/
		r = 255;
		g = color;
		b = 0;
	}
	else if (color > 255 && color <= 510) {   /* зелёный макс, падает красный*/
		r = 510 - color;
		g = 255;
		b = 0;
	}
	else if (color > 510 && color <= 765) {   /* зелёный макс, растёт синий*/
		r = 0;
		g = 255;
		b = color - 510;
	}
	else if (color > 765 && color <= 1020) {  /* синий макс, падает зелёный*/
		r = 0;
		g = 1020 - color;
		b = 255;
	}
	else if (color > 1020 && color <= 1275) { /* синий макс, растёт красный*/
		r = color - 1020;
		g = 0;
		b = 255;
	}
	else if (color > 1275 && color <= 1530) { /* красный макс, падает синий*/
		r = 255;
		g = 0;
		b = 1530 - color;
	}
	if (bright != 255) {
		r = fade8(r, bright);
		g = fade8(g, bright);
		b = fade8(b, bright);
	}
	return mRGB(r, g, b);
}

unsigned long int mWheel8(char c, char br)
{
char rd, gr, bl;
char shift;
	if (c > 170) {
		shift = (c - 170) * 3;
		rd = shift;
		gr = 0;
		bl = 255 - shift;
	}else if (c > 85) {
		shift = (c - 85) * 3;
		rd = 0;
		gr = 255 - shift;
		bl = shift;
	}else {
		shift = c * 3;
		rd = 255 - shift;
		gr = shift;
		bl = 0;
	}
	if (br != 255) {
		rd = fade8(rd, br);
		gr = fade8(gr, br);
		bl = fade8(bl, br);
	}
	return mRGB(rd, gr, bl);
}

#endif
