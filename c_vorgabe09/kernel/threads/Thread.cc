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
 * Autor:           Michael, Schoettner, HHU, 3.7.2022                       *
 *****************************************************************************/
#include "kernel/threads/Thread.h"

// global counter for thread IDs
unsigned int TIDcnt = 0;


// Funktionen, die auf der Assembler-Ebene implementiert werden, muessen als
// extern "C" deklariert werden, da sie nicht dem Name-Mangeling von C++
// entsprechen.
extern "C" {
    void Thread_start  (struct ThreadState* regs);
    
    void Thread_switch (struct ThreadState* regs_now,
                        struct ThreadState* reg_then);
}


/*****************************************************************************
 * Prozedur:        ThreadState_init                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Bereitet den Kontext eines Threads fuer den ersten       *
 *                  Aufruf vor. Diese Methode wird jetzt nur noch vom erten  *
 *                  Thread genutzt, das ist der Idle-Thread der zuerst in    *
 *                  Ready-Queue eingetragen wird.                            *
 *                  Der Stackframe muss kompatibel zum Interrupt-Stackframe  *
 *                  sein, da später nur noch im Timer-Interrupt umgechaltet  *
 *                  wird (iehe startup.asm).                                 *
 *****************************************************************************/
void ThreadState_init (struct ThreadState* regs, unsigned int* stack,
                       void (*kickoff)(Thread*), void* object) {
    
    register unsigned int **sp = (unsigned int**)stack;
    
    // Stack initialisieren. Es soll so aussehen, als waere soeben die
    // eine Funktion aufgerufen worden, die als Parameter den Zeiger
    // "object" erhalten hat.
    // Da der Funktionsaufruf simuliert wird, kann fuer die Ruecksprung-
    // adresse nur ein unsinniger Wert eingetragen werden. Die aufgerufene
    // Funktion muss daher dafuer sorgen, dass diese Adresse nie benoetigt
    // wird, sie darf also nicht terminieren, sonst kracht's.
    
    *(--sp) = (unsigned int*)object;    // Parameter
    *(--sp) = (unsigned int*)0x131155; // Ruecksprungadresse
    
    // Nun legen wir noch die Adresse der Funktion "kickoff" ganz oben auf
    // den Stack. Wenn dann bei der ersten Aktivierung dieser Koroutine der
    // Stackpointer so initialisiert wird, dass er auf diesen Eintrag
    // verweist, genuegt ein ret, um die Funktion kickoff zu starten.
    // Genauso sollen auch alle spaeteren Threadwechsel ablaufen.
    
    *(--sp) = (unsigned int*)kickoff;   // Adresse
    
    // Initialisierung der Struktur ThreadState mit den Werten, die die
    // nicht-fluechtigen Register beim ersten Starten haben sollen.
    // Wichtig ist dabei nur der Stackpointer.
    
    regs->ebx = 0;
    regs->esi = 0;
    regs->edi = 0;
    regs->ebp = 0;
    regs->esp = sp;

    // nachfolgend die fluechtige Register
    // wichtig fuer preemptives Multitasking
    regs->eax = 0;
    regs->ecx = 0;
    regs->edx = 0;
    
    // flags initialisieren
    regs->efl = (void*)0x200; // Interrupt-Enable
}


