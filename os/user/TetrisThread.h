
#ifndef __tetristhread_include__
#define __tetristhread_include__

#include "kernel/threads/Thread.h"

class TetrisThread : public Thread {
    
private:
    int id;

    TetrisThread (const TetrisThread &copy); // Verhindere Kopieren
    
public:
    TetrisThread () : Thread () {}

    // spielt Tetris
    void run ();
};

#endif
