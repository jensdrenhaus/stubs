/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Schedulers.                                           */
/*****************************************************************************/



#include "thread/organizer.h"



Scheduler::Scheduler ()
{

}
		
void Scheduler::ready (Entrant& that)
{
	readyqueue.enqueue(&that);
}
			
void Scheduler::schedule ()
{
	Entrant* job = (Entrant*)readyqueue.dequeue();
	go(*job);
}
		
void Scheduler::exit ()
{
	
	dispatch(*((Entrant*)readyqueue.dequeue()));

}
			
void Scheduler::kill (Entrant& that)
{
	if(&that == active()){
		exit();
	}
	else{
			readyqueue.remove(&that);
	}
}
			
void Scheduler::resume ()
{
	readyqueue.enqueue((Entrant*)active());
	dispatch(*((Entrant*)readyqueue.dequeue()));
}
