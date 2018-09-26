/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I C                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interrupt Controller.                                        */
/* Mit Hilfe des PICs koennen Hardware-Unterbrechungen einzeln zugelassen    */
/* oder unterdrueckt werden. Auf diese Weise wird also bestimmt, ob die      */
/* Unterbrechung eines Geraetes ueberhaupt an den Prozessor weitergegeben    */
/* wird. Selbst dann erfolgt eine Aktivierung der Unterbrechungsroutine nur, */
/* wenn der Prozessor bereit ist, auf Unterbrechungen zu reagieren. Dies     */
/* kann mit Hilfe der Klasse CPU festgelegt werden.                          */
/*****************************************************************************/

#include "machine/pic.h"

PIC pic;

// IRx disable 
// <=> x-th bit in IMR Byte = 1

void PIC::forbid (int interrupt_device)
{
		
		if (interrupt_device >= 0 && interrupt_device < 8)
		{
			IMR_MASTER.outb(IMR_MASTER.inb() | (1 << interrupt_device)); 
		}
		else if(interrupt_device >=8 && interrupt_device < 16)
		{
			IMR_SLAVE.outb(IMR_SLAVE.inb() | (1 << (interrupt_device - 8))); 
		}           
}

// IRx enable
// <=> x-th bit in IMR Byte = 0

void PIC::allow (int interrupt_device)
{
	
		
		if (interrupt_device >= 0 && interrupt_device < 8)
		{
			IMR_MASTER.outb(IMR_MASTER.inb() & ~(1 << interrupt_device)); 
		}
		else if(interrupt_device >=8 && interrupt_device < 16)
		{
			IMR_SLAVE.outb(IMR_SLAVE.inb() & ~(1 << (interrupt_device - 8))); 
		}           
   
}
