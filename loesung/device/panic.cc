/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Standard Unterbrechungsbehandlung.                                        */
/*****************************************************************************/
/* Hier muesst ihr selbst Code vervollstaendigen */ 
/* Hier muesst ihr selbst Code vervollstaendigen */ 
 
#include "device/panic.h"
#include "machine/cpu.h"
#include "device/cgastr.h"

#include "syscall/guarded_organizer.h"
Panic panic;

extern void *nextStack;

bool Panic::prologue(int slot)
{
	if(slot == 39)
		return false;
	
	kout << "panik " <<slot <<" "<<nextStack<< "  "<<((void**)nextStack)[0]<< endl;
	
	
	
	//kout << "panik "<<organizer.active()<<"  "<<organizer.active()->regs.esp;
	kout.flush();
	
	cpu.halt();
	return false;
}
