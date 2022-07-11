/*****************************************************************************
 *                                                                           *
 *                        L O O P T H R E A D                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo eines Threads. Schleife die Zahlen ausgibt.         *
 *****************************************************************************/

#include "user/TextThread.h"
#include "user/TextDemo.h"

#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         LoopThread::run                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Code des Threads.                                        *
 *****************************************************************************/
void TextThread::run () {
  //cpu.disable_int();
	textDemo();
	kout << "Press <ESC> to exit" << endl;
	while(1){
			Key key = kb.key_hit();
			if(key.valid()){
				if((int) key.ascii() == 0){
    			//cpu.enable_int();
					break;
				}
			}
	}
	scheduler.exit();
   
}
