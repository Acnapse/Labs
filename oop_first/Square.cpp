#include "Square.h"
#include <iostream>
#include <cmath>

FSquare::FSquare() : FSquare(0) {}

FSquare::FSquare(size_t i) : side(i) {}

FSquare::FSquare(const FSquare& orig) {
    side = orig.side;
}

FSquare::FSquare(std::istream &is) {
    is >> side;
}

double FSquare::Square(){
	return (double)side * (double)side;
}

void FSquare::Print(std::ostream& os) const {
    os << "Square  :  a = " << side << "                   ";
}

FSquare& FSquare::operator=(const FSquare& right) {
    
    if (this == &right) return *this;
    
    side = right.side;
    
    return *this;
}

FSquare& FSquare::operator++() {
    side++;
    return *this;
}

size_t FSquare::GetSide() {
    return this->side;
}

FSquare operator+(const FSquare& left, const FSquare& right) {
    
    return FSquare(left.side + right.side);
}

std::ostream& operator<<(std::ostream& os, const FSquare& obj) {
    os << "side = " << obj.side;
    return os;
}


std::istream& operator>>(std::istream& is, FSquare& obj) {
    is >> obj.side;
    return is;
}
