/* $Id: cgascr.cc 5834 2013-10-08 17:04:08Z os $ */

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             C G A _ S C R E E N                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse kann man auf den Bildschirm des PCs zugreifen.    */
/* Der Zugriff erfolgt direkt auf der Hardwareebene, d.h. ueber den Bild-    */
/* schirmspeicher bzw. die I/O-Ports der Grafikkarte.                        */
/*****************************************************************************/

#include "machine/cgascr.h"
#include "machine/cpu.h"

void CGA_Screen::show (int x, int y, char c, unsigned char attrib)
{
	char *CGA_START = (char*)0xb8000;
	char *pos = CGA_START + 2 *(x+y*80);
	*pos = c;
	*(pos+1) = attrib;
}
void CGA_Screen::setpos (int x, int y)
{
	IO_Port index(0x3d4);
	IO_Port data(0x3d5);
	int i = y*80+x;
	int index_bak = index.inb();
	index.outb(14);
	data.outb(i>>8);
	//if(index.inb() != 14)show(60,24,'A',0x0f);
	index.outb(15);
	data.outb(i);
	//if(index.inb() != 15)show(61,24,'B',0x0f);
	//index.outb(index_bak);
}
void CGA_Screen::getpos (int &x, int &y)
{
	IO_Port index(0x3d4);
	IO_Port data(0x3d5);
	int i = 0;
	int index_bak = index.inb();
	index.outb(14);
	i = data.inb() << 8;
	//if(index.inb() != 14)show(60,24,'C',0x0f);
	index.outb(15);
	i |= data.inb();
	//if(index.inb() != 15)show(60,24,'D',0x0f);
	x = i % 80;
	y = i / 80;
	//index.outb(index_bak);
}
void CGA_Screen::print (char* text, int length, unsigned char attrib)
{
	int x,y;
	getpos(x,y);
	for(int i=0;i<length;i++)
	{
		if(text[i] == '\n')
		{
			y++;
			x=0;
		}
		else
		{
			show(x,y,text[i],attrib);
			x++;
			if(x>=80)
			{
				x=0;
				y++;
			}
		}
		if(y>=25)
		{
			y--;
			scroll();
		}
	}
	setpos(x,y);
}

void CGA_Screen::scroll()
{
	char *CGA_START = (char*)0xb8000;
	for(int y=0;y<24;y++)
	{
		for(int x=0;x<80;x++)
		{
			char *pos1 = CGA_START + 2 *(x+y*80);
			char *pos2 = CGA_START + 2 *(x+(y+1)*80);
			*pos1 = *pos2;
			*(pos1+1) = *(pos2+1);
		}
	}
	for(int x=0;x<80;x++)
	{
		char *pos1 = CGA_START + 2 *(x+24*80);
		*pos1 = ' ';
		*(pos1+1) = 0x0f;
	}
}
