/*****************************************************************************
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines einfachen Zeitscheiben-Schedulers. *
 *                  Rechenbereite Threads werden in 'readyQueue' verwaltet.  *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 3.7.2022                       *
 *****************************************************************************/

#include "kernel/threads/Scheduler.h"
#include "kernel/threads/IdleThread.h"
#include "kernel/Globals.h"


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
    Thread* first;

   // Idle-Thread erzeugen und einfuegen
   IdleThread *idle = new IdleThread();
   ready (idle);

   first = (Thread*) readyQueue.dequeue();
   start (*first);
}


/*****************************************************************************
 * Methode:         Scheduler::ready                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread in readyQueue eintragen.                          *
 *                                                                           *
 * Parameter:                                                                *
 *      that        Einzutragender Thread                                    *
 *****************************************************************************/
void Scheduler::ready (Thread* that) {
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

    // hole naechsten Thread aus ready-Liste.
    Thread* next = (Thread*) readyQueue.dequeue();
    
    // next aktivieren
    dispatch (*next);

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
void Scheduler::kill (Thread* that) {
    // Thread-Wechsel durch PIT verhindern
    cpu.disable_int ();

    readyQueue.remove (that);
    
    // Thread-Wechsel durch PIT jetzt wieder erlauben
    cpu.enable_int ();
}


/*****************************************************************************
 * Methode:         Scheduler::yield                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    CPU freiwillig abgeben und Auswahl des naechsten Threads.*
 *                  Naechsten Thread aus der readyQueue holen, den aktuellen *
 *                  aus der readyQueue austragen und auf den naechsten       *
 *                  mithilfe des Dispatchers umschalten.                     *
 *                                                                           *
 *                  Achtung: Falls nur der Idle-Thread läuft, so ist die     *
 *                           readyQueue leer.                                *
 *****************************************************************************/
void Scheduler::yield () {
    Thread* next;

    // Thread-Wechsel durch PIT verhindern
    cpu.disable_int ();

    next = (Thread*) readyQueue.dequeue ();
    
    readyQueue.enqueue ((Thread*) active());

    dispatch (*next);
    
    // Thread-Wechsel durch PIT jetzt wieder erlauben
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
    
   /* Hier muss Code eingefuegt werden */
   
}
