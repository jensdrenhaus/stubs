/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          O R G A N I Z E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein Organizer ist ein spezieller Scheduler, der zusaetzlich das Warten    */
/* von Threads (Customer) auf Ereignisse erlaubt.                            */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */ 
#include "thread/organizer.h"


void Organizer::block (Customer& customer, Waitingroom& waitingroom){
		customer.waiting_in(&waitingroom);
		waitingroom.enqueue(&customer);
		Scheduler::kill(customer);
}
void Organizer::wakeup (Customer& customer){
	customer.waiting_in(0);
	ready(customer);
}
void Organizer::kill (Customer& that){
	if(that.waiting_in()){
		that.waiting_in()->remove(&that);
	}
	else{Scheduler::kill(that);}
		
}
