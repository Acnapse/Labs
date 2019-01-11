#ifndef Iterator_h
#define Iterator_h

#include <iostream>
#include <memory>

template <class node, class T>
class Iterator {
private:
    std::shared_ptr<node> node_ptr;
public:
    Iterator(std::shared_ptr<node> n) {
        node_ptr = n;
    }
    
    std::shared_ptr<T> operator* () {
        return node_ptr->GetFigure();
    }

    std::shared_ptr<T> operator-> () {
    	return node_ptr->GetFigure();
    }
    
    void operator++ () {
        node_ptr->GetNext();
    }
    
    Iterator operator ++ (int) {
        Iterator iter(*this);
        ++(*this);
        return iter;
    }
    
    bool operator == (Iterator const& i) {
        return node_ptr->GetIndex() == i.node_ptr->GetIndex();
    }
    
    bool operator != (Iterator const& i) {
        return !(*this == i);
    }
};

#endif
