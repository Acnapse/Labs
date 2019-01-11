#ifndef BINARYTREEITEM_H
#define BINARYTREEITEM_H

#include <memory>
#include <iostream>
#include "TAllocationBlock.h"

template <class T>
class BinaryTreeItem {
public:
    BinaryTreeItem(const std::shared_ptr<T> &figure, size_t index);
    BinaryTreeItem(std::shared_ptr<BinaryTreeItem<T>> r);
    template <class A> friend std::ostream &operator<<(std::ostream &os, const BinaryTreeItem<A> &obj);

	std::shared_ptr<BinaryTreeItem<T>> SetLeft(std::shared_ptr<BinaryTreeItem<T>> left);
	std::shared_ptr<BinaryTreeItem<T>> SetRight(std::shared_ptr<BinaryTreeItem<T>> right);
    //std::shared_ptr<BinaryTreeItem<T>> SetParent(std::shared_ptr<BinaryTreeItem<T>> parent);
	std::shared_ptr<BinaryTreeItem<T>> GetLeft();
	std::shared_ptr<BinaryTreeItem<T>> GetRight();
    void * operator new (size_t size);
    void operator delete(void *p);
    BinaryTreeItem<T> GetNext();
    std::shared_ptr<T> GetFigure() const;
    size_t GetIndex();
    
    virtual ~BinaryTreeItem(){};
    
private:
    size_t index;
	std::shared_ptr<T> figure;
    //std::shared_ptr<BinaryTreeItem<T>> parent;
	std::shared_ptr<BinaryTreeItem<T>> left;
	std::shared_ptr<BinaryTreeItem<T>> right;
    
    static TAllocationBlock treeitem_allocator;
};

#endif
