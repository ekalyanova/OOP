#pragma once
#include  <mutex>
#include <vector>

enum class Blocks_State {
	CLEAR, FILLED
};

struct Data {
	void* pointer;
	size_t size;
	Blocks_State state;
};

class DataFIFO {
	DataFIFO(size_t bufferSize, size_t maxBlocks);
	~DataFIFO();
	void * getFree(size_t size);
	void addReady(void * data);
	void * getReady(size_t & size);
	void addFree(void * data);
private:
	void* buffer;

	size_t right_offset{};
	size_t left_offset{};

	size_t filled_blocks{};
	
	std::mutex lock;

	Data* data;
	//std::vector<Data*> data;
		
	size_t bufferSize;
	size_t maxBlocks;
	size_t buf_offset;
	size_t to_read_offset;
	size_t to_write_offset;
};