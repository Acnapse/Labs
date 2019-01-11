#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <cstdlib>
#include <iostream>
#include "Figure.hpp"

class FSquare : public Figure {
public:
    FSquare();
    FSquare(size_t i);
    FSquare(const FSquare& orig);
    FSquare(std::istream &is);
    
    FSquare& operator++();
    FSquare& operator=(const FSquare& right);
    double Square() const override;
    void Print(std::ostream& os) const override;
    friend FSquare operator+(const FSquare& left, const FSquare& right);
    
    friend std::ostream& operator<<(std::ostream& os, const FSquare& obj);
    friend std::istream& operator>>(std::istream& is, FSquare& obj);
    
private:
    size_t side;
};


#endif
