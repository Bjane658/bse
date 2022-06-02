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
#include "user/TextDemo.h"
#include "user/soundDemo.h"


int main() {
    // Bildschirm loeschen.
	kout.clear();

    // Bildschirmausgabe testen (Strings, hex, dec, ...)
    
	textDemo();
    
    // PC-Lautsprecher testen

	soundDemo();

    return 0;
 }
