/*****************************************************************************
 *                                                                           *
 *                         K E Y I R Q D E M O                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo zu Interrupts.                                      *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                      *
 *****************************************************************************/

#include "kernel/Globals.h"


void key_irq_demo() {
  cpu.disable_int();
	kout.clear();
	kout.setpos(1,1);
	kout << "Tastatur per Interrupt Demo" << endl;
  kb.plugin();
  cpu.enable_int();
}
