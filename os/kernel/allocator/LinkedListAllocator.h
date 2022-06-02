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

#ifndef __LinkedListAllocator_include__
#define __LinkedListAllocator_include__

#include "kernel/Allocator.h"


// Format eines freien Blocks
struct free_block {
    unsigned int size;
    struct free_block *next;
};

// freier Block und vorheriger freier Block
struct free_and_prev_free_block {
    struct free_block *prev;
    struct free_block *next;
};


class LinkedListAllocator : Allocator {
    
private:
      // freie Bloecke werden verkettet
      struct free_block *free_start;

      LinkedListAllocator(Allocator &copy); // Verhindere Kopieren
      struct free_and_prev_free_block findFreeFittingBlock(unsigned int req_size);
      struct free_and_prev_free_block findFreeBlocksInbetween(void* ptr);
      void consolidateFreeBlocks(struct free_block* prevFreeBlock, struct free_block* freeBlock);

public:
      LinkedListAllocator () { }

      void init ();        
      void dump_free_memory ();
      void* alloc (unsigned int req_size);
      void free (void *ptr);

};

#endif
