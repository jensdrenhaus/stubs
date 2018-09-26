/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S E M A P H O R E                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Semaphor.                                   */
/*****************************************************************************/

#ifndef __Guarded_Semaphore_include__
#define __Guarded_Semaphore_include__

#include "meeting/semaphore.h"
#include "guard/secure.h"


        
class Guarded_Semaphore : public Semaphore
{
private:
    Guarded_Semaphore (const Guarded_Semaphore &copy); // Verhindere Kopieren
public:
	Guarded_Semaphore (int c):Semaphore(c){};
	void p ();
	void v ();
	void wait (){p();}
	void signal (){v();}
 };


class SecureSem {
	Guarded_Semaphore *sem;
public:
	SecureSem(Guarded_Semaphore *sem)
	{
		this->sem = sem;
		sem->wait();
	}
	~SecureSem(){sem->signal();}	
};


#endif
