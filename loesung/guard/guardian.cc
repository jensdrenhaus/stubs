/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              G U A R D I A N                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Zentrale Unterbrechungsbehandlungsroutine des Systems.                    */
/* Der Parameter gibt die Nummer des aufgetretenen Interrupts an.            */
/*****************************************************************************/

/* INCLUDES */

/* FUNKTIONEN */
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "guard/guard.h"
#include "machine/cpu.h"

extern "C" void guardian (unsigned int slot);

/* GUARDIAN: Low-Level Interrupt-Behandlung. Die Funktion wird spaeter noch */
/*           erweitert.                                                     */

void guardian (unsigned int slot)
 {
	 if(slot == 39)return;
	 
	if (plugbox.report(slot).prologue(slot)) {
		guard.relay(&plugbox.report(slot));
	}
 }
