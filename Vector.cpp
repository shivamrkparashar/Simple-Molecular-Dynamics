//
// Created by shivam on 5/9/24.
//
#include "Vector.h"
#include <iostream>
using namespace std;

// default argument constructor
Vector::Vector(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
}

// overloading output stream operator
ostream& operator<<(ostream & os, Vector & v){
    os << v.x << " " << v.y << " " << v.z << endl;
    return os;
}

// overloading add operator
Vector Vector::operator+(const Vector &v1) const {
    Vector result;
    result.x = x + v1.x;
    result.y = y + v1.y;
    result.z = z + v1.z;
    return result;
}

// overloading subtract operator
Vector Vector::operator-(const Vector &v1) const {
    Vector result;
    result.x = x - v1.x;
    result.y = y - v1.y;
    result.z = z - v1.z;
    return result;
}
/*
// overloading element wise multiplication
Vector Vector::operator*(Vector &v1) {
    Vector result;
    result.x = x * v1.x;
    result.y = y * v1.y;
    result.z = z * v1.z;
    return result;
}
 */

// overloading multiplying by a scalar
Vector Vector::operator*(const double &d) const {
    Vector result;
    result.x = x * d;
    result.y = y * d;
    result.z = z * d;
    return result;
}

// dot product of two vectors
double Vector::dot(const Vector &v1) const{
    return v1.x*x + v1.y*y + v1.z*z;
}
