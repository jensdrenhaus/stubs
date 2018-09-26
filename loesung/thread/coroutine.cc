/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          C O R O U T I N E                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Koroutinenkonzepts.                                   */
/* Im Konstruktor wird der initiale Kontext der Koroutine eingerichtet.      */
/* Mit go() wird die erste Koroutine aktiviert. Alle weiteren Koroutinen-    */
/* wechsel sollten mit resume() erfolgen.                                    */
/* Um bei einem Koroutinenwechsel den Kontext sichern zu koennen, enthaelt   */
/* jedes Koroutinenobjekt eine Struktur toc, in dem die Werte der nicht-     */
/* fluechtigen Register gesichert werden koennen.                            */
/*****************************************************************************/

#include "thread/coroutine.h"
#include "device/cgastr.h"
#include "guard/guard.h"

// Funktionen, die auf der Assembler-Ebene implementiert werden, muessen als
// extern "C" deklariert werden, da sie nicht dem Name-Mangeling von C++ 
// entsprechen.
extern "C"
 {
	void toc_settle (struct toc* regs, void* tos, void (*kickoff)(void*), void* object);
	void toc_go (struct toc* regs);
	void toc_switch (struct toc* regs_now, struct toc* regs_then);
 }

void kickoff (Coroutine* object);

Coroutine::Coroutine(void *tos) {

	toc_settle (&regs, tos, (void (*)(void*))&kickoff, this);
}

void Coroutine::go() {
	cpu.disable_int();
	toc_go(&regs);
}

void *nextStack;

void Coroutine::resume(Coroutine& next)
{
	if(&next == 0)
	{
		kout.setpos(1, 1);
		kout << "Coroutine::resume next = NULL";
		kout.flush();
		cpu.halt();
	}
	
	nextStack = next.regs.esp;
	
	cpu.disable_int();
	toc_switch(&regs, &next.regs);
	cpu.enable_int();
}

		
