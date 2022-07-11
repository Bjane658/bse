/*****************************************************************************
 *                                                                           *
 *                        L O O P T H R E A D                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo eines Threads. Schleife die Zahlen ausgibt.         *
 *****************************************************************************/

#include "user/LoopThread.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         LoopThread::run                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Code des Threads.                                        *
 *****************************************************************************/
void LoopThread::run () {
	unsigned int counter = 0;
	
	while(1){
    cpu.disable_int();
		kout.setpos(0,5 + id);
		kout << "Thread[" << id << "]tid: " << tid << " counter: " << dec << counter;
		kout.flush();
    cpu.enable_int();
		counter += 1;
		scheduler.yield();
	}
   
}
