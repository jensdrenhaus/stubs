/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               L O C K E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Locker implementiert eine Sperrvariable, die verwendet wird,   */
/* um kritische Abschnitte zu schuetzen. Die Variable zeigt allerdings nur   */
/* an, ob der kritische Abschnitt frei ist. Ein eventuelles Warten und der   */
/* Schutz der fuer diese Klasse notwendigen Zaehlfunktion muss ausserhalb    */
/* erfolgen.                                                                 */
/*****************************************************************************/

#ifndef __Locker_include__
#define __Locker_include__

//#include "device/cgastr.h"
#include "machine/cpu.h"

class Locker
 {
private:
    Locker(const Locker &copy); // Verhindere Kopieren
    int free;

public:
	Locker()
	{
		free = 1;
	}
	 
	void inline enter()
	{
		if(!free)
		{
			/*kout.setpos(1, 1);
			kout << "free = 0 in enter";
			kout.flush();*/
			cpu.halt();
		}
		
		free = 0;
	}

	 void inline retne()
	 {
		if(free)
		{
			/*kout.setpos(1, 1);
			kout << "free = 1 in retne";
			kout.flush();*/
			cpu.halt();
		}
		 free = 1;
	 }
	 
	 bool inline avail()
	 {
		 return free;
	 } 
 };

#endif
