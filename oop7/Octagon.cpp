#include "Octagon.hpp"
#include <iostream>
#include <cmath>

Octagon::Octagon() : Octagon(0) {}

Octagon::Octagon(size_t i) : side(i) {}

Octagon::Octagon(const Octagon& orig) {
    side = orig.side;
}

Octagon::Octagon(std::istream &is) {
    is >> side;
}

double Octagon::Square() const {
    return 2 * (double)side * (double)side * sqrt(1 + sqrt(2));
}

void Octagon::Print(std::ostream& os) const {
    os << "Octagon :  a = " << side << "\t\t\t\t\tSquare = " << Square();;
}

Octagon& Octagon::operator=(const Octagon& right) {
    
    if (this == &right) return *this;
    
    side = right.side;
    
    return *this;
}

Octagon& Octagon::operator++() {
    side++;
    return *this;
}

Octagon operator+(const Octagon& left, const Octagon& right) {
    
    return Octagon(left.side + right.side);
}

std::ostream& operator<<(std::ostream& os, const Octagon& obj) {
    os << "side = " << obj.side << "\t\tSquare = " << obj.Square();
    return os;
}


std::istream& operator>>(std::istream& is, Octagon& obj) {
    is >> obj.side;
    return is;
}
