/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

#ifndef __application_include__
#define __application_include__

#include "syscall/thread.h"
class Application : public Thread
 
 {
private:
    Application (const Application &copy); // Verhindere Kopieren
	char stack[4096];

public:

	Application(): Thread(stack+4096)
	{
	}
	void action();
 };

#endif
