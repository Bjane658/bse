/*****************************************************************************
 *                                                                           *
 *                                   P I T                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Programmable Interval Timer.                             *
 *                                                                           *
 * Autor:           Michael Schoettner, 3.7.2022                             *
 *****************************************************************************/

#include "devices/PIT.h"
#include "kernel/IOport.h"
#include "kernel/Globals.h"

static IOport PITCH0 (0x40);    // interrupt mask register von PIC 1
static IOport PITCMD (0x43);    // interrupt mask register von PIC 1


/*****************************************************************************
 * Methode:         PIT::interval                                            *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Zeitinervall programmieren.                              *
 *                                                                           *
 * Parameter:                                                                *
 *      us:         Zeitintervall in Mikrosekunden, nachdem periodisch ein   * 
 *                  Interrupt erzeugt werden soll.                           *
 *****************************************************************************/
void PIT::interval (int us) {
	timer_interval = us;
}

void PIT::dumpStatus(){
		//read back command f0r ch0
		PITCMD.outb(0b11100010);
		unsigned int ch0Status = PITCH0.inb();
		kout << "status: " << bin << ch0Status << endl;
}


/*****************************************************************************
 * Methode:         PIT::plugin                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Unterbrechungen fuer den Zeitgeber erlauben. Ab sofort   *
 *                  wird bei Ablauf des definierten Zeitintervalls die       *
 *                  Methode 'trigger' aufgerufen.                            *
 *****************************************************************************/
void PIT::plugin () {
		if(timer_interval > 0){
			int counter = (int) timer_interval/0.83809511038551;
			kout << "counter: " << counter << endl;
			int low = 0x00FF & counter;
			int high = counter >> 8;
			
			// set ch0 mode 3
			PITCMD.outb(0b00110110);
			PITCH0.outb(low);
			PITCH0.outb(high);
		}


    // in IntDispatcher registrieren
    kout << "plugin PIT" << endl;
    intdis.assign(intdis.time, *this);

    // in PIC Interrupts des Timer zulassen
    pic.allow(pic.timer);


}

void PIT::printClock(){
	int prevX = 0;
	int prevY = 0;
	kout.getpos(prevX, prevY);

	kout.setpos(0,0);
	switch(timer_char){
		case 0:
			kout << '|';
			break;
		case 1:
			kout << '/';
			break;
		case 2:
			kout << '-';
			break;
		case 3:
			kout << '\\';
			break;
		default:
			kout << '-';
	}
	timer_char = (timer_char + 1) % 4;
	kout.flush();
	kout.setpos(prevX, prevY);
}


/*****************************************************************************
 * Methode:         PIT::trigger                                             *
 *---------------------------------------------------------------------------*
 * Beschreibung:    ISR fuer den Zeitgeber. Wird aufgerufen, wenn der        * 
 *                  Zeitgeber eine Unterbrechung ausloest. Anzeige der Uhr   *
 *                  aktualisieren und Thread wechseln durch Setzen der       *
 *                  Variable 'forceSwitch', wird in 'int_disp' behandelt.    *
 *****************************************************************************/
void PIT::trigger () {
		if(systime % 100 == 0){
			printClock();
		}
    
    // alle 10ms, Systemzeit weitersetzen
    systime++;


    // Bei jedem Tick einen Threadwechsel ausloesen.
    // Aber nur wenn der Scheduler bereits fertig intialisiert wurde
    // und ein weiterer Thread rechnen moechte

    /* hier muss Code eingefuegt werden */
}



