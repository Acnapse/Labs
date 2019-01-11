#ifndef TTree_H
#define TTree_H

#include "TIterator.h"
#include "TTreeItem.hpp"
#include <memory>
#include <future>
#include <mutex>
#include <thread>

template <class T> class TTree {
public:
    TTree();
    
    void push(T* item, size_t index);
    bool empty();
    size_t size();
    
    TIterator<TTreeItem<T>, T> begin() const;
    TIterator<TTreeItem<T>, T> end() const;
    
    std::shared_ptr<T> operator[] (size_t i);
    
    std::shared_ptr<T> pop(std::shared_ptr<T> item);
    void Get();
    void walk(std::shared_ptr<TTreeItem<T>>, int fl);
    void Change(TIterator<TTreeItem<T>, T> item);
//    int Find (std::shared_ptr<T> item);
    template <class A> friend std::ostream& operator<<(std::ostream& os,const TTree<A>& tree);
    void RemoveSubitem(int32_t value);
    virtual ~TTree();
private:
    std::recursive_mutex tree_mutex;
    size_t count;
    std::shared_ptr<TTreeItem<T>> root;
    
};

#endif    /* TTree_H */
