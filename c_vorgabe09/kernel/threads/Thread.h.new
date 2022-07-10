/*****************************************************************************
 *                                                                           *
 *                                 T H R E A D                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines preemptiven Thread-Konzepts.       *
 *                  Thread-Objekte werden vom Scheduler in einer verketteten *
 *                  Liste 'readyQueue' verwaltet.                            *
 *                                                                           *
 *                  Im Konstruktor wird der initialie Kontext des Threads    *
 *                  eingerichtet. Mit 'start' wird ein Thread aktiviert.     *
 *                  Die CPU kann mit 'yield' freiwillig abgegeben.           *
 *                  Um bei einem Threadwechsel den Kontext sichern zu        *
 *                  koennen, enthaelt jedes Threadobjekt eine Struktur       *
 *                  ThreadState, in dem die Werte der nicht-fluechtigen und  *
 *                  fluechtigen Register gesichert werden koennen.           *
 *                                                                           *
 *                  Zusaetzlich zum vorhandenen freiwilligen Umschalten der  *
 *                  CPU mit 'Thread_switch' gibt es nun ein forciertes Um-   *
 *                  durch den Zeitgeber-Interrupt ausgeloest wird und in     *
 *                  Assembler in startup.asm implementiert ist. Fuer das     *
 *                  Zusammenspiel mit dem Scheduler ist die Methode          *
 *                  'prepare_preemption' in Scheduler.cc wichtig.            *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 1.1.2017                       *
 *****************************************************************************/

#ifndef __Thread_include__
#define __Thread_include__

#include "kernel/threads/ThreadState.h"
#include "lib/Chain.h"

class Thread : public Chain {
    
private:
    Thread(const Thread &copy); // Verhindere Kopieren

private:
    unsigned int *stack;     // pointer auf Stack des Threads

public:
    unsigned int tid;       // Thread-ID (wird automatisch vergeben)
    struct ThreadState regs;
    
    Thread ();
    ~Thread ();
   
    // Thread aktivieren
    void start ();

    // Umschalten auf Thread 'next'
    void switchTo (Thread& next);

    // Methode des Threads, muss in Sub-Klasse implementiert werden
    virtual void run () = 0;
    
 };

#endif
