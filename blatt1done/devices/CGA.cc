/*****************************************************************************
 *                                                                           *
 *                                    C G A                                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Mit Hilfe dieser Klasse kann man auf den Bildschirm des  *
 *                  PCs zugreifen. Der Zugriff erfolgt direkt auf der Hard-  *
 *                  wareebene, d.h. ueber den Bildschirmspeicher und den     *
 *                  I/O-Ports der Grafikkarte.                               *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *                  Aenderungen von Michael Schoettner, HHU, 21.8.2016       *
 *****************************************************************************/
#include "devices/CGA.h"
#include "kernel/IOport.h"


/*****************************************************************************
 * Methode:         CGA::setpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Setzen des Cursors in Spalte x und Zeile y.              *
 *****************************************************************************/
void CGA::setpos (int x, int y) {
	unsigned short cursor_address = (x + y * 80);

	IOport indexRegister(0x3d4);
	IOport dataRegister(0x3d5);

	indexRegister.outb(15);
	dataRegister.outb(cursor_address & 0xff);
	
	indexRegister.outb(14);
	dataRegister.outb(cursor_address >> 8 & 0xff);
}


/*****************************************************************************
 * Methode:         CGA::getpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Abfragem der Cursorposition                              *
 *                                                                           *
 * Rückgabewerte:   x und y                                                  *
 *****************************************************************************/
void CGA::getpos (int &x, int &y) {
	IOport indexRegister(0x3d4);
	indexRegister.outb(14);

	IOport dataRegister(0x3d5);
	char curPosHigh = dataRegister.inb();

	indexRegister.outb(15);
	const char curPosLow = dataRegister.inb();

	int pos = (curPosHigh & 0xff) << 8 | (curPosLow & 0xff);
	x = pos % 80;
	y = pos / 80;
}


/*****************************************************************************
 * Methode:         CGA::show                                                *
 *--------------------------------------------------------------------------*
 * Beschreibung:    Anzeige eines Zeichens mit Attribut an einer bestimmten  *
 *                  Stelle auf dem Bildschirm.                               *
 *                                                                           *
 * Parameter:                                                                *
 *      x,y         Position des Zeichens                                    *
 *      character   Das auszugebende Zeichen                                 *
 *      attrib      Attributbyte fuer das Zeichen                            *
 *****************************************************************************/
void CGA::show (int x, int y, char character, unsigned char attrib) {
	char *CGA_START = (char *)0xb8000;
	char *pos;

	pos = CGA_START + 2*(x + y*80);
	*pos = character;
	*(pos + 1) = attrib;
}

/*****************************************************************************
 * Methode:         CGA::getchar                                             *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Abfragem des Char an Position                            *
 *                                                                           *
 * Rückgabewerte:   char                                                     *
 *****************************************************************************/
unsigned char CGA::getchar(int x, int y){
	char *CGA_START = (char *)0xb8000;
	char *pos;

	pos = CGA_START + 2*(x + y*80);
	return *pos;
}


/*****************************************************************************
 * Methode:         CGA::print                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Anzeige mehrerer Zeichen ab der aktuellen Cursorposition *
 *                  '\n' fuer Zeilenvorschub.                                *
 *                                                                           *
 * Parameter:                                                                *
 *      string      Auszugebende Zeichenkette                                *
 *      n           Laenger der Zeichenkette                                 *
 *      attrib      Attributbyte fuer alle Zeichen der Zeichenkette          *
 *****************************************************************************/
void CGA::print (char* string, int n, unsigned char attrib) {
	int x;
	int y;

	getpos(x,y);

	for(int i=0; i<n; i++){
		if(string[i] == '\n'){
			x = 0;
			y = y+1;
			setpos(x,y);
			continue;
		}
		if(x > 79){
			x = 0;
			y = y+1;
		}
		if(y > 24){
			scrollup();
			y = y-1;
		}
		show(x,y, string[i], attrib);
		x = x + 1;
		setpos(x,y);
	}
}


/*****************************************************************************
 * Methode:         CGA::scrollup                                            *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Verschiebt den Bildschirminhalt um eine Zeile nach oben. *
 *                  Die neue Zeile am unteren Bildrand wird mit Leerzeichen  *
 *                  gefuellt.                                                *
 *****************************************************************************/
void CGA::scrollup () {
	unsigned char showAttribute = attribute(color::BLACK, color::WHITE, 0);
	for(int y = 1; y < 25; y++){
		for(int x = 0; x < 80; x++){
			if(y < 25){
				unsigned char value = getchar(x,y);
				//unsigned char attribute = getAttribute(x,y);
				show(x, y - 1, value, showAttribute);
			}
			show(x, y, ' ', showAttribute);
		}
	}

    
    
}


/*****************************************************************************
 * Methode:         CGA::clear                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Lösche den Textbildschirm.                               *
 *****************************************************************************/
void CGA::clear () {
	for(int y=0; y<25; y++){
		for(int x=0; x<80; x++){
			show(x,y, 255, attribute(color::BLACK, color::BLACK, 0));
		}
	}
}


/*****************************************************************************
 * Methode:         CGA::attribute                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Hilfsfunktion zur Erzeugung eines Attribut-Bytes aus     *
 *                  Hintergrund- und Vordergrundfarbe und der Angabe, ob das *
 *                  Zeichen blinkend darzustellen ist.                       *
 *                                                                           *
 * Parameter:                                                                *
 *      bg          Background color                                         *
 *      fg          Foreground color                                         *
 *      blink       ywa/no                                                   *
 *****************************************************************************/
unsigned char CGA::attribute (CGA::color bg, CGA::color fg, bool blink) {
	return (blink << 6) + (bg << 3) + fg;
}
