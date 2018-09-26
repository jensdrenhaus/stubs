/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          D I S P A T C H E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Dispatcher.                                           */
/* Der Dispatcher verwaltet den life-Pointer, der die jeweils aktive         */
/* Koroutine angibt. mit go() wird der life Pointer initialisiert und die    */
/* erste Koroutine gestartet, alle weiteren Kontextwechsel werden mit        */
/* dispatch() ausgeloest. active() liefert den life Pointer zurueck.         */
/*****************************************************************************/

#include "thread/dispatch.h"


Dispatcher::Dispatcher ()
{
	current = 0;
}

void Dispatcher::go (Coroutine& first)
{	
		current = &first;
		current->go();
	
}
		
void Dispatcher::dispatch (Coroutine& next)
{
		 Coroutine* tmp = current;
		 current = &next;
	     tmp->resume(next);
	     
	
}
		
Coroutine* Dispatcher::active()
{
	return current;
}
