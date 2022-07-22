#ifndef __textthread_include__
#define __textthread_include__

#include "kernel/threads/Thread.h"

class TextThread : public Thread {
    
private:

    TextThread (const TextThread &copy); // Verhindere Kopieren
    
public:
    // Gibt der Loop einen Stack und eine Id.
    TextThread () : Thread () {}

    // Zaehlt einen Zaehler hoch und gibt ihn auf dem Bildschirm aus.
    void run ();
};

#endif
