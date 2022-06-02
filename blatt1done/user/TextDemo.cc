
#include "kernel/Globals.h"
#include "user/TextDemo.h"

void textDemo() {
	kout.setpos(0,0);
	kout << "Test der Zahlenausgabeform" << endl;
	kout << "Dec | Hex | Bin" << endl;
	for(int i=0; i<17; i++){
		kout << dec << i << ' ' << hex << i <<  ' ' << bin << i << endl;
	}
}
