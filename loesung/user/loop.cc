/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 L O O P                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Loop ist ein Thread, der nichts weiter tut als einen Zaehler hochzu-      */
/* zaehlen und dies auf dem Bildschirm anzuzeigen. Zwischendurch gibt er     */
/* den Prozessor ab. Der Scheduler bestimmt dann, welcher Thread als         */
/* naechstes laufen soll.                                                    */
/*****************************************************************************/

#include "user/loop.h"
#include "device/cgastr.h"
#include "machine/cpu.h"
#include "guard/secure.h"
#include "syscall/guarded_organizer.h"
#include "meeting/bellringer.h"

#include "device/watch.h"

#include "syscall/guarded_semaphore.h"
#include "syscall/guarded_buzzer.h"

Guarded_Semaphore s(0);
Guarded_Buzzer buzzer;

class TestKilled: public Thread
{
	char stack[4096];
	public:
	int id;
	TestKilled(): Thread(stack+4096)
	{
	}
	void action()
	{
		buzzer.sleep();
		//s.wait();
	 int i=0;
		while (i<id*1000)
		{
			i++;
			{ SecureSem section(&screen_lock);
				kout.setpos(5, id+15);
				kout << "test "<<id<<": " << i;
				kout.flush();
			}
			
			//organizer.resume();
		
		}
		
		{ SecureSem section(&screen_lock);
			kout.setpos(5, id+15);
			kout << "test "<<id<<" exit: " << i;
			kout.flush();
		}
	}
}testKilled[10];


void Loop::action ()
 {
	int i=0;
	 
	 for(int k=0;k<10;k++)
	 {
		 testKilled[k].id = k;
		organizer.ready(testKilled[k]);
	 }
	 
	 buzzer.set(3000);
	 /*for(int k=0;k<10;k++)
	 {
		 int start = watch.time;
		while(watch.time < start + 1000000)
		{
			 
			{ SecureSem section(&screen_lock);
				kout.setpos(1, 3);
				kout << "time: " << watch.time;
				kout.flush();
			}
		}
		s.signal();
	}*/
	 
	while (true)
	{
		i++;
		{ SecureSem section(&screen_lock);
			kout.setpos(5, 12);
			kout << "loop: " << i;
			kout.flush();
		}
		/*for(int k=0;k<10;k++)
		{
			if(i>=(10-k)*1000)
			{
				organizer.kill(testKilled[k]);
			}
		}*/
		if(i>=100000)
		{
			{ SecureSem section(&screen_lock);
				kout.setpos(5, 12);
				kout << "exit: " << i;
				kout.flush();
			}
		
			organizer.exit();
		}
		//organizer.resume();
	}
 }
