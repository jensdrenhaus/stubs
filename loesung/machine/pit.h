/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#ifndef __pit_include__
#define __pit_include__

#include "machine/io_port.h"

class PIT
 {
private:
    PIT(const PIT &copy); // Verhindere Kopieren
    
	IO_Port PIT1_CNT;
	IO_Port PIT1_CTRL; 
	int set_us;
   
   
public:

    PIT (int us) : PIT1_CNT(0x40), PIT1_CTRL(0x43) {
      interval (us);
    }
    
    int interval () {
		return set_us;
			
    }
    
    
    void interval (int us);
};

#endif
