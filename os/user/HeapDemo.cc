/*****************************************************************************
 *                                                                           *
 *                            H E A P D E M O                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demonstration der dynamischen Speicherverwaltung.        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 27.12.2016                      *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/Allocator.h"
#include "user/HeapDemo.h"
#include "user/MyObj.h"


// Hilfsfunktion: Auf Return-Taste warten
void waitForReturn() {

    /* hier muss Code eingefuegt werden */

}


void heap_demo() {
		kout.clear();
		kout.setpos(0,0);
    kout << "Demo 1/4: 2 Objekte dynamisch allozieren" << endl;
    kout << "========================================" << endl;

    allocator.dump_free_memory();

    kout << "Allocating Object 1" << endl;
    MyObj* my1 = new MyObj(4, 'b');
    kout << "my1 Address: " << hex << my1 << "  myNum: " << dec << my1->myNum << "  myChar: "  << my1->myChar << endl;
    kout << endl;

    MyObj* my2 = new MyObj(10, 'a');
    kout << "Allocating Object 2" << endl;
    kout << "my2 Address: " << hex << my2 << "  myNum: " << dec << my2->myNum << "  myChar: "  << my2->myChar << endl;
    kout << endl;
    allocator.dump_free_memory();
		unsigned int* wrong = &total_mem;

		kout << "wrong: " << dec << *wrong << endl;
		kout << "total_mem location" << hex << &total_mem << endl;
		kout << "total_mem" << dec << total_mem << endl;
		kout << "Weiter mit <ENTER>" << endl;

    while(1){
        Key key = kb.key_hit();
        if(key.valid()){
					if((int) key.ascii() == 10){
						break;
					}
        }
    }

		kout.clear();
		kout.setpos(0,0);
    kout << "Demo 2/4: 2 Objekte wieder freigeben" << endl;
    kout << "========================================" << endl;
    allocator.dump_free_memory();

		kout << "Deleting Object 1 with Address: " << hex << my1 << endl;
		delete my1;

    allocator.dump_free_memory();

		kout << "Deleting Object 2 with Address: " << hex << my2 << endl;
		delete my2;

    allocator.dump_free_memory();
		kout << "Weiter mit <ENTER>" << endl;
}

