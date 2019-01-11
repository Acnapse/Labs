#ifndef TSTACK_H
#define TSTACK_H

#include "TIterator.h"
#include "TBinaryTreeItem.h"
#include <memory>
#include <future>
#include <mutex>

template <class T> class TBinaryTree {
public:
    TBinaryTree();
    
    void push(T* item, size_t index);
    void push(std::shared_ptr<T> item, size_t index);
    bool empty();
    size_t size();
    
    TIterator<TBinaryTreeItem<T>,T> begin() const;
    TIterator<TBinaryTreeItem<T>,T> end() const;
    
    std::shared_ptr<T> operator[] (size_t i);
    void sort();
    void sort_parallel();
    
    void print(std::ostream& os, std::shared_ptr<TBinaryTreeItem<T> > item) const;
    std::shared_ptr<T> pop(size_t index);
    template <class A> friend std::ostream& operator<<(std::ostream& os,const TBinaryTree<A>& stack);
    virtual ~TBinaryTree();
    
    std::future<void> sort_in_background();
private:
    std::shared_ptr<TBinaryTreeItem<T> > head;
    size_t count;
};

#endif
