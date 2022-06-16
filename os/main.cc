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
#include "user/CoopThreadDemo.h"
#include "user/HelloWorldThread.h"
#include "user/LoopThread.h"
#include "lib/Queue.h"
#include "lib/Chain.h"


CoroutineDemo coroutineDemo;


int main() {
    
    // Speicherverwaltung initialisieren
    allocator.init();

    // Bildschirm loeschen.
    kout.clear();
		kout.setpos(0,0);

		// CoroutineDemo
    //kout.setpos(0,0);
    //kout << "Start Coroutines" << endl;
		//coroutineDemo.main();
		//
		

		//HelloWorldThread* hw = new HelloWorldThread();
		CoopThreadDemo* coop = new CoopThreadDemo();
		//LoopThread* lt = new LoopThread(0);
		//LoopThread* lt1 = new LoopThread(1);
		//LoopThread* lt2 = new LoopThread(2);

		scheduler.Scheduler::ready(coop);
		/*
		scheduler.Scheduler::ready(lt);
		scheduler.Scheduler::ready(lt1);
		scheduler.Scheduler::ready(lt2);
		*/
		scheduler.Scheduler::schedule();


    
    // Tastatur-Unterbrechungsroutine 'einstoepseln'
    //kb.plugin();

    // Interrupts erlauben (Tastatur)
    //cpu.enable_int();

		//Anwendung im Scheduler anmelden
		//scheduler.Scheduler::schedule();
  
  
    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
 }
