/*****************************************************************************
*                                                                           *
*                              Q U E U E                                    *
*                                                                           *
*---------------------------------------------------------------------------*
* Beschreibung:    Implementierung einer einfach verketteten Liste von      *
*                  Chain Objekten. Die Implementierung ist etwas trickreich *
*                  'tail' verweist naemlich nicht, wie oft ueblich, auf das *
*                  letzte Element der Liste, sondern auf den 'next' Zeiger  *
*                  des letzten Elements, bzw., solange die Liste noch leer  *
*                  ist, auf den 'head' Zeiger der Liste. Dadurch muss beim  *
*                  Anfuegen eines Elements an die Liste nicht ueberprueft   *
*                  werden, ob bereits Elemente in ihr enthalten sind. Beim  *
*                  Entfernen von Elementen kann auf die Fallunterscheidung  *
*                  allerdings nicht verzichtet werden.                      *
*                                                                           *
* Autor:           Olaf Spinczyk, TU Dortmund                               *
*****************************************************************************/


#include "lib/Queue.h"

void Queue::enqueue(Chain* item){
	tail = &item;
}

Chain* Queue::dequeue(){
	Chain* firstElement = head;
	if(head->next == 0){
		head = 0;
		tail = &head;
	}else{
		head = head->next;
	}
	return firstElement;
}

void Queue::remove(Chain* item){
}


