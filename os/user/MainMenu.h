
#ifndef __mainmenu_include__
#define __mainmenu_include__


#include "kernel/threads/Thread.h"


class MainMenu : public Thread {
    
private:
    MainMenu (const MainMenu &copy); // Verhindere Kopieren

public:
    // Gib dem Anwendungsthread einen Stack.
    MainMenu () : Thread () { }

    // Thread-Startmethode
    void run ();

 };

#endif
