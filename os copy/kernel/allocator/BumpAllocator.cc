/*****************************************************************************
 *                                                                           *
 *                        B U M P A L L O C A T O R                          *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Eine sehr einfache Heap-Verwaltung, welche freigegebenen *
 *                  Speicher nicht mehr nutzen kann.                         *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 3.3.2022                        *
 *****************************************************************************/

#include <stddef.h>
#include "kernel/Globals.h"
#include "kernel/allocator/LinkedListAllocator.h"


/*****************************************************************************
 * Methode:         BumpAllocator::init                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    BumpAllokartor intitialisieren.                          *
 *****************************************************************************/
void BumpAllocator::init() {
    next = (unsigned char *) heap_start;
    allocations = 0;
}


/*****************************************************************************
 * Methode:         BumpAllocator::dump_free_memory                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherinfos. Zu Debuggingzwecken.      *
 *****************************************************************************/
void BumpAllocator::dump_free_memory() {
    kout << "heap_start: " << hex << heap_start << "    heap_end: " << hex << heap_end  << "    heap_size: " << hex << heap_size << endl;
    kout << "next free address: " << hex << next << "   allocations: " << dec << allocations << endl;
    kout << endl;
}


/*****************************************************************************
 * Methode:         BumpAllocator::alloc                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * BumpAllocator::alloc(unsigned int req_size) {
    if((unsigned int)(next + req_size) > heap_end) return (void *) -1;

    void * req_address = (void *) next;
    next = next + req_size;
    allocations += 1;


    return req_address;
}


/*****************************************************************************
 * Methode:         BumpAllocator::free                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Nicht implementiert.                                     *
 *****************************************************************************/
void BumpAllocator::free(void *ptr) {
    kout << "   mm_free: ptr= " << hex << (unsigned int)ptr << ", not supported" << endl;
}

