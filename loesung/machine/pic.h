/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I C                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interrupt Controller.                                        */
/* Mit Hilfe des PICs koennen Hardware-Unterbrechungen einzeln zugelassen    */
/* oder unterdrueckt werden. Auf diese Weise wird also bestimmt, ob die      */
/* Unterbrechung eines Geraetes ueberhaupt an den Prozessor weitergegeben    */
/* wird. Selbst dann erfolgt eine Aktivierung der Unterbrechungsroutine nur, */
/* wenn der Prozessor bereit ist, auf Unterbrechungen zu reagieren. Dies     */
/* kann mit Hilfe der Klasse CPU festgelegt werden.                          */
/*****************************************************************************/

#ifndef __pic_include__
#define __pic_include__

#include "machine/io_port.h"


class PIC
 {
    private:
        PIC(const PIC &copy);
 

        IO_Port IMR_MASTER;    
        IO_Port IMR_SLAVE;

    public:

        PIC() : IMR_MASTER(0x21), IMR_SLAVE(0xa1)
        {
            
        }

        void allow (int interrupt_device);

        void forbid (int interrupt_device);
        
        
        enum 
        {
            timer = 0,
            keyboard = 1
        };

          
 };

extern PIC pic;

#endif
