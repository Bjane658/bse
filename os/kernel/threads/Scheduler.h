/*****************************************************************************
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines einfachen Zeitscheiben-Schedulers. *
 *                  Rechenbereite Threads werden in 'readQueue' verwaltet.   *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 22.8.2016                      *
 *****************************************************************************/

#ifndef __Scheduler_include__
#define __Scheduler_include__

#include "kernel/threads/Dispatch.h"
#include "kernel/threads/Thread.h"
#include "lib/Queue.h"
#include "lib/Semaphore.h"

class Scheduler : public Dispatcher {
    
private:
    Scheduler (const Scheduler &copy); // Verhindere Kopieren
     
private:
    Queue readyQueue;   // auf die CPU wartende Threads
    // Scheduler wird evt. von einer Unterbrechung vom Zeitgeber gerufen,
    // bevor er initialisiert wurde
    bool  initialized;
   
public:
    Scheduler ();

    // Scheduler initialisiert?
    // Zeitgeber-Unterbrechung kommt evt. bevor der Scheduler fertig
    // intiialisiert wurde!
    bool isInitialized() { return initialized; }
		
    // ruft nur der Idle-Thread (erster Thread der vom Scheduler gestartet wird)
    void setInitialized() { initialized = true; }

    // Scheduler starten
    void schedule ();
    
    // Thread in readyQueue eintragen
    void ready (Thread * that);
    
    // Thread terminiert sich selbst
    void exit ();

    // Thread mit 'Gewalt' terminieren
    void kill (Thread * that);

		// Thread alle Threads außer den aufrufenden und denn Idle Thread terminieren
		void killAll();

    // CPU freiwillig abgeben und Auswahl des naechsten Threads
    void yield ();
		
    // Thread umschalten; wird aus der ISR des PITs gerufen
    void preempt ();

		void block();

		void deblock(Thread * that);

		int threadsRunning();

		Semaphore semaphore;
};

#endif
