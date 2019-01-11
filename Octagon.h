#ifndef OCTAGON_H
#define	OCTAGON_H
#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Octagon : public Figure {
public:
	Octagon();
	Octagon(size_t i);
	Octagon(const Octagon& orig);
    Octagon(std::istream &is);

	Octagon& operator++();
    Octagon& operator=(const Octagon& right);
	double Square() override;
	void Print(std::ostream& os) const override;
	friend Octagon operator+(const Octagon& left, const Octagon& right);
	size_t GetSide() override;

	friend std::ostream& operator<<(std::ostream& os, const Octagon& obj);
	friend std::istream& operator>>(std::istream& is, Octagon& obj);

private:
	size_t side;
};

#endif	
