#ifndef IREMOVECRITERIAALL_HPP
#define IREMOVECRITERIAALL_HPP

#include "IRemoveCriteria.hpp"

template <class T> class IRemoveCriteriaAll : public IRemoveCriteria<T>{
public:
    IRemoveCriteriaAll(size_t mark) : _mark(mark){};
    bool isIt(T *value) override{
        return _mark == value->GetMark();
    }
private:
    size_t _mark;
};

#endif
