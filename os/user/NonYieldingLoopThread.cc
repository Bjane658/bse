/*****************************************************************************
 *                                                                           *
 *                        L O O P T H R E A D                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo eines Threads. Schleife die Zahlen ausgibt.         *
 *****************************************************************************/

#include "user/NonYieldingLoopThread.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         LoopThread::run                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Code des Threads.                                        *
 *****************************************************************************/
void NonYieldingLoopThread::run () {
	unsigned int counter = 0;
	
	while(1){
    cpu.disable_int();
		kout.setpos(0,5 + id);
		kout << "Thread[" << id << "]: " << dec << counter;
    cpu.enable_int();
		kout.flush();
		counter += 1;
	}
   
}
