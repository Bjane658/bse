
#include "user/TetrisThread.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         TetrisThread::run                                        *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Code des Threads.                                        *
 *****************************************************************************/
void TetrisThread::run () {
	
	while(1){
		pcspk.tetris();
	}
   
}
