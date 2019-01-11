#ifndef IREMOVECRITERIABYVALUE_HPP
#define IREMOVECRITERIABYVALUE_HPP
#include "IRemoveCriteria.hpp"
#include <memory>

template <class T>
class IRemoveCriteriaBySquare : public IRemoveCriteria<T>{
public:
    IRemoveCriteriaBySquare(size_t value) : _value(value) {};
    bool isIt(T *value) override{
        return _value > value->Square();
    }
    
private:
    size_t _value;
};

#endif
