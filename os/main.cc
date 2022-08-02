/*****************************************************************************
 *                                                                           *
 *                                M A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Startroutine, wird direkt vom Bootlader angesprungen,    *
 *                  nachdem dieser in den Protected Mode geschaltet hat und  *
 *                  die GDT und IDT initalisiert hat.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/Paging.h"
#include "user/MainMenu.h"


int main() {
	// Speicherverwaltung initialisieren
  allocator.init();

	// Paging initialisieren
	pg_init();


	pit.plugin();

	// Interrupts erlauben
	cpu.enable_int();

	kout.clear();

	/* Main Menu */
	MainMenu* mainMenu = new MainMenu();
	scheduler.Scheduler::ready(mainMenu);


	//Anwendung im Scheduler anmelden
	scheduler.Scheduler::schedule();

	while (1) ; // wir kehren nicht zum Bootlader zurueck
	return 0;
 }
