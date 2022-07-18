

#include "user/BluescreenNullPointer.h"
#include "kernel/Paging.h"
#include "kernel/Globals.h"


void BluescreenNullPointer::run () {

	BluescreenNullPointer* bnp = 0;
	bnp->run();
   
}
