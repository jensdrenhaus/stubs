/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 B E L L                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Eine "Glocke" ist eine abstrakte Basisklasse, die das Ausloesen einer     */
/* Aktivitaet nach einer bestimmten Wartezeit erlaubt.                       */
/* Dazu besitzt sie einen Zaehler, der vom "Gloeckner" (Bellringer) ver-     */
/* waltet wird.                                                              */
/*****************************************************************************/

#ifndef __Bell_include__
#define __Bell_include__

#include "object/chain.h"

class Bell : public Chain
 {
private:
    Bell(const Bell &copy); // Verhindere Kopieren    
    int counter;
    
public:
    Bell() {}
	~Bell(){}
	
	void wait (int value)
	{
		counter = value;
	}
	
	int wait()
	{
		return counter;
	}
	
	void tick ()
	{
		counter--;
	}
	
	bool run_down ()
	{
		return counter <=0;// == 0;
	}
	
	virtual void ring () = 0;

};

#endif
