#ifndef TTREEITEM_HPP
#define TTREEITEM_HPP
#include <memory>

template<class T> class TBinaryTreeItem {
public:
    TBinaryTreeItem(T* value);
    
    std::shared_ptr<T> GetValue();
    size_t GetIndex();
    std::shared_ptr<TBinaryTreeItem<T>> GetLeft();
    void SetLeft(std::shared_ptr<TBinaryTreeItem<T>> left);
    std::shared_ptr<TBinaryTreeItem<T>> GetRight();
    std::shared_ptr<TBinaryTreeItem<T>> GetNext();
    void SetRight(std::shared_ptr<TBinaryTreeItem<T>> right);
    void SetPrev(std::weak_ptr<TBinaryTreeItem<T>> prev);
    void PushBack(std::shared_ptr<TBinaryTreeItem<T>> next);
    
    virtual ~TBinaryTreeItem();
private:
    std::shared_ptr<T> _value;
    std::shared_ptr<TBinaryTreeItem> left;
    std::shared_ptr<TBinaryTreeItem> right;

    size_t index;
};

#endif
