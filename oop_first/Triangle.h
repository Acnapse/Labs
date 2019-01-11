#ifndef TRIANGLE_H
#define	TRIANGLE_H
#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Triangle : public Figure{
public:
    Triangle();
    Triangle(size_t i, size_t j, size_t k);
    Triangle(const Triangle& orig);
    Triangle(std::istream &is);
    
    Triangle& operator++();
    Triangle& operator=(const Triangle& right);
    double Square() override;
    void Print(std::ostream& os) const override;
    friend Triangle operator+(const Triangle& left, const Triangle& right);
    size_t GetSide() override;
    
    friend std::ostream& operator<<(std::ostream& os, const Triangle& obj);
    friend std::istream& operator>>(std::istream& is, Triangle& obj);

private:
	size_t side_a;
	size_t side_b;
	size_t side_c;
};

#endif


