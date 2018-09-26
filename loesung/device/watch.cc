/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/
#include "device/watch.h"
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "machine/pic.h"
#include "syscall/guarded_organizer.h"
#include "meeting/bellringer.h"

#include "guard/guard.h"

Watch watch(10000);

void Watch::windup ()
{
	plugbox.assign(Plugbox::timer, *this);
	pic.allow(PIC::timer);

}

// PROLOGUE: Prologue der Uhrenunterbrechung
bool Watch::prologue (int slot)
{
	return true;
}

// EPILOGUE: Epilogue der Uhrenunterbrechung
void Watch::epilogue ()
{
	static int i=0;
	i++;
	int x,y;
	time += interval();
	
	/*
	kout.getpos(x, y);
	kout.setpos(1, 1);
	kout << "timer "<<i;
	kout.flush();						
	
	kout.setpos(x, y);*/
	
		bellringer.check();
	
		
		
		
		organizer.Scheduler::resume();
}

int Watch::getTime()
{
	Secure section();
	return time;
}
