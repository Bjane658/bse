
#include "kernel/Globals.h"
#include "user/MainMenu.h"
#include "user/TextThread.h"
#include "user/VBEdemo.h"
#include "user/InterruptDemo.h"
#include "user/HeapThread.h"
#include "user/PreemtiveThreadDemo.h"
#include "user/BluescreenNullPointer.h"
#include "user/BluescreenWriteProtection.h"


/*****************************************************************************
 * Methode:         CoopThreadDemo::run                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Der Anwendungsthread erzeugt drei Threads die Zaehler    *
 *                  ausgeben und terminiert sich selbst.                     *
 *****************************************************************************/
void MainMenu::run () {

	scheduler.semaphore.p();
	kout.clear();
	kout.setpos(0,2);
	kout << "Main Menu" << endl;
	kout << "Choose Demo Programm" << endl;
	scheduler.semaphore.v();

	while(1){
		if(scheduler.threadsRunning() < 3){
			scheduler.semaphore.p();
			kout.clear();
			kout.setpos(0,2);
			kout << "Main Menu" << endl;
			kout << "Choose Demo Programm" << endl;
			kout << "1. Text Demo" << endl;
			kout << "2. Grafik Demo" << endl;
			kout << "3. Interrupt Demo" << endl;
			kout << "4. Heap Demo" << endl;
			kout << "5. Preemtives Scheduling: 3 Zaehler-Threads, 1 Musik Thread und Systemzeit" << endl;
			kout << "6. Bluescreen Null Pointer" << endl;
			kout << "7. Bluescreen Write Protection" << endl;

			scheduler.semaphore.v();

			Key key = kb.key_hit();
			if(key.valid()){
				if((int) key.ascii() == 0){

					kout.setpos(0,10);
					kout << "ESC hit" << endl;
				}
				kout.clear();
				switch(key.ascii()){
						case '1':{
							TextThread* textThread = new TextThread();
							scheduler.Scheduler::ready(textThread);
							kout.setpos(0,20);
							break;
						}
						case '2':{
							VBEdemo* vbeDemo = new VBEdemo();
							scheduler.Scheduler::ready(vbeDemo);
							break;
						}
						case '3':{
							InterruptDemo* interruptDemo = new InterruptDemo();
							scheduler.Scheduler::ready(interruptDemo);
							break;
						}
						case '4':{
							HeapThread* heapThread = new HeapThread();
							scheduler.Scheduler::ready(heapThread);
							break;
						}
						case '5':{
							PreemtiveThreadDemo* preemtive = new PreemtiveThreadDemo();
							scheduler.Scheduler::ready(preemtive);
							break;
						}
						case '6':{
							BluescreenNullPointer* bnp = new BluescreenNullPointer();
							scheduler.Scheduler::ready(bnp);
							break;
						}
						case '7':{
							BluescreenWriteProtection* bwp = new BluescreenWriteProtection();
							scheduler.Scheduler::ready(bwp);
							break;
						}
				}
			}
		}
	}

}
