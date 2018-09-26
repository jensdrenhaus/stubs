/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Semaphore werden zur Synchronisation von Threads verwendet.               */
/*****************************************************************************/

#ifndef __Semaphore_include__
#define __Semaphore_include__

#include "meeting/waitingroom.h"

/* Hier muesst ihr selbst Code vervollstaendigen */ 
        
class Semaphore : public Waitingroom
/* Hier muesst ihr selbst Code vervollstaendigen */         
 {
private:
    Semaphore (const Semaphore &copy); // Verhindere Kopieren
    int counter;
public:
	Semaphore (int c);
	void p ();
	bool try_wait ();
	void v ();
	void wait (){p();}
	void signal (){v();}
 };

#endif
