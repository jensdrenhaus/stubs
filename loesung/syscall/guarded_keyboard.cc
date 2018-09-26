/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ K E Y B O A R D                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zur Tastatur.                                   */
/*****************************************************************************/

#include "guard/secure.h"
#include "syscall/guarded_keyboard.h"

Guarded_Keyboard keyboard;

Key Guarded_Keyboard::getkey ()
{
		Secure secure;
		return Keyboard::getkey();
}

bool Guarded_Keyboard::isPressed(unsigned char key)
{
	Secure secure;
	return Keyboard_Controller::isPressed(key);
}

void Guarded_Keyboard::clearBuffer()
{
	Secure secure;
	Keyboard::clearBuffer();
}
