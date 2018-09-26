/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          B E L L R I N G E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Der "Gloeckner" wird im Rahmen der Timer-Epilog Bearbeitung aktiviert.    */
/* Er prueft, ob irgendwelche Glocken (Bell-Objekte) laeuten muessen. Die    */
/* Glocken befinden sich in einer Queue, die der Gloeckner verwaltet.        */
/*****************************************************************************/

#include "meeting/bellringer.h"
Bellringer bellringer;

void Bellringer::check ()
{
	Bell* itr = (Bell*)first();
	if(!itr)
		return;
	
	itr->tick();
	
	while (itr) {
		if (itr->run_down ()) {
				itr->ring ();
				dequeue();
		}
		else
			return;
		itr = (Bell*)first();
	}
		
}

void Bellringer::job (Bell* bell, int ticks)
{
	Bell* after = 0;
	Bell* itr = (Bell*)first();
	
	while (itr && ticks >= itr->wait()) {
		ticks -= itr->wait();
		after = itr;
		itr = (Bell*)itr->next;
	}

	if(!after)
	{
		if(first())
		{
			Bell *b2 = (Bell*)first();
			b2->wait(b2->wait()-ticks);
		}
		bell->wait(ticks);
		insert_first(bell);
	}
	else
	{
		if(after->next)
		{
			Bell *b2 = (Bell*)after->next;
			b2->wait(b2->wait()-ticks);
		}
		bell->wait(ticks);
		insert_after(after, bell);
	}
}

void Bellringer::cancel (Bell* bell)
{
	if(!bell->next)
	{
		Bell *b2 = (Bell*)bell->next;
		b2->wait(b2->wait()+bell->wait());
	}
	remove(bell);
}

