/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse koennen Aktivitaeten, die einen kritischen        */
/* Abschnitt betreffen, der mit einem Guard-Objekt geschuetzt ist, mit       */
/* Unterbrechungsbehandlungsroutinen synchronisiert werden, die ebenfalls    */
/* auf den kritischen Abschnitt zugreifen.                                   */
/*****************************************************************************/
#include "guard.h"
#include "machine/cpu.h"

#include "device/cgastr.h"
	Guard guard;

	Guard::Guard ()
	{
		
	}
	
	void Guard::leave()
	{	
		cpu.disable_int();
		Chain *e = queue.dequeue();
		
		while(e)
		{
			((Gate*)e)->queued(false);
			cpu.enable_int();
			((Gate*)e)->epilogue();
			cpu.disable_int();
		    e = queue.dequeue();

		}
		
		retne();
		
		cpu.enable_int();
	}
	
	void Guard::relay(Gate* item)
	{
		
		
		if(!item->queue())
		{
			item->queued(true);
			queue.enqueue(item);
		}
	
		if(avail())
		{
			enter();
			leave();
		}
				
		/*if(avail())
		{
			enter();
			cpu.enable_int();
			item->epilogue();
		}
		else if(!item->queue())
		{
			item->queued(true);
			queue.enqueue(item);
		}*/
		
	}

