#include "ImageFifo.h"
#include <string>
#include <iostream>

int main() {

	ImageFifo fifo(sizeof(int), 10);

	int* s = static_cast<int*>(fifo.getFree());
	*s = 4;
	fifo.addReady(s);
	s = static_cast<int*>(fifo.getReady());
	std::cout << *s << std::endl;
	fifo.addFree(s);

	return 0;
}