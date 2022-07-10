/*****************************************************************************
 *                                                                           *
 *             Preemitve Thread Demo 										                     *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Beispiel für preemitve Threads.                          *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 21.8.2016                       *
 *****************************************************************************/
#ifndef __preemtivethreaddemo_include__
#define __preemtivethreaddemo_include__


#include "kernel/threads/Thread.h"


class PreemtiveThreadDemo : public Thread {
    
private:
    PreemtiveThreadDemo (const PreemtiveThreadDemo &copy); // Verhindere Kopieren

public:
    // Gib dem Anwendungsthread einen Stack.
    PreemtiveThreadDemo () : Thread () { }

    // Thread-Startmethode
    void run ();

 };

#endif
