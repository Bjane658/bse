

#ifndef __bluescreennullpointer_include__
#define __bluescreennullpointer_include__

#include "kernel/threads/Thread.h"

class BluescreenNullPointer : public Thread {
    
private:
    int id;

    BluescreenNullPointer (const BluescreenNullPointer &copy); // Verhindere Kopieren
    
public:
    BluescreenNullPointer () : Thread () {}

    void run ();
};

#endif
