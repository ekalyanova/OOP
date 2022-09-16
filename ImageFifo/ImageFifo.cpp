#include "ImageFifo.h"

ImageFifo::ImageFifo(size_t blockSize, size_t maxBlocks): _blockSize(blockSize), _maxBlocks(maxBlocks)
{
	_buff = operator new[]((blockSize * maxBlocks));
	_filledBlocks = new State[maxBlocks];
}

ImageFifo::~ImageFifo()
{
	operator delete[](_buff);
	operator delete[](_filledBlocks);
}

void * ImageFifo::getFree()
{
	return _findBlock(_clearPos, State::FREE);
}

void ImageFifo::addReady(void * data)
{
	_addBlock(_readyPos, State::READY, data);
}


void * ImageFifo::getReady()
{
	return _findBlock(_readyPos, State::READY);
}


void ImageFifo::addFree(void * data)
{
	_addBlock(_clearPos, State::FREE, data);
}

void * ImageFifo::_findBlock(size_t &pos, State state)
{
	if (pos == _maxBlocks)
		return nullptr;

	std::lock_guard<std::mutex> locker(_lock);

	void* obj = reinterpret_cast<char*>(_buff) + pos * _blockSize;
	_filledBlocks[pos] = static_cast<State>(state + 1);

	if (pos == _maxBlocks - 1)
		pos = 0;
	for (; pos < _maxBlocks; pos++)
		if (_filledBlocks[pos] == state)
			break;

	return obj;
}

void ImageFifo::_addBlock(size_t & currentPos, State state, void * data)
{
	const size_t pos = (size_t(data) - size_t(_buff)) / _blockSize;

	if (pos >= _maxBlocks)
		return;

	if ((state == State::ON_WRITE && _filledBlocks[pos] != State::READY) || _filledBlocks[pos] == state)
		return;

	std::lock_guard<std::mutex> locker(_lock);
	_filledBlocks[pos] = state;

	if (currentPos == _maxBlocks)
		currentPos = pos;
}