

#include "user/BluescreenNullPointer.h"
#include "kernel/Paging.h"
#include "kernel/Globals.h"


void BluescreenNullPointer::run () {

  cpu.enable_int();
	BluescreenNullPointer* bnp = 0;
	bnp->run();
   
}
