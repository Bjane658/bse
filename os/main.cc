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
#include "user/MainMenu.h"
#include "user/PreemtiveThreadDemo.h"
#include "user/VBEdemo.h"
#include "user/HelloWorldThread.h"
#include "user/LoopThread.h"
#include "lib/Queue.h"
#include "lib/Chain.h"
#include "lib/Semaphore.h"
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
		//
		
		//Semaphore* s = new Semaphore(2);


		//paging
		pg_init();




		/****************************************************
		 *																									*
		 *								THREADS														*
		 *																									*
		 ****************************************************/

		kout.clear();
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
		/*
		PreemtiveThreadDemo* preemtive = new PreemtiveThreadDemo();
		scheduler.Scheduler::ready(preemtive);
		*/

		pit.plugin();
    // Interrupts erlauben (Tastatur)
    cpu.enable_int();
		/* Main Menu */
		MainMenu* mainMenu = new MainMenu();
		scheduler.Scheduler::ready(mainMenu);
		

		/* Graphic Demo */
		/*
		VBEdemo* vbeDemo = new VBEdemo();
		scheduler.Scheduler::ready(vbeDemo);
		*/

		//scheduler.Scheduler::schedule();


    
    // Tastatur-Unterbrechungsroutine 'einstoepseln'
		// kb.plugin();



		//Anwendung im Scheduler anmelden
		scheduler.Scheduler::schedule();
  
    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
 }
