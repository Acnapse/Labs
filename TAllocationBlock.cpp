#include "TAllocationBlock.h"
#include <iostream>

TAllocationBlock::TAllocationBlock(size_t size, size_t count) : _size(size), _count(count) {
	_used_blocks = (char *)malloc(_size * _count);

	for (size_t i = 0; i < _count; ++i)
        _free_blocks.push_back(_used_blocks + i * size);
	_free_count = _count;
}

void * TAllocationBlock::allocate() {
    void * result = nullptr;

	if (!_free_blocks.empty()) {
        result = _free_blocks.popBack();
		_free_count--;
		std::cout << "TAllocationBlock: Allocate " << _count - _free_blocks.Size() << " " << _free_blocks.Size() << " of " << _count << std::endl;
	}

	return result;
}

void TAllocationBlock::deallocate(void * pointer) {
	
    _free_blocks.push_back(pointer); //[_free_count] = pointer;
	_free_count++;
}

bool TAllocationBlock::has_free_blocks() {
	return _free_count > 0;
}


TAllocationBlock::~TAllocationBlock() {
	if (_free_count < _count) std::cout << "TAllocationBlock: Memory Leak?" << std::endl;
	else std::cout << "TAllocationBlock: Memory freed" << std::endl;
    free(_used_blocks);
}
