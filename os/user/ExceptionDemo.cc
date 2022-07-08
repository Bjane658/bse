
#include "kernel/Globals.h"
#include "user/ExceptionDemo.h"

void exceptionDemo() {
	asm("int $3");
}
