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
#include "user/TextDemo.h"
#include "user/KeyIRQDemo.h"
#include "user/KeyIRQThread.h"
#include "user/TextThread.h"
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
#include "kernel/threads/IdleThread.h"


CoroutineDemo coroutineDemo;


int main() {

    
		//
    // Speicherverwaltung initialisieren
    allocator.init();

    // Bildschirm loeschen.
    //kout.clear();
		//kout.setpos(0,0);

		//textDemo();
		//key_irq_demo();
		//keyboard_demo();
		//exceptionDemo();
		//heap_demo();
		//pcspk.tetris();


		//paging
		pg_init();

		/*
		unsigned int* p1 = pg_alloc_page();
		*p1 = 0x10;
		pg_write_protect_page(p1);
		//pg_notpresent_page(p1);

		kout << "p1 address: " << hex << p1 << endl;
		kout << "p1 value: " << hex << *p1 << endl;
		//*p1 = 0x11;
		unsigned int* p4 = (unsigned int*) 0xbffffc;
		*p4 = 0x11;
		kout << "p4 address: " << hex << p4 << endl;
		kout << "p4 value: " << hex << *p4 << endl;

		unsigned int* p2 = pg_alloc_page();
		//*p2 = 0x22;
		kout << "p2 address: " << hex << p2 << endl;
		kout << "p2 value: " << hex << *p2 << endl;

		unsigned int* p3 = pg_alloc_page();
		*p3 = 0x33;
		kout << "p3 address: " << hex << p3 << endl;
		kout << "p3 value: " << hex << *p3 << endl;
		*/

		unsigned int* pt5 = (unsigned int*) allocator.alloc(8);
		kout << "[pt5]: " << hex << pt5 << endl;
		unsigned int* pt6 = (unsigned int*) allocator.alloc(8);
		kout << "[pt6]: " << hex << pt6 << endl;



		/****************************************************
		 *																									*
		 *								THREADS														*
		 *																									*
		 ****************************************************/

		// CoroutineDemo
    //kout.setpos(0,0);
    //kout << "Start Coroutines" << endl;
		//coroutineDemo.main();
		//
		
		/* Text Thread Demo */
		//TextThread* textThread = new TextThread();
		//scheduler.Scheduler::ready(textThread);

		/* Key IRQ Thread Demo */
		/*
		KeyIRQThread* keyIRQThread = new KeyIRQThread();
		scheduler.Scheduler::ready(keyIRQThread);
		*/

		/* Coop Thread Demo */
	
		/*
		CoopThreadDemo* coop = new CoopThreadDemo();
		scheduler.Scheduler::ready(coop);
		*/
		
		

		/* Preemtive Thread Demo */
		IdleThread* it = new IdleThread();
		PreemtiveThreadDemo* preemtive = new PreemtiveThreadDemo();
		scheduler.Scheduler::ready(preemtive);
		

		/* Graphic Demo */
		/*
		VBEdemo* vbeDemo = new VBEdemo();
		scheduler.Scheduler::ready(vbeDemo);
		*/

		//scheduler.Scheduler::schedule();


		pit.plugin();
    
    // Tastatur-Unterbrechungsroutine 'einstoepseln'
		// kb.plugin();

    // Interrupts erlauben (Tastatur)
    cpu.enable_int();


		//Anwendung im Scheduler anmelden
		scheduler.Scheduler::schedule();
  
    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
 }
