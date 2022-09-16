#pragma once
#include <mutex>

class ImageFifo final
{
public:
	ImageFifo(size_t blockSize, size_t maxBlocks);
	~ImageFifo();

	void* getFree();
	void addReady(void * data);
	void* getReady();
	void addFree(void *data);
	
private:
	std::mutex _lock;

	enum State {
		FREE,
		FILLED,
		READY,
		ON_WRITE
	};
	
	void*	_findBlock(size_t &pos, State state);
	void	_addBlock(size_t &pos, State state, void* data);

	State*	_filledBlocks;
	void*	_buff;

	size_t	_clearPos = 0;
	size_t	_readyPos = 0;

	size_t	_blockSize;
	size_t	_maxBlocks;

};