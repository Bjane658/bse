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
#include "kernel/Globals.h"

void Queue::enqueue(Chain* item){
	*tail = item;
	tail = &item->next;
}

Chain* Queue::dequeue(){
	Chain* firstElement = head;
	if(head->next == 0){
		head = 0;
		tail = &head;
	}else{
		head = head->next;
	}
	firstElement->next = 0;
	return firstElement;
}

void Queue::remove(Chain* item){
	Chain* prevElement = 0;
	Chain* element = head;
	while(element != 0){
		if(element == item){
			if(element == head && (void*)element == (void*)tail){
				head = 0;
				tail = &head;
			}else if(element == head){
				head = element->next;
			}else if((void*)element == (void*)tail){
				prevElement->next = 0;
				*tail = prevElement;
				tail = &prevElement->next;
			}else{
				prevElement->next = element->next;
			}
			item->next = 0;
			break;
		}
		prevElement = element;
		element = element->next;
	}
}

void Queue::dump(bool verbose){
	//kout.clear();
	kout.setpos(0,15);
	if(verbose){
		kout << "Queue Dump:" << endl;
		kout << "head: " << hex << head << " head Address: " << hex << &head << endl;
		kout << "head->next: " << hex << head->next << " head->next Address: " << hex << &head->next << endl;
		kout << "tail: " << hex << tail << " tail Address: " << hex << &tail << endl;
		kout << "*tail: " << hex << *tail << endl;
	}
	kout << hex << head;
	Chain* next = head->next;
	while(next != 0){
		kout << "->" << hex << next;
		next = next->next;
	}
	kout << endl;
}

bool Queue::is_empty(){
	if(head == 0){
		return true;
	}
	return false;
}

int Queue::count(){
	int counter = 0;
	if(is_empty()){
		return counter;
	}
	counter += 1;
	Chain* next = head->next;
	while(next != 0){
		counter += 1;
		next = next->next;
	}
	return counter;
}


