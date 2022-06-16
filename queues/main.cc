#include <iostream>
using namespace std;

#include "lib/Chain.h"
#include "lib/Queue.h"




int main() {
	Chain* ch1 = new Chain();
	Chain* ch2 = new Chain();

	Queue* queue = new Queue();
	queue->enqueue(ch1);



  return 0;
} 
