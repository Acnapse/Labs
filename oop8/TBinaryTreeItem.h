#ifndef TSTACKITEM_H
#define TSTACKITEM_H
#include <memory>

template<class T> class TBinaryTreeItem {
public:
    TBinaryTreeItem(T *item, size_t index);
    TBinaryTreeItem(std::shared_ptr<T> item, size_t index);
    template<class A> friend std::ostream& operator<<(std::ostream& os, const TBinaryTreeItem<A>& obj);
    
    std::shared_ptr<TBinaryTreeItem<T> > SetLeft(std::shared_ptr<TBinaryTreeItem> left);
    std::shared_ptr<TBinaryTreeItem<T> > GetLeft();
    std::shared_ptr<TBinaryTreeItem<T> > SetRight(std::shared_ptr<TBinaryTreeItem> right);
    std::shared_ptr<TBinaryTreeItem<T> > GetRight();
    std::shared_ptr<TBinaryTreeItem<T> > SetParent(std::shared_ptr<TBinaryTreeItem> parent);
    std::shared_ptr<TBinaryTreeItem<T> > GetParent();
    std::shared_ptr<TBinaryTreeItem<T> > GetNext();
    std::shared_ptr<T> GetValue() const;
    size_t GetIndex() const;
    
    virtual ~TBinaryTreeItem();
private:
    std::shared_ptr<T> item;
    std::shared_ptr<TBinaryTreeItem<T> > left;
    std::shared_ptr<TBinaryTreeItem<T> > right;
    std::shared_ptr<TBinaryTreeItem<T> > parent;
    size_t index;
};

#endif    
