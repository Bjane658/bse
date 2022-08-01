/*****************************************************************************
 *                                                                           *
 *                             S E M A P H O R E                             *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung von Sempahor-Objekten.                   *
 *                                                                           *
 * Autor:           Michael Schoettner, 2.9.2016                             *
 *****************************************************************************/

#include "lib/Semaphore.h"
#include "kernel/Globals.h"


void Semaphore::p(){
	cpu.disable_int();
	counter -= 1;
	if(counter < 0){
		scheduler.block();
	}
	lock.acquire();
	cpu.disable_int();
}

void Semaphore::v(){
  cpu.disable_int();
	counter += 1;
	if(counter <= 0){
		if(!waitQueue.is_empty()){
			Thread* nextThread = (Thread*)waitQueue.dequeue();
			scheduler.deblock(nextThread);
		}
	}
	lock.release();
  cpu.enable_int();
}
