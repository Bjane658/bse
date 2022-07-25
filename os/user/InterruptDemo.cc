
#include "user/InterruptDemo.h"
#include "kernel/Globals.h"


void InterruptDemo::run () {
	scheduler.semaphore.p();
	kout.setpos(0,1);
	kout << "Keyboard interrupt demo" << endl;
	scheduler.semaphore.v();
	kb.plugin();
	cpu.enable_int();

	while(1){
	}
   
}
