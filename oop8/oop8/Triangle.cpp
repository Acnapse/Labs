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

bool Triangle::operator==(const Triangle& other) {
    return (side_a == other.side_a)&&(side_b == other.side_b)&&(side_c == other.side_c);
}

double Triangle::Square() {
    double p = double(side_a + side_b + side_c) / 2.0;
    double res = sqrt(p * (p - double(side_a))*(p - double(side_b))*(p - double(side_c)));
    return res;
}

Triangle& Triangle::operator=(const Triangle& right) {
    
    if (this == &right) return *this;
    
    std::cout << "Triangle copied" << std::endl;
    side_a = right.side_a;
    side_b = right.side_b;
    side_c = right.side_c;
    
    return *this;
}

bool Triangle::operator<(const Triangle& other) {
    return (double) (*this)<(double) (other);
}

bool Triangle::operator>(const Triangle& other) {
    return double(*this)>double(other);
}

bool Triangle::operator<=(const Triangle& other) {
    return double(*this) <= double(other);
}

bool Triangle::operator>=(const Triangle& other) {
    return double(*this) >= double(other);
}

Triangle::operator double () const {
    double p = double(side_a + side_b + side_c) / 2.0;
    return sqrt(p * (p - double(side_a))*(p - double(side_b))*(p - double(side_c)));
}

Triangle::~Triangle() {}

std::ostream& operator<<(std::ostream& os, const Triangle& obj) {
    
    os << " a = " << obj.side_a << ", b = " << obj.side_b << ", c = " << obj.side_c << "\t\tSquare = " << double(obj);
    return os;
}
