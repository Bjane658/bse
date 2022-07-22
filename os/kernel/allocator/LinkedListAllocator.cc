/*****************************************************************************
 *                                                                           *
 *                  L I N K E D L I S T A L L O C A T O R                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einfache Speicherverwaltung, welche den freien Speicher  *
 *                  mithilfe einer einfach verketteten Liste verwaltet.      *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 13.6.2020                        *
 *****************************************************************************/

#include <stddef.h>
#include "kernel/Globals.h"
#include "kernel/allocator/LinkedListAllocator.h"

#define HEAP_MIN_FREE_BLOCK_SIZE 64         // min. Groesse eines freien Blocks
#define HEAP_BLOCK_SIZE_INFO 4         // 4 Byte Size Info eines belegten Blocks


/*****************************************************************************
 * Methode:         LinkedListAllocator::init                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Liste der Freispeicherbloecke intitialisieren.           *
 *                  Anker zeigt auf ein Dummy-Element. Danach folgt          *
 *                  ein Block der den gesamten freien Speicher umfasst.      *
 *                                                                           *
 *                  Wird automatisch aufgerufen, sobald eine Funktion der    *
 *                  Speicherverwaltung erstmalig gerufen wird.               *
 *****************************************************************************/
void LinkedListAllocator::init() {
	kout << "heap_start: " << hex << heap_start << endl;
	kout << "total_mem: " << total_mem << endl;
	kout << "free_start: " << hex << free_start <<endl;
	kout << "free_start addr: " << hex << &free_start <<endl;

    struct free_block* first_free_block = (free_block*) heap_start;
    *first_free_block = { heap_size, 0 };

		free_start_value = { 0, first_free_block };
		kout << "free_start_value address: " << hex << &free_start_value << endl;
		kout << "first_free_block address: " << hex << &first_free_block << endl;
    free_start = &free_start_value;
    
    /*
    kout << "free start: " << hex << free_start << "    size: " << dec << free_start->size << " next free Address: " << hex << free_start->next << endl;
    kout << "free_block size: " << dec << sizeof (struct free_block) << endl;

    dump_free_memory();
    */
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::dump_free_memory                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherliste. Zu Debuggingzwecken.      *
 *****************************************************************************/
void LinkedListAllocator::dump_free_memory() {
    struct free_block* currentFreeBlock = free_start->next;
    unsigned int blocks = 0;

    kout << "======== free memory dump ======" << "Anker next Address: " << hex << free_start->next << endl;
    while(true)
    {
        blocks++;
        kout << "free Block" << dec << blocks << "  From: " << hex << currentFreeBlock << " To: " << hex << (void *) currentFreeBlock + currentFreeBlock->size << endl;
        kout << "  size: " << dec << currentFreeBlock->size << "   next: " << hex << currentFreeBlock->next << endl;
        if(currentFreeBlock->next == 0) break;
        currentFreeBlock = currentFreeBlock->next;
    };

    kout << "======== =============== ======" << endl;

}

struct free_and_prev_free_block LinkedListAllocator::findFreeFittingBlock(unsigned int req_size){
    struct free_block* currentFreeBlock = free_start->next;
    struct free_block* prevFreeBlock = NULL;

    while(currentFreeBlock->size < req_size + 32)
    {
        if(currentFreeBlock->next == 0){
            currentFreeBlock = NULL;
            break;
        }
        prevFreeBlock = currentFreeBlock;
        currentFreeBlock = currentFreeBlock->next;
    }
    
    return {prevFreeBlock, currentFreeBlock};
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::alloc                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * LinkedListAllocator::alloc(unsigned int req_size) {
    struct free_and_prev_free_block freeAndPrevFreeBlock = findFreeFittingBlock(req_size);

    //kout << "======== alloc ======" << endl;
    //kout << "first free fitting block address: " << hex << freeAndPrevFreeBlock.next << endl;
    //kout << "prev free fitting block address: " << hex << freeAndPrevFreeBlock.prev << endl;

    struct free_block* newFreeBlock = (free_block*)(((void *) freeAndPrevFreeBlock.next) + HEAP_BLOCK_SIZE_INFO + req_size);
    //kout << " new free block addresse: " << hex << newFreeBlock << endl;
    newFreeBlock->size = freeAndPrevFreeBlock.next->size - (HEAP_BLOCK_SIZE_INFO + req_size);
    newFreeBlock->next = freeAndPrevFreeBlock.next->next;

    unsigned int * allocatedStart = (unsigned int *) freeAndPrevFreeBlock.next;
    *allocatedStart = req_size;

    //kout << "allocatedStart Address: " << hex << allocatedStart << endl;
    //kout << "allocatedStart size: " << dec << *allocatedStart << endl;
    //kout << "allocatedStart return Address: " << hex << (void *) allocatedStart + HEAP_BLOCK_SIZE_INFO << endl;
    

    if(freeAndPrevFreeBlock.prev == 0 || freeAndPrevFreeBlock.prev == free_start->next){
				free_start_value = {0, newFreeBlock};
        free_start = &free_start_value;
    
    }else{
        freeAndPrevFreeBlock.prev->next = newFreeBlock;
    }

    

    //kout << "======== ====== ======" << endl;
  
    return (void *) allocatedStart + HEAP_BLOCK_SIZE_INFO;
}

struct free_and_prev_free_block LinkedListAllocator::findFreeBlocksInbetween(void* ptr){
    struct free_block* currentFreeBlock = free_start->next;
    struct free_block* prevFreeBlock = NULL;

    while(((prevFreeBlock < ptr) && (ptr < currentFreeBlock)) != 1)
    {
        //kout << "inside while" << endl;
        if(currentFreeBlock->next == 0){
            currentFreeBlock = NULL;
            break;
        }
        prevFreeBlock = currentFreeBlock;
        currentFreeBlock = currentFreeBlock->next;
    }
    return {prevFreeBlock, currentFreeBlock};
};

void LinkedListAllocator::consolidateFreeBlocks(struct free_block* prevFreeBlock, struct free_block* freeBlock){
		if(prevFreeBlock == 0){
			return;
		}

    void* prevFreeBlockNextBlockAddress = (void* )prevFreeBlock + prevFreeBlock->size;
    void* freeBlockNextBlockAddress = (void*) freeBlock + freeBlock->size;

    if(freeBlockNextBlockAddress == freeBlock->next){
        freeBlock->size = freeBlock->size + freeBlock->next->size;
        freeBlock->next = freeBlock->next->next;
    }
    
    if(prevFreeBlockNextBlockAddress == freeBlock){
        prevFreeBlock->next = freeBlock->next;
        prevFreeBlock->size = prevFreeBlock->size + freeBlock->size;
    }
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::free                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen Speicherblock freigeben.                           *
 *****************************************************************************/
void LinkedListAllocator::free(void *ptr) {
    const void* startAddress = ptr - HEAP_BLOCK_SIZE_INFO;
    const unsigned int allocatedSize = *(unsigned int*) startAddress + HEAP_BLOCK_SIZE_INFO;
    struct free_block* newFreeBlock = (free_block*) startAddress;
    *newFreeBlock = {allocatedSize};


    struct free_and_prev_free_block freeBlocksAround = findFreeBlocksInbetween((void*)newFreeBlock);

    if(freeBlocksAround.prev == 0){
        newFreeBlock->next = freeBlocksAround.next;
        free_start->next = newFreeBlock;
        consolidateFreeBlocks(freeBlocksAround.prev, newFreeBlock);
        return;
    }

    newFreeBlock->next = freeBlocksAround.next;
    freeBlocksAround.prev->next = newFreeBlock;

    consolidateFreeBlocks(freeBlocksAround.prev, newFreeBlock);

}

