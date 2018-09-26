/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C U S T O M E R                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein Thread, der auf ein Ereignis warten kann.                             */
/*****************************************************************************/

#ifndef __customer_include__
#define __customer_include__

#include "thread/entrant.h"
class Waitingroom;
/* Hier muesst ihr selbst Code vervollstaendigen */ 
        
class Customer: public Entrant
/* Hier muesst ihr selbst Code vervollstaendigen */         
 {
private:
    Customer (const Customer &copy); // Verhindere Kopieren
    Waitingroom* room;
public:
	Customer (void* tos):Entrant(tos){}
	void waiting_in (Waitingroom *w){room = w;}
	Waitingroom* waiting_in (){return room;}
};

#endif
