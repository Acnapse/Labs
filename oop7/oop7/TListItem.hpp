#ifndef TLISTITEM_HPP
#define TLISTITEM_HPP
#include <memory>
#include <thread>
#include <mutex>

template <class T> class TListItem {
public:
    TListItem(std::shared_ptr<T> item, std::recursive_mutex *parent);
    template<class A> friend std::ostream& operator<<(std::ostream& os, const TListItem<A>& obj);
    
    std::shared_ptr<T> GetValue() const;
    std::shared_ptr<TListItem<T>> GetNext();
    std::shared_ptr<TListItem<T>> GetPrev();
    std::shared_ptr<TListItem<T>> SetNext(std::shared_ptr<TListItem> &next);
    std::shared_ptr<TListItem<T>> SetPrev(std::shared_ptr<TListItem> &prev);
    
    virtual ~TListItem();
private:
    std::shared_ptr<T> _value;
    std::shared_ptr<TListItem> _next;
    std::shared_ptr<TListItem> _prev;
    std::recursive_mutex *list_mutex;
};

#endif

