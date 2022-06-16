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
#include "user/CoroutineDemo.h"


CoroutineDemo coroutineDemo;


int main() {
    
    // Speicherverwaltung initialisieren
    allocator.init();

    // Bildschirm loeschen.
    kout.clear();

		// CoroutineDemo
    //kout.setpos(0,0);
    //kout << "Start Coroutines" << endl;
		//coroutineDemo.main();
    
    // Tastatur-Unterbrechungsroutine 'einstoepseln'
    kb.plugin();

    // Interrupts erlauben (Tastatur)
    cpu.enable_int();

		//Anwendung im Scheduler anmelden
		//scheduler.Scheduler::schedule();
  
  
    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
 }
