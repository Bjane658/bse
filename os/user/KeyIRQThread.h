/*****************************************************************************
 *                                                                           *
 *                        L O O P T H R E A D                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo eines Threads. Schleife die Zahlen ausgibt.         *
 *****************************************************************************/

#ifndef __keyirqthread_include__
#define __keyirqthread_include__

#include "kernel/threads/Thread.h"

class KeyIRQThread : public Thread {
    
private:

    KeyIRQThread (const KeyIRQThread &copy); // Verhindere Kopieren
    
public:
    // Gibt der Loop einen Stack und eine Id.
    KeyIRQThread () : Thread () {}

    // Zaehlt einen Zaehler hoch und gibt ihn auf dem Bildschirm aus.
    void run ();
};

#endif
