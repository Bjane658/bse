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
#include "user/KeyboardDemo.h"
#include "user/ExceptionDemo.h"
#include "user/HeapDemo.h"
#include "user/CoroutineDemo.h"
#include "user/CoopThreadDemo.h"
#include "user/PreemtiveThreadDemo.h"
#include "user/VBEdemo.h"
#include "user/HelloWorldThread.h"
#include "user/LoopThread.h"
#include "lib/Queue.h"
#include "lib/Chain.h"


CoroutineDemo coroutineDemo;


int main() {
    
		//
    // Speicherverwaltung initialisieren
    allocator.init();

    // Bildschirm loeschen.
    kout.clear();
		kout.setpos(0,0);
		/*	Keyboard Demo */
		//kout << "Keyboard Demo" << endl;
		//keyboard_demo();
		
		//exceptionDemo();
		//

		//paging
		/*
		pg_init();

		unsigned int* p1 = pg_alloc_page();
		*p1 = 0x10;
		pg_write_protect_page(p1);
		pg_notpresent_page(p1);

		kout << "p1: " << hex << p1 << endl;
		kout << "[p1]: " << hex << *p1 << endl;
		*p1 = 0x11;

		unsigned int* pt2 = (unsigned int*) allocator.alloc(8);
		kout << "[pt2]: " << hex << *pt2 << endl;
		*/



		/*	Heap Demo */
		//heap_demo();

		// CoroutineDemo
    //kout.setpos(0,0);
    //kout << "Start Coroutines" << endl;
		//coroutineDemo.main();
		//
		

		/* Coop Thread Demo */
		
	
		/*
		CoopThreadDemo* coop = new CoopThreadDemo();
		scheduler.Scheduler::ready(coop);
		*/
		

		/* Preemtive Thread Demo */
		PreemtiveThreadDemo* preemtive = new PreemtiveThreadDemo();
		scheduler.Scheduler::ready(preemtive);
		

		/* Graphic Demo */
		//VBEdemo* vbeDemo = new VBEdemo();
		//scheduler.Scheduler::ready(vbeDemo);

		//scheduler.Scheduler::schedule();


    kb.plugin();
		pit.plugin();
    
    // Tastatur-Unterbrechungsroutine 'einstoepseln'

    // Interrupts erlauben (Tastatur)
    cpu.enable_int();

		//kout << "Playing tetris" << endl;
		//pcspk.tetris();

		//Anwendung im Scheduler anmelden
		scheduler.Scheduler::schedule();
  
  
    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
 }
