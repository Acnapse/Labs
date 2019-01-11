#ifndef IREMOVECRITERIA_HPP
#define IREMOVECRITERIA_HPP

template <class T> class IRemoveCriteria {
public:
    virtual bool isIt(T *value) = 0;
private:
    
};
#endif
