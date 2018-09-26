/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Semaphore werden zur Synchronisation von Threads verwendet.               */
/*****************************************************************************/

#include "meeting/semaphore.h"
#include "syscall/guarded_organizer.h"
#include "thread/customer.h"

Semaphore::Semaphore (int c){
	counter = c;
}
	
void Semaphore::p (){
	if(counter > 0){counter--;}
	else{
		organizer.block(*(Customer*)organizer.active(), *this);
	}	
}

void Semaphore::v (){
	Customer* temp;	
	temp = (Customer*)Queue::dequeue();
	if(temp != 0){
		organizer.wakeup(*temp);
	}
	else{counter++;}
	
}



bool Semaphore::try_wait (){
	if(counter > 0)
	{
		counter--;
		return true;
	}
	else 
		return false;
}
