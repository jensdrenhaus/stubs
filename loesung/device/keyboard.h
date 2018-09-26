/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

#ifndef __Keyboard_include__
#define __Keyboard_include__

#include "machine/keyctrl.h"
#include "guard/gate.h"
#include "machine/key.h"
#include "syscall/guarded_semaphore.h"
 
class Keyboard : public Gate, public Keyboard_Controller
{        
private:

      Keyboard (const Keyboard &copy);
      Key key;
      bool epilogueReadingKey;
      //char key_atomar;
      
      Key buffer;
      bool hasKey;
      //Guarded_Semaphore buffer_empty(1);
      Guarded_Semaphore key_buffered;
                
         
public:

	Keyboard();
	~Keyboard()
	{}
     
     void plugin ();
	 
	 bool prologue (int slot);
	 void epilogue ();
	 Key getkey();
	 void clearBuffer();
 }; 

#endif
