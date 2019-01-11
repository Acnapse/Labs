#ifndef OCTAGON_HPP
#define OCTAGON_HPP
#include <cstdlib>
#include <iostream>
#include "Figure.hpp"

class Octagon : public Figure {
public:
    Octagon();
    Octagon(size_t i);
    Octagon(const Octagon& orig);
    Octagon(std::istream &is);
    
    Octagon& operator++();
    Octagon& operator=(const Octagon& right);
    double Square() const override;
    void Print(std::ostream& os) const override;
    friend Octagon operator+(const Octagon& left, const Octagon& right);
    
    friend std::ostream& operator<<(std::ostream& os, const Octagon& obj);
    friend std::istream& operator>>(std::istream& is, Octagon& obj);
    
private:
    size_t side;
};

#endif
