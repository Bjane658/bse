

#ifndef __bluescreenwriteprotection_include__
#define __bluescreenwriteprotection_include__

#include "kernel/threads/Thread.h"

class BluescreenWriteProtection : public Thread {
    
private:
    int id;

    BluescreenWriteProtection (const BluescreenWriteProtection &copy); // Verhindere Kopieren
    
public:
    BluescreenWriteProtection () : Thread () {}

    void run ();
};

#endif
