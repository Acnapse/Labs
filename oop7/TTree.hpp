#ifndef TTREE_HPP
#define TTREE_HPP

#include "TIterator.hpp"
#include "TTreeItem.hpp"
#include "IRemoveCriteria.hpp"
#include <memory>

template <class T, class TT> class TBinaryTree {
public:
    TBinaryTree();
    
    void InsertSubitem(std::shared_ptr<TT> item);
    void RemoveSubitem(IRemoveCriteria<TT> * criteria);
    void PushBack(T* value);
    bool Remove(T* value);
    size_t Size();
    
    TIterator<TBinaryTreeItem<T>,T> begin() const;
    TIterator<TBinaryTreeItem<T>,T> end() const;
    
    template <class A, class AA>
    friend std::ostream& operator<<(std::ostream& os,const TBinaryTree<A, AA>& tree);

    virtual ~TBinaryTree();
private:
    std::shared_ptr<TBinaryTreeItem<T>> root;
};

#endif
