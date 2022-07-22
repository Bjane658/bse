
#ifndef __heapthread_include__
#define __heapthread_include__

#include "kernel/threads/Thread.h"

class HeapThread : public Thread {
    
private:

    HeapThread (const HeapThread &copy); // Verhindere Kopieren
    
public:
    HeapThread () : Thread () {}

    void run ();
};

#endif
