
#include "kernel/Globals.h"
#include "user/MainMenu.h"
#include "user/VBEdemo.h"
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
	kout.setpos(0,2);
	kout << "Main Menu" << endl;
	kout << "Choose Demo Programm" << endl;
	scheduler.semaphore.v();

	while(1){
		if(scheduler.threadsRunning() < 3){
			scheduler.semaphore.p();
			kout.setpos(0,2);
			kout << "Main Menu" << endl;
			kout << "Choose Demo Programm" << endl;
			kout << "Thread count: " << dec << scheduler.threadsRunning() << endl;
			scheduler.semaphore.v();

			Key key = kb.key_hit();
			if(key.valid()){
				if((int) key.ascii() == 0){

					kout.setpos(0,10);
					kout << "ESC hit" << endl;
				}
				/* Graphic Demo */
				switch(key.ascii()){
						case '1':{
							VBEdemo* vbeDemo = new VBEdemo();
							scheduler.Scheduler::ready(vbeDemo);
							break;
						}
						case '2':{
							PreemtiveThreadDemo* preemtive = new PreemtiveThreadDemo();
							scheduler.Scheduler::ready(preemtive);
							break;
						}
						case '3':{
							BluescreenNullPointer* bnp = new BluescreenNullPointer();
							scheduler.Scheduler::ready(bnp);
							break;
						}
						case '4':{
							BluescreenWriteProtection* bwp = new BluescreenWriteProtection();
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
