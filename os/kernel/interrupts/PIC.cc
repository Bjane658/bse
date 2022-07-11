/*****************************************************************************
 *                                                                           *
 *                                  P I C                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Mit Hilfe des PICs koennen Hardware-Interrupts (IRQs)    *
 *                  einzeln zugelassen oder unterdrueckt werden. Auf diese   *
 *                  Weise wird also bestimmt, ob die Unterbrechung eines     *
 *                  Geraetes ueberhaupt an den Prozessor weitergegeben wird. *
 *                  Selbst dann erfolgt eine Aktivierung der Unterbrechungs- *
 *                  routine nur, wenn der Prozessor bereit ist, auf Unter-   *
 *                  brechungen zu reagieren. Dies kann mit Hilfe der Klasse  *
 *                  CPU festgelegt werden.                                   *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *****************************************************************************/

#include "kernel/interrupts/PIC.h"
#include "kernel/IOport.h"
#include "devices/CGA_Stream.h"
#include "kernel/Globals.h"

//static IOport IMR1 (0x20);    // irr, isr, int.vect
//static IOport IMR1 (0xa0);    // irr, isr, int.vect

static IOport IMR1 (0x21);    // interrupt mask register von PIC 1
static IOport IMR2 (0xa1);    // interrupt mask register von PIC 2


/*****************************************************************************
 * Methode:         PIC::allow                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Sorgt dafuer, dass der uebergebene IRQ ab sofort durch   *
 *                  den PIC an den Prozessor weitergereicht wird. Um eine    *
 *                  Unterbrechungsbehandlung zu ermoeglichen, muss           *
 *                  zusaetzlich CPU::enable_int() aufgerufen werden.         *
 *                                                                           *
 * Parameter:                                                                *
 *      irq:        IRQ der erlaubt werden soll                              *
 *****************************************************************************/
void PIC::allow (int irq) {
    //IMR1.outb(0b11111101);
    //IMR2.outb(0b11111111);

    if(irq > 7 || irq < 0){
        return;
    }
    unsigned int imr1 = IMR1.inb();
    unsigned int imr2 = IMR2.inb();
    unsigned int imr = imr2 << 8 | imr1;

    unsigned int invertedAllowBit = 1 << irq;
    unsigned int result = ~((~imr) | invertedAllowBit);

    IMR1.outb(result);
    
}


/*****************************************************************************
 * Methode:         PIC::forbid                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Unterdrueckt mit Hilfe des PICs einen bestimmten IRQ.    *
 *                                                                           *
 * Parameter:                                                                *
 *      interrupt:  IRQ der maskiert werden soll                             *
 *****************************************************************************/
void PIC::forbid (int irq) {
    if(irq > 7 || irq < 0){
        return;
    }
    unsigned int imr1 = IMR1.inb();
    unsigned int imr2 = IMR2.inb();
    unsigned int imr = imr2 << 8 | imr1;
    //kout << "IMR: " << bin << imr << endl;

    unsigned int forbitBit = 1 << irq;
    unsigned int result = imr | forbitBit;
    //kout << "IMR: " << bin << result << endl;

    IMR1.outb(result);
}


/*****************************************************************************
 * Methode:         PIC::status                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Liefert den aktuellen Zustand des Maskierbits eines      *
 *                  bestimmten IRQs.                                         *
 *                                                                           *
 * Parameter:                                                                *
 *      irq:  IRQ dessen Status erfragt werden soll                          *
 *****************************************************************************/
bool PIC::status (int irq) {
    if(irq > 7 || irq < 0){
        return 0;
    }
    unsigned int imr1 = IMR1.inb();
    unsigned int imr2 = IMR2.inb();
    unsigned int imr = imr2 << 8 | imr1;
    
    unsigned int result = (imr >> irq) & 1;

    
    kout << "PIC Status for irq: " << dec << irq << "=> " << bin << result <<  endl;
    kout << "IMR: " << bin << imr << endl;

    //IMR1.outb(0b11111101);
    //IMR2.outb(0b11111111);

    //imr1 = IMR1.inb();
    //imr2 = IMR2.inb();
    //imr = imr2 << 8 | imr1;

    ///kout << "imr1: " << bin << imr1 << endl;
    //kout << "imr2: " << bin << imr2 << endl;

    //kout << "IMR: " << bin << imr << endl;

    return result;
}
 
