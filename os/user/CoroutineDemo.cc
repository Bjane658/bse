/*****************************************************************************
 *                                                                           *
 *                      C O R O U T I N E D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstieg in eine Anwendung.                              *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/CoroutineDemo.h"
#include "user/CoroutineLoop.h"


// Stacks (koennen alternative auch per 'new' alloziert werden)
static unsigned int stack[3][1024];


/*****************************************************************************
 * Methode:         CoroutineDemo::main                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    main-Methode der Anwendung.                              *
 *****************************************************************************/
void CoroutineDemo::main () {

    /* 
     * Hier muss Code eingefuegt werden 
     *
     * Die 3 Koroutinen einrichten, verketten und die 1. starten
     *
     */

	CoroutineLoop* loop1 = new CoroutineLoop(stack[0], 1);
	CoroutineLoop* loop2 = new CoroutineLoop(stack[1], 2);
	CoroutineLoop* loop3 = new CoroutineLoop(stack[2], 3);
	loop1->setNext(loop2);
	loop2->setNext(loop3);
	loop3->setNext(loop1);
	loop1->start();





	/*
	unsigned int **sp = (unsigned int**)loop1->regs.esp;
	kout.setpos(0,11);
	CoroutineState* reg = &loop1->regs;
	unsigned int** regI = (unsigned int**) &loop1->regs;
	kout << "ebx addr: "<< hex << regI << " val: " << *regI <<  " valval: " << hex << **regI << endl;
	kout << "esi addr: "<< hex << ++regI << " val: " << *regI <<  " valval: " << hex << **regI << endl;
	kout << "edi addr: "<< hex << ++regI << " val: " << *regI <<  " valval: " << hex << **regI << endl;
	kout << "ebp addr: "<< hex << ++regI << " val: " << *regI <<  " valval: " << hex << **regI << endl;
	kout << "esp addr: "<< hex << ++regI << " val: " << *regI <<  " valval: " << hex << **regI << endl;
	sp = (unsigned int**)loop1->regs.esp;
	kout << "addr: "<< hex << sp << " val: " << *sp << endl;
	++sp;
	kout << "addr: "<< hex << sp << " val: " << *sp << endl;
	++sp;
	kout << "addr: "<< hex << sp << " val: " << *sp << endl;
	++sp;
	kout << "addr: "<< hex << sp << " val: " << *sp << endl;
	*/


}
