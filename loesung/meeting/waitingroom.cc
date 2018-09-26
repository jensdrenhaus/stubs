/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Liste von Threads, die auf ein Ereignis warten.                           */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */ 
#include "meeting/waitingroom.h"
#include "syscall/guarded_organizer.h"


void Waitingroom::remove (Customer* customer){
		Queue::remove(customer);
}
Waitingroom::~Waitingroom (){
		Customer* temp;
		do{
			temp = (Customer*)Queue::dequeue();
			if(temp != 0){
				organizer.wakeup(*temp);
			}
		}while(temp != 0);
}
