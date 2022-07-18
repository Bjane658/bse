

#include "user/BluescreenWriteProtection.h"
#include "kernel/Paging.h"
#include "kernel/Globals.h"


void BluescreenWriteProtection::run () {

		unsigned int* p1 = pg_alloc_page();
		*p1 = 0x10;
		pg_write_protect_page(p1);
		//pg_notpresent_page(p1);

		kout << "p1 address: " << hex << p1 << endl;
		kout << "p1 value: " << hex << *p1 << endl;
		*p1 = 0x11;
		unsigned int* p4 = (unsigned int*) 0xbffffc;
		*p4 = 0x11;
		kout << "p4 address: " << hex << p4 << endl;
		kout << "p4 value: " << hex << *p4 << endl;

		unsigned int* p2 = pg_alloc_page();
		//*p2 = 0x22;
		kout << "p2 address: " << hex << p2 << endl;
		kout << "p2 value: " << hex << *p2 << endl;

		unsigned int* p3 = pg_alloc_page();
		*p3 = 0x33;
		kout << "p3 address: " << hex << p3 << endl;
		kout << "p3 value: " << hex << *p3 << endl;

		unsigned int* pt5 = (unsigned int*) allocator.alloc(8);
		kout << "[pt5]: " << hex << pt5 << endl;
		unsigned int* pt6 = (unsigned int*) allocator.alloc(8);
		kout << "[pt6]: " << hex << pt6 << endl;

   
}
