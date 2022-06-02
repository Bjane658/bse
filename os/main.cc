/*****************************************************************************
 *                                                                           *
 *                                M A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Startroutine, wird direkt vom Bootlader angesprungen,    *
 *                  nachdem dieser in den Protected Mode geschaltet hat und  *
 *                  die GDT und IDT initalisiert hat.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"



int main() {
    
    // Speicherverwaltung initialisieren
    allocator.init();

    // Bildschirm loeschen.
    kout.clear();
    kout.setpos(0,0);
    kout << "Enable Interrupts" << endl;
    
    // Tastatur-Unterbrechungsroutine 'einstoepseln'
    /* hier muss Code eingefuegt werden */
    kb.plugin();

    //Keyboard init in main statt in Keyboard.cc
    //intdis.assign(33, kb);
    pic.status(0);
    
    // Interrupts erlauben (Tastatur)
    cpu.enable_int();
  
    //key_irq_demo();
  
    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
 }
