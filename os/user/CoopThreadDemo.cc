/*****************************************************************************
 *                                                                           *
 *             C O O P E R A T I V E T H R E A D D E M O                     *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Beispiel für kooperative Threads.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 21.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/CoopThreadDemo.h"
#include "user/LoopThread.h"


/*****************************************************************************
 * Methode:         CoopThreadDemo::run                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Der Anwendungsthread erzeugt drei Threads die Zaehler    *
 *                  ausgeben und terminiert sich selbst.                     *
 *****************************************************************************/
void CoopThreadDemo::run () {
	unsigned int counter = 0;
	LoopThread* l0 = new LoopThread(0);
	LoopThread* l1 = new LoopThread(1);
	LoopThread* l2 = new LoopThread(2);

	//scheduler.Scheduler::readyQueue.dump(false);

	scheduler.Scheduler::ready(l0);
	scheduler.Scheduler::ready(l1);
	scheduler.Scheduler::ready(l2);
	//scheduler.Scheduler::readyQueue.dump(false);

	while(1){
		kout.setpos(0,0);
		kout << "DemoRun: " << dec << counter << endl;
		if(counter >= 1000){
			scheduler.kill(l1);
			scheduler.exit();
		}
		counter = counter + 1;
		scheduler.yield();
	}
}
