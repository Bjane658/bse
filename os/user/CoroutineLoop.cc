/*****************************************************************************
 *                                                                           *
 *                       C O R O U T I N E L O O P                           *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Loop ist eine Koroutine, die nichts weiter tut als einen *
 *                  Zaehler hochzuzaehlen und diesen auf dem Bildschirm      *
 *                  anzuzeigen und dann auf die naechste Korotuine umzu-     *
 *                  schalten.				 	 	 	           			 *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *****************************************************************************/

#include "user/CoroutineLoop.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         CoroutineLoop::run                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstiegsfunktion der Koroutine.                         *
 *****************************************************************************/
void CoroutineLoop::run () {
		//kout.setpos(15,15);
		//kout << "loop[" << dec << id << "]: " << endl;
		//kout.flush();
		
		while(1){
			//kout << "while" << endl;
		}
}
