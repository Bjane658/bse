
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
	TextThread* textThread = new TextThread();
	VBEdemo* vbeDemo = new VBEdemo();
	InterruptDemo* interruptDemo = new InterruptDemo();
	HeapThread* heapThread = new HeapThread();
	PreemtiveThreadDemo* preemtive = new PreemtiveThreadDemo();
	BluescreenNullPointer* bnp = new BluescreenNullPointer();
	BluescreenWriteProtection* bwp = new BluescreenWriteProtection();

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
			kout << "5. Preemtives Scheduling: 3 Zähler-Threads, 1 Musik Thread und Systemzeit" << endl;
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
				/* Graphic Demo */
				switch(key.ascii()){
						case '1':{
							scheduler.Scheduler::ready(textThread);
							kout.setpos(0,20);
							break;
						}
						case '2':{
							scheduler.Scheduler::ready(vbeDemo);
							break;
						}
						case '3':{
							scheduler.Scheduler::ready(interruptDemo);
							break;
						}
						case '4':{
							scheduler.Scheduler::ready(heapThread);
							break;
						}
						case '5':{
							scheduler.Scheduler::ready(preemtive);
							break;
						}
						case '6':{
							scheduler.Scheduler::ready(bnp);
							break;
						}
						case '7':{
							scheduler.Scheduler::ready(bwp);
							break;
						}
				}
			}
		}else{

			/*
			Key key = kb.key_hit();
			if(key.valid()){
				if((int) key.ascii() == 0){

					kout.setpos(0,20);
					kout << "ESC hit" << endl;
					scheduler.killAll();
				}
			}
			*/
		}
	}

}
