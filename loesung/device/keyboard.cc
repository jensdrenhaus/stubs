/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

#include "device/keyboard.h"
#include "machine/plugbox.h"
#include "machine/pic.h"
#include "machine/keyctrl.h"
#include "device/cgastr.h"



Keyboard::Keyboard(): key_buffered(0)
{
	//key_atomar = '0';
	hasKey = false;
	epilogueReadingKey = false;
}



     void Keyboard::plugin ()
     {
		 plugbox.assign(Plugbox::keyboard, *this);
		 pic.allow(PIC::keyboard);
	 }
	 
	 bool Keyboard::prologue (int slot)
	 {
		Key key = key_hit();
		
		bool valid = key.valid();
		
		if(valid)
		{
			if ((key.ctrl_left()) && key.alt_left() && (key.scancode() == Key::scan::del))
			{
				reboot();
			}
		}
		//key_atomar = key.ascii();
		if(!epilogueReadingKey)
			this->key = key;
	   return valid;
	 }
	 
	 void Keyboard::epilogue ()
	 {
		 if(hasKey)
			return;
		
		 //buffer_empty.wait ();
		// buffer.ascii (key_atomar);
		epilogueReadingKey = true;
		 buffer = key;
		 epilogueReadingKey = false;
		 hasKey = true;
		 key_buffered.Semaphore::signal ();
		 	
			/*int x,y;
			
			static int xpos = 20, ypos = 10;	
			
			
			kout.getpos(x, y);
			kout.setpos(xpos, ypos);
			kout << key_atomar;
			kout.flush();						
			
			kout.setpos(x, y);*/
		
	 }
	 
	
Key Keyboard::getkey()
{
	key_buffered.Semaphore::wait ();
	Key tmp = buffer;
	hasKey = false;
	//buffer_empty.signal ();
	return tmp;
	

}

void Keyboard::clearBuffer()
{
	while(key_buffered.Semaphore::try_wait())
	{
		hasKey = false;
	}
}
