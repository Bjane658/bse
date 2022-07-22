#ifndef __interruptdemo_include__
#define __interruptdemo_include__

#include "kernel/threads/Thread.h"

class InterruptDemo : public Thread {
    
private:

    InterruptDemo (const InterruptDemo &copy); // Verhindere Kopieren
    
public:
    // Gibt der Loop einen Stack und eine Id.
    InterruptDemo () : Thread () {}

    // Zaehlt einen Zaehler hoch und gibt ihn auf dem Bildschirm aus.
    void run ();
};

#endif
