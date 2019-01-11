#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Figure.h"
#include "BinaryTreeItem.h"
#include "Iterator.h"
#include <memory>

template <class T>
class BinaryTree {
public:

    BinaryTree();

    void push(const std::shared_ptr<T> &figure, size_t index);
    bool empty();
    std::shared_ptr<T> pop(size_t index);
    template <class A> friend std::ostream& operator<<(std::ostream& os, const BinaryTree<A>& tree);
    size_t GetCount();
    std::shared_ptr<BinaryTreeItem<T>> GetMax() const;
    std::shared_ptr<BinaryTreeItem<T>> GetMin() const;
    
    Iterator<BinaryTreeItem<T>, T> begin();
    Iterator<BinaryTreeItem<T>, T> end();

    virtual ~BinaryTree();

private:
    std::shared_ptr<BinaryTreeItem<T>> head;
    size_t count;
};

#endif


