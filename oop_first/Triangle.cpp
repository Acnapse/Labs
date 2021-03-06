#include "Triangle.h"
#include <iostream>
#include <cmath>

Triangle::Triangle() : Triangle(0, 0, 0) {}

Triangle::Triangle(size_t i, size_t j, size_t k) : side_a(i), side_b(j), side_c(k) {}

Triangle::Triangle(const Triangle& orig) {
    side_a = orig.side_a;
    side_b = orig.side_b;
    side_c = orig.side_c;
}

Triangle::Triangle(std::istream &is) {
    is >> side_a;
    is >> side_b;
    is >> side_c;
}

double Triangle::Square() {
	double p = double(side_a + side_b + side_c) / 2.0;
	return sqrt(p * (p - double(side_a))*(p - double(side_b))*(p - double(side_c)));
}

void Triangle::Print(std::ostream& os) const {
    os << "Triangle:  a = " << side_a << ", b = " << side_b << ", c = " << side_c << "    ";

}

Triangle& Triangle::operator=(const Triangle& right) {
    
    if (this == &right) return *this;
    
    side_a = right.side_a;
    side_b = right.side_b;
    side_c = right.side_c;
    
    return *this;
}

Triangle& Triangle::operator++() {
    side_a++;
    side_b++;
    side_c++;
    return *this;
}

size_t Triangle::GetSide() {
    return this->side_a;
}

Triangle operator+(const Triangle& left, const Triangle& right) {
    Triangle tmp;
    tmp.side_a = left.side_a + right.side_a;
    tmp.side_b = left.side_b + right.side_b;
    tmp.side_c = left.side_c + right.side_c;
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const Triangle& obj) {
    os << "a = " << obj.side_a << ", b = " << obj.side_b << ", c = " << obj.side_c << std::endl;
    return os;
}


std::istream& operator>>(std::istream& is, Triangle& obj) {
    is >> obj.side_a;
    is >> obj.side_b;
    is >> obj.side_c;
    return is;
}

