/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse O_Stream enthaelt die Definition des << Operators fuer die     */
/* wichtigsten der vordefinierten Datentypen und realisiert somit die        */
/* bekannte Ausgabefunktion der C++ IO_Stream Bibliothek. Zur Zeit wird die  */
/* Darstellung von Zeichen, Zeichenketten und ganzen Zahlen unterstuetzt.    */
/* Ein weiterer << Operator erlaubt die Verwendung von Manipulatoren.        */
/*                                                                           */
/* Neben der Klasse O_Stream sind hier auch die Manipulatoren hex, dec, oct  */
/* und bin fuer die Wahl der Basis bei der Zahlendarstellung, sowie endl     */
/* fuer den Zeilenumbruch definiert.                                         */
/*****************************************************************************/

#include "object/o_stream.h"

/* Hier muesst ihr selbst Code vervollstaendigen */ 

O_Stream& O_Stream::operator<< (unsigned char c)
{
	put(c);
	return *this;
}
O_Stream& O_Stream::operator<< (char c) 
{
	put(c);
	return *this;
}


O_Stream& O_Stream::operator<< (unsigned short number)
{
	*this << (unsigned long)(number);
	return *this;
}
O_Stream& O_Stream::operator<< (short number)
{
	*this << long(number);
	return *this;
}
O_Stream& O_Stream::operator<< (unsigned int number)
{
	*this << (unsigned long)(number);
	return *this;
}
O_Stream& O_Stream::operator<< (int number)
{
	*this << long(number);
	return *this;
}
O_Stream& O_Stream::operator<< (unsigned long number)
{
	char buffer[sizeof(unsigned long)*8];
	int i = 0;
	while(number != 0 || i == 0)
	{
		int z = number%ziffern;
		if(z<10)
			buffer[i] = '0'+z;
		else
			buffer[i] = 'a'+(z-10);
		i++;
		number /= ziffern;
	}
	while(i)
	{
		i--;
		put(buffer[i]);
	}
	return *this;
}
O_Stream& O_Stream::operator<< (long number) 
{
	if(number<0)
	{
		put('-');
		*this << (unsigned long)(-number);
	}
	else
		*this << (unsigned long)(number);
	return *this;
}


O_Stream& O_Stream::operator<< (void* pointer) 
{
	int z = ziffern;
	if(pointer == 0)
		*this << "NULL";
	else
		*this << "0x" << hex << (unsigned long)pointer;
	ziffern = z;
	return *this;
}


O_Stream& O_Stream::operator<< (char* text) 
{
	while(*text)
	{
		put(*text);
		text++;
	}
	return *this;
}


O_Stream& O_Stream::operator<< (O_Stream& (*fkt) (O_Stream&)) 
{
	fkt(*this);
	return *this;
}

O_Stream& endl (O_Stream& os)
{
	os.put('\n');
	return os;
}
O_Stream& bin (O_Stream& os)
{
	os.ziffern = 2;
	return os;
}
O_Stream& oct (O_Stream& os)
{
	os.ziffern = 8;
	return os;
}
O_Stream& dec (O_Stream& os)
{
	os.ziffern = 10;
	return os;
}
O_Stream& hex (O_Stream& os)
{
	os.ziffern = 16;
	return os;
}
