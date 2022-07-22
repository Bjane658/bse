
#include "user/HeapThread.h"
#include "kernel/Globals.h"
#include "user/HeapDemo.h"


void HeapThread::run () {

	heap_demo();
	
	scheduler.exit();
   
}
