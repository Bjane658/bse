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

	CoroutineLoop* loop1 = new CoroutineLoop(&stack[0][1024], 1);
	CoroutineLoop* loop2 = new CoroutineLoop(&stack[1][1024], 2);
	CoroutineLoop* loop3 = new CoroutineLoop(&stack[2][1024], 3);
	loop1->setNext(loop2);
	loop2->setNext(loop3);
	loop3->setNext(loop1);
	loop1->start();

}
