/*****************************************************************************
 *                                                                           *
 *                                M A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Startroutine, wird direkt vom Bootlader angesprungen,    *
 *                  nachdem dieser in den Protected Mode geschaltet hat und  *
 *                  die GDT und IDT initalisiert hat.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 16.12.2016                      *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/CoopTaskDemo.h"


int main() {
    // Bildschirm loeschen.
    
    // Startmeldung ausgeben
    
    // Tastatur-Unterbrechungsroutine einstoepseln

    // Interrupts erlauben (Tastatur)

    // Anwendung im Scheduler anmelden
    /* Hier muss Code eingefuegt werden */
    
    // Scheduler starten
    scheduler.Scheduler::schedule ();

    return 0;
 }
