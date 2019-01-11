#ifndef TRIANGLE_H
#define    TRIANGLE_H
#include <cstdlib>
#include <iostream>
#include "Figure.hpp"

class Triangle : public Figure {
public:
    Triangle();
    Triangle(size_t i,size_t j,size_t k);
    Triangle(const Triangle& orig);
    
    friend std::ostream& operator<<(std::ostream& os, const Triangle& obj);
    
    bool operator==(const Triangle& other);
    bool operator<(const Triangle& other);
    bool operator>(const Triangle& other);
    bool operator<=(const Triangle& other);
    bool operator>=(const Triangle& other);
    operator double () const;
    
    double Square() const override;
    void Print(std::ostream& os) const override;
    
    Triangle& operator=(const Triangle& right);
    
    virtual ~Triangle();
private:
    size_t side_a;
    size_t side_b;
    size_t side_c;
};

#endif    /* TRIANGLE_H */
