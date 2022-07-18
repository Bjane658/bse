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
	if(counter > 0){
		counter -= 1;
		if(counter == 0){
			lock.acquire();
			cpu.enable_int();
		}
	}else{
		scheduler.block();
		lock.acquire();
		cpu.enable_int();
	}
}

void Semaphore::v(){
  cpu.disable_int();
	lock.release();
	counter += 1;
	if(!waitQueue.is_empty()){
		Thread* nextThread = (Thread*)waitQueue.dequeue();
		scheduler.deblock(nextThread);
	}
  cpu.enable_int();
}

