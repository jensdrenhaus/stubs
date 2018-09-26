/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Schedulers.                                           */
/*****************************************************************************/

#ifndef __schedule_include__
#define __schedule_include__

#include "thread/dispatch.h"
#include "object/queue.h"
#include "thread/entrant.h"
        
class Scheduler : public Dispatcher       
 {
private:
      Scheduler (const Scheduler &copy); // Verhindere Kopieren
      Queue readyqueue;
      
	public:
		Scheduler ();
		
		void ready (Entrant& that);
			
		void schedule ();
		
		void exit ();
			
		void kill (Entrant& that);
			
		void resume ();
 
 };


#endif
