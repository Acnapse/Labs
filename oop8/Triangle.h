#ifndef TRIANGLE_H
#define    TRIANGLE_H
#include <cstdlib>
#include <iostream>

class Triangle {
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
    
    double Square();
    Triangle& operator=(const Triangle& right);
    
    virtual ~Triangle();
private:
    size_t side_a;
    size_t side_b;
    size_t side_c;
};

#endif
