/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe des "Weckers" koennen Prozesse eine bestimmte Zeit lang         */
/* schlafen und sich dann wecken lassen.                                     */
/*****************************************************************************/

#include "meeting/buzzer.h"
#include "meeting/bellringer.h"
#include "syscall/guarded_organizer.h"

Buzzer::Buzzer()
{
}

Buzzer::~Buzzer()
{
	bellringer.cancel(this);

}

	
void Buzzer::ring ()
{
	Customer* temp;
		do{
			temp = (Customer*)Queue::dequeue();
			if(temp != 0){
				organizer.wakeup(*temp);
			}
		}while(temp != 0);
}


void Buzzer::set (int ms)
{
	bellringer.job (this, ms / 10);
}


void Buzzer::sleep ()
{
	organizer.block(*(Customer*)organizer.active(), *this);
}
