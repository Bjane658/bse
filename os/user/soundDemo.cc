
#include "kernel/Globals.h"

#include "user/soundDemo.h"

void soundDemo() {
	kout << "Soundtest: playing Tetris ..." << endl;
	pcspk.tetris();
}
