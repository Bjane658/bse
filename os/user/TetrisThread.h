
/*****************************************************************************
 *                                                                           *
 *                        Tetristhread				                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo eines Threads. Schleife die Zahlen ausgibt.         *
 *****************************************************************************/

#ifndef __tetristhread_include__
#define __tetristhread_include__

#include "kernel/threads/Thread.h"

class TetrisThread : public Thread {
    
private:
    int id;

    TetrisThread (const TetrisThread &copy); // Verhindere Kopieren
    
public:
    // Gibt der Loop einen Stack und eine Id.
    TetrisThread (int i) : Thread () { id = i; }

    // spielt Tetris
    void run ();
};

#endif
