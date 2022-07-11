/*****************************************************************************
 *                                                                           *
 *                             I D L E T H R E A D                           *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Wird nur aktiviert, wenn kein Thread arbeiten moechte.   *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 13.8.2016                      *
 *****************************************************************************/

#ifndef __IdleThread_include__
#define __IdleThread_include__


#include "kernel/threads/Thread.h"
#include "kernel/Globals.h"


class IdleThread : public Thread {
    
private:
		int counter = 0;
    IdleThread(const Thread &copy); // Verhindere Kopieren

public:
    IdleThread () : Thread () {  }
    
    void run () {
        // Idle-Thread läuft, ab jetzt ist der Scheduler fertig initialisiert
        scheduler.setInitialized();
				//kout << "IdleThread[" << hex << tid << "]" << endl;
        while (1) {
						kout.setpos(0,20);
						kout << "IdleThread[" << dec << tid << "]: " << dec << counter << endl;
						counter += 1;
            scheduler.yield();
        }
    }
    
 };

#endif
