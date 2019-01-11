#ifndef TLIST_HPP
#define TLIST_HPP
#include <memory>
#include "TListItem.hpp"
#include "TIterator.hpp"
#include <future>
#include <mutex>
#include <thread>

template <class T> class TList {
public:
    TList();
    
    void push(std::shared_ptr<T> value);
    bool empty();
    size_t Size();
    
    TIterator<TListItem<T>, T> begin() const;
    TIterator<TListItem<T>, T> end() const;
    
    std::shared_ptr<T> operator[] (size_t i);
    
    std::shared_ptr<T> pop();
    template <class A>
    friend std::ostream& operator<<(std::ostream& os,const TList<A>& list);
    
    virtual ~TList();
private:
    std::shared_ptr<TListItem<T>> head;
    std::shared_ptr<TListItem<T>> last;
    size_t count;
    
    std::recursive_mutex list_mutex;
};

#endif
