
/*****************************************************************************
 *                                                                           *
 *             Preemtive Thread demo										                     *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Beispiel für preemtive Threads.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 21.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/PreemtiveThreadDemo.h"
#include "user/LoopThread.h"
#include "user/TetrisThread.h"


/*****************************************************************************
 * Methode:         CoopThreadDemo::run                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Der Anwendungsthread erzeugt drei Threads die Zaehler    *
 *                  ausgeben und terminiert sich selbst.                     *
 *****************************************************************************/
void PreemtiveThreadDemo::run () {

	LoopThread* l0 = new LoopThread(0);
	LoopThread* l1 = new LoopThread(1);
	LoopThread* l2 = new LoopThread(2);
	TetrisThread* tetris = new TetrisThread(3);

	scheduler.Scheduler::ready(l0);
	scheduler.Scheduler::ready(l1);
	scheduler.Scheduler::ready(l2);
	scheduler.Scheduler::ready(tetris);
	//scheduler.Scheduler::readyQueue.dump(false);

	scheduler.exit();
}
