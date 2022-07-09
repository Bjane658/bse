/*****************************************************************************
 *                                                                           *
 *                                   P I T                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Programmable Interval Timer.                             * 
 *                                                                           *
 * Autor:           Michael Schoettner, 23.8.2016                            *
 *****************************************************************************/

#ifndef __PIT_include__
#define __PIT_include__

#include "kernel/interrupts/ISR.h"

class PIT : public ISR {
    
private:
    PIT(const PIT &copy); // Verhindere Kopieren
         
private:
    enum { time_base = 838 };  /* ns */
    int timer_interval;
		int timer_char;
		void printClock();
		void dumpStatus();

public:
		unsigned int clockChar = 0;
    // Zeitgeber initialisieren.
    PIT (int us) {
        interval (us);
    }
    
    // Konfiguriertes Zeitintervall auslesen.
    int interval () {
        return timer_interval;
    }
    
    // Zeitintervall in Mikrosekunden, nachdem periodisch ein Interrupt
    //erzeugt werden soll.
    void interval (int us);

    // Aktivierung der Unterbrechungen fuer den Zeitgeber
    void plugin ();
    
    // Unterbrechnungsroutine des Zeitgebers.
    void trigger ();
};

#endif
