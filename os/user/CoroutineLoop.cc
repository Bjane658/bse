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
void CoroutineLoop::dumpStack(){
	unsigned int **stack = (unsigned int**)regs.ebx;
	if(id == 1){
		kout.setpos(0,0);
	}
	if(id == 2){
		kout.setpos(20,0);
	}
	if(id == 3){
		kout.setpos(30,0);
	}
	kout << "Stack [" << dec << id << "]" <<  endl;
	int i = 0;
	while(i < 1024){
		if(stack[i] != 0){
			kout << "|" << dec << i << "| " << hex << stack[i] << " |" << endl;
		}
		i = i + 1;
	}
}
void CoroutineLoop::dump(){
			kout.setpos(0,6 + 6* id );
			kout << "run dump for: " <<  dec << id << "        x" << endl;
			kout << "RegsAddress: "  << hex << &regs << "        ";
			kout << "NextRegsAddress: "  << hex << &((Coroutine*)(next))->regs << endl;
			kout << "RegsAddressEDI: "  << hex << regs.edi << "        ";
			kout << "NextRegsAddressEDI: "  << hex << ((Coroutine*)(next))->regs.edi << endl;
			kout << "RegsAddressEBP: "  << hex << regs.ebp << "        ";
			kout << "NextRegsAddressEBP: "  << hex << ((Coroutine*)(next))->regs.ebp << endl;
			kout << "RegsAddressESI: "  << hex << regs.esi << "   ";

			kout << "NextRegsAddressESI: "  << hex << ((Coroutine*)(next))->regs.esi << endl;
			kout << "RegsAddressESP: "  << hex << regs.esp << "   ";

			kout << "NextRegsAddressESP: "  << hex << ((Coroutine*)(next))->regs.esp << endl;

}

void CoroutineLoop::run () {
		unsigned int counter = 0;
		
		while(1){
		kout.setpos(20,0+id);
			kout << "loop[" << dec << id << "]: " << dec << counter << endl;
			kout.flush();
			counter += 1;
			switchToNext();
		}
}
