/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstraktion einer Interruptvektortabelle. Damit kann man die Behandlungs- */
/* routine fuer jeden Hardware-, Softwareinterrupt und jede Prozessor-       */
/* exception festlegen.                                                      */
/*****************************************************************************/
#include "machine/plugbox.h"
#include "device/panic.h"

Plugbox plugbox;

Plugbox::Plugbox()
{
	for (unsigned int i = 0; i < 64; i++)
	{
		gates[i] = &panic;
	} 
}
	Plugbox::~Plugbox()
	{}
	
	void Plugbox::assign (unsigned int slot, Gate& gate)
	{
		if (slot < 64)
		{
			gates[slot] = &gate;
		}		
	}
	
	
	Gate& Plugbox::report (unsigned int slot)
	{
		if (slot < 64)
		{
			return *gates[slot];
		}		
		return panic;
	}
	
