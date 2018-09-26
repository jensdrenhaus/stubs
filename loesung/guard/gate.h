/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  G A T E                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Klasse von Objekten, die in der Lage sind, Unterbrechungen zu behandeln.  */
/*****************************************************************************/

#ifndef __Gate_include__
#define __Gate_include__

#include "object/chain.h"

class Gate : public Chain
{
	private:
		bool inQueue;
	public:
		Gate(){inQueue = false;}
		
		virtual ~Gate(){}
		
		virtual bool prologue (int slot) = 0;
		virtual void epilogue () = 0;
		void queued(bool q){inQueue = q;}
		bool queue (){return inQueue;}
};
#endif
