#ifndef TSTACKITEM_H
#define TSTACKITEM_H
#include <memory>
#include <thread>
#include <mutex>

template<class T> class TTreeItem {
public:
    TTreeItem(T *item, size_t index, std::recursive_mutex *parent);
    template<class A> friend std::ostream& operator<<(std::ostream& os, const TTreeItem<A>& obj);
    
    std::shared_ptr<TTreeItem<T>> SetLeft(std::shared_ptr<TTreeItem> left);
    std::shared_ptr<TTreeItem<T>> GetLeft();
    std::shared_ptr<TTreeItem<T>> SetRight(std::shared_ptr<TTreeItem> right);
    std::shared_ptr<TTreeItem<T>> GetRight();
    std::shared_ptr<TTreeItem<T>> SetParent(std::shared_ptr<TTreeItem> parent);
    std::shared_ptr<TTreeItem<T>> GetParent();
    void SetFlag();
    int GetFlag();
    std::shared_ptr<TTreeItem<T>> GetNext();
    std::shared_ptr<T> GetValue() const;
    size_t GetIndex() const;
    
    virtual ~TTreeItem();
private:
    std::shared_ptr<T> item;
    std::shared_ptr<TTreeItem<T>> left;
    std::shared_ptr<TTreeItem<T>> right;
    std::shared_ptr<TTreeItem<T>> parent;
    std::recursive_mutex *tree_mutex;
    int flag;
    size_t index;
    
};
#endif
