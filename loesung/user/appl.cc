/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "device/cgastr.h"
#include "machine/cpu.h"
#include "guard/secure.h"
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_keyboard.h"
/* Hier muesst ihr selbst Code vervollstaendigen */         
         
/* GLOBALE VARIABLEN */

extern CGA_Stream kout;

void Application::action ()
 {
	 int i=0;
	 //test.app = this;
	while (true)
	{
		Key k = keyboard.getkey();
		{
			SecureSem section(&screen_lock);
			kout.setpos(5, 10);
			kout << "key "<<k.ascii()<<"  "<<k.ctrl_left()<< " "<<i;
			kout.flush();
		}
		i++;
		/*{ SecureSem section(&screen_lock);
			kout.setpos(5, 10);
			kout << "hallo";
			kout.flush();
		}
		
		organizer.resume();*/
	}
 }
