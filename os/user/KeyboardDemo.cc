/*****************************************************************************
 *                                                                           *
 *                        K E Y B O A R D D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                      *
 *****************************************************************************/

#include "kernel/Globals.h"


void keyboard_demo() {
    while(1){
        Key key = kb.key_hit();
        if(key.valid()){
					if((int) key.ascii() == 0){
						break;
					}
         kout << dec << key.ascii();
         kout << dec << (int)key.ascii();
				 kout.flush();
        }
    }
}
