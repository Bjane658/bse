/*****************************************************************************
 *                                                                           *
 *                        L O O P T H R E A D                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo eines Threads. Schleife die Zahlen ausgibt.         *
 *****************************************************************************/

#include "user/KeyIRQThread.h"
#include "user/KeyIRQDemo.h"

#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         LoopThread::run                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Code des Threads.                                        *
 *****************************************************************************/
void KeyIRQThread::run () {
  //cpu.disable_int();
	key_irq_demo();
	kout.setpos(0,25);
	kout << "Press <ESC> to exit" << endl;
	kout.setpos(0,2);
	while(1){
	}
   
}
