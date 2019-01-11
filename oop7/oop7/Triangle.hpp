#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "Figure.hpp"
#include <cstdlib>
#include <iostream>

class Triangle : public Figure{
public:
    Triangle();
    Triangle(size_t i,size_t j,size_t k);
    Triangle(const Triangle& orig);
    
    friend std::ostream& operator<<(std::ostream& os, const Triangle& obj);
    
    double Square() const override;
    void Print(std::ostream& os) const override;
    
    bool operator==(const Triangle& other);
    Triangle& operator=(const Triangle& right);
    
    virtual ~Triangle();
private:
    size_t side_a;
    size_t side_b;
    size_t side_c;
};

#endif



