#include "DataFIFO.h"

DataFIFO::DataFIFO(size_t bufferSize, size_t maxBlocks) : bufferSize(bufferSize), maxBlocks(maxBlocks) {
	buffer = operator new(bufferSize);
}

DataFIFO::~DataFIFO() {
	operator delete(buffer);
}

void* DataFIFO::getFree(size_t size) {
	if (filled_blocks == maxBlocks || size > (bufferSize - left_offset) || size > (bufferSize - right_offset))
		return nullptr;
	std::lock_guard<std::mutex> guard(lock);
	
}


void DataFIFO::addFree(void* data) {
	if (data < buffer || data > static_cast<char*>(buffer) + bufferSize)
		return;

	std::lock_guard<std::mutex> guard(lock);
	this->data->state = Blocks_State::FILLED;
}


