/*****************************************************************************
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines einfachen Zeitscheiben-Schedulers. *
 *                  Rechenbereite Threads werden in 'readQueue' verwaltet.   *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 23.11.2018                     *
 *****************************************************************************/

#include "kernel/threads/Scheduler.h"
#include "kernel/threads/IdleThread.h"


/*****************************************************************************
 * Methode:         Scheduler::Scheduler                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Konstruktor des Schedulers. Registriert den Leerlauf-    *
 *                  Thread.                                                  *
 *****************************************************************************/
Scheduler::Scheduler () {
    initialized = false;

}

/*****************************************************************************
 * Methode:         Scheduler::schedule                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Scheduler starten. Wird nur einmalig aus main.cc gerufen.*
 *****************************************************************************/
void Scheduler::schedule () {
    cpu.disable_int ();
		IdleThread* it = new IdleThread();
		ready(it);
		initialized = true;
		Thread* firstThread = (Thread*)readyQueue.dequeue();
		//ready(firstThread);
		start(*firstThread);
    cpu.enable_int ();
}


/*****************************************************************************
 * Methode:         Scheduler::ready                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread in readyQueue eintragen.                          *
 *                                                                           *
 * Parameter:                                                                *
 *      that        Einzutragender Thread                                    *
 *****************************************************************************/
void Scheduler::ready (Thread * that) {
    // Thread-Wechsel durch PIT verhindern
    cpu.disable_int ();

    readyQueue.enqueue (that);

    // Thread-Wechsel durch PIT jetzt wieder erlauben
    cpu.enable_int ();
}


/*****************************************************************************
 * Methode:         Scheduler::exit                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread ist fertig und terminiert sich selbst. Hier muss  *
 *                  nur auf den naechsten Thread mithilfe des Dispatchers    *
 *                  umgeschaltet werden. Der aktuell laufende Thread ist     *
 *                  nicht in der readyQueue.                                 *
 *****************************************************************************/
void Scheduler::exit () {
    // Thread-Wechsel durch PIT verhindern
    cpu.disable_int ();

	//readyQueue.dump(false);
	Thread* nextThread = (Thread*)readyQueue.dequeue();
	//readyQueue.dump(false);
	//kout << "nextThread: " << hex << nextThread << endl;
	dispatch(*nextThread);
	
    // Interrupts werden in Thread_switch in Thread.asm wieder zugelassen
    // dispatch kehr nicht zurueck
}


/*****************************************************************************
 * Methode:         Scheduler::kill                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread mit 'Gewalt' terminieren. Er wird aus der         *
 *                  readyQueue ausgetragen und wird dann nicht mehr aufge-   *
 *                  rufen. Der Aufrufer dieser Methode muss ein anderer      *
 *                  Thread sein.                                             *
 *                                                                           *
 * Parameter:                                                                *
 *      that        Zu terminierender Thread                                 *
 *****************************************************************************/
void Scheduler::kill (Thread * that) {
    // Thread-Wechsel durch PIT verhindern
    cpu.disable_int ();

    readyQueue.remove (that);
    
    // Thread-Wechsel durch PIT jetzt wieder erlauben
    cpu.enable_int ();
}

void Scheduler::killAll () {
    // Thread-Wechsel durch PIT verhindern
    cpu.disable_int ();

		Thread* active = get_active();

		kout.setpos(0,20);
		kout << "queue count" << dec << readyQueue.count() << endl;
		while(readyQueue.count() >= 2){
			Thread* next = (Thread*) readyQueue.dequeue();
			if(next == 0){
				break;
			}
			kout << "thread " << hex << next << " tid: " << dec << next->tid << endl;
			if(next->tid == 1){
				ready(next);
			}
		}
    
    // Thread-Wechsel durch PIT jetzt wieder erlauben
    cpu.enable_int ();
}




/*****************************************************************************
 * Methode:         Scheduler::yield                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    CPU freiwillig abgeben und Auswahl des naechsten Threads.*
 *                  Naechsten Thread aus der readyQueue holen, den aktuellen *
 *                  in die readyQueue wieder eintragen. Das Umschalten soll  *
 *                  mithilfe des Dispatchers erfolgen.                       *
 *                                                                           *
 *                  Achtung: Falls nur der Idle-Thread läuft, so ist die     *
 *                           readyQueue leer.                                *
 *****************************************************************************/
void Scheduler::yield () {
  cpu.disable_int ();

	Thread* nextThread = (Thread*)readyQueue.dequeue();

	ready(get_active());

	if(nextThread == 0){
		kout << "empty queue" << endl;
	}else{
		dispatch(*nextThread);
	}

  cpu.enable_int ();
}

/*****************************************************************************
 * Methode:         Scheduler::preempt                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Diese Funktion wird aus der ISR des PITs aufgerufen und  *
 *                  schaltet auf den naechsten Thread um, sofern einer vor-  *
 *                  handen ist.                                              *
 *****************************************************************************/
void Scheduler::preempt () {
	if(initialized){
		yield();
	}
}

void Scheduler::block(){
  cpu.disable_int ();

	Thread* nextThread = (Thread*)readyQueue.dequeue();

	// active Thread in Semaphor Warteschlange eintragen
	Thread* activeThread = get_active();
	semaphore.waitQueue.enqueue(activeThread);


	if(nextThread == 0){
		kout << "empty queue" << endl;
	}else{
		dispatch(*nextThread);
	}

  cpu.enable_int ();
}

void Scheduler::deblock(Thread * that){
  cpu.disable_int ();
	ready(that);
  cpu.enable_int ();
}

int Scheduler::threadsRunning(){
	int threadCount = 0;
	if(get_active() != 0){
		threadCount += 1;
	}

	return threadCount + readyQueue.count();
}
