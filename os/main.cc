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
#include "lib/Queue.h"
#include "lib/Chain.h"


CoroutineDemo coroutineDemo;


int main() {
    
    // Speicherverwaltung initialisieren
    allocator.init();

    // Bildschirm loeschen.
    kout.clear();
		kout.setpos(0,0);

		Chain* ch1 = new Chain();
		Chain* ch2 = new Chain();
		Chain* ch3 = new Chain();

		Queue* q1 = new Queue();
		kout << "q1 Addresse: " << hex << q1 << endl;
		q1->dump(true);
		kout << "Enqueueing: " << hex << ch1 << endl;
		q1->enqueue(ch1);
		q1->dump(false);
		kout << "Enqueueing: " << hex << ch2 << endl;
		q1->enqueue(ch2);
		q1->dump(false);
		kout << "Enqueueing: " << hex << ch3 << endl;
		q1->enqueue(ch3);
		q1->dump(false);

		kout << "Removing: " << hex << ch3 << endl;
		q1->remove(ch3);
		q1->dump(false);

		kout << "Removing: " << hex << ch2 << endl;
		q1->remove(ch2);
		q1->dump(false);

		kout << "Removing: " << hex << ch1 << endl;
		q1->remove(ch1);
		q1->dump(true);

		kout << "Enqueueing: " << hex << ch2 << endl;
		q1->enqueue(ch2);
		q1->dump(false);
		kout << "Enqueueing: " << hex << ch3 << endl;
		q1->enqueue(ch3);
		q1->dump(false);



    while (1) ; // wir kehren nicht zum Bootlader zurueck


		// CoroutineDemo
    //kout.setpos(0,0);
    //kout << "Start Coroutines" << endl;
		//coroutineDemo.main();
    
    // Tastatur-Unterbrechungsroutine 'einstoepseln'
    //kb.plugin();

    // Interrupts erlauben (Tastatur)
    //cpu.enable_int();

		//Anwendung im Scheduler anmelden
		//scheduler.Scheduler::schedule();
  
  
    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
 }
