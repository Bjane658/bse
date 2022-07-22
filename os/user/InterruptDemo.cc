
#include "user/InterruptDemo.h"
#include "kernel/Globals.h"


void InterruptDemo::run () {
	kb.plugin();
	cpu.enable_int();

	kout.setpos(0,0);
	kout << "Keyboard interrupt demo" << endl;
	
	while(1){
			Key key = kb.key_hit();
			if(key.valid()){
				if((int) key.ascii() == 0){
					break;
				}
			}
	}
	kout.clear();
  pic.forbid(pic.keyboard);
	scheduler.exit();
	while(1){
	}
   
}
