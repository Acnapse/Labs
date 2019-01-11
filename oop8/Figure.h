#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <iostream>

class Figure {
public:
    virtual double Square() = 0;
    virtual void Print(std::ostream& os) const = 0;
    virtual size_t GetMark() = 0;
    friend std::ostream& operator<<(std::ostream& os, const Figure& obj) {
        obj.Print(os);
        return os;
    }
    
    friend std::istream& operator> >(std::istream& is, Figure& obj);
};

#endif
