/*****************************************************************************
 *                                                                           *
 *                        L O O P T H R E A D                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo eines Threads. Schleife die Zahlen ausgibt.         *
 *****************************************************************************/

#ifndef __nonyieldingthread_include__
#define __nonyieldingthread_include__

#include "kernel/threads/Thread.h"

class NonYieldingLoopThread : public Thread {
    
private:
    int id;

    NonYieldingLoopThread (const NonYieldingLoopThread &copy); // Verhindere Kopieren
    
public:
    // Gibt der Loop einen Stack und eine Id.
    NonYieldingLoopThread (int i) : Thread () { id = i; }

    // Zaehlt einen Zaehler hoch und gibt ihn auf dem Bildschirm aus.
    void run ();
};

#endif
