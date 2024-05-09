//
// Created by shivam on 5/9/24.
//
#ifndef SMD_VECTOR_H
#define SMD_VECTOR_H

#include <iostream>
using namespace std;

class Vector{
public:
    double x;
    double y;
    double z;

    // explicit keywords does not allow type conversion of a, b, c
    Vector(double a=0.0, double b=0.0, double c=0.0);

    Vector operator+ (const Vector &) const;
    Vector operator- (const Vector &) const;
    // Vector operator* (Vector &);
    Vector operator* (const double &) const;

    // [[nodiscard]]: store the return value of this function into some variable, or print
    [[nodiscard]] double dot(const Vector &) const;

    friend ostream & operator<< (ostream & os, Vector & vector);
};
#endif //SMD_VECTOR_H
