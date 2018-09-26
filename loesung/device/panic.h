/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Standard Unterbrechungsbehandlung.                                        */
/*****************************************************************************/

#ifndef __panic_include__
#define __panic_include__

/* INCLUDES */

#include "guard/gate.h"

class Panic : public Gate
/* Hier muesst ihr selbst Code vervollstaendigen */         
 {
private:
    Panic (const Panic &copy); // Verhindere Kopieren
public:
    Panic () {}
	
	bool prologue(int slot);
	
	void epilogue ()	
	{}
	
	
          
 };

#endif

extern Panic panic;

