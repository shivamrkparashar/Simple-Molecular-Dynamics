//
// Created by shivam on 5/9/24.
//

#ifndef SMD_ATOM_H
#define SMD_ATOM_H

#include "Vector.h"

class Particle{
public:
    Vector position;  // Angstrom
    Vector oldPosition;
    Vector velocity; // (Angstrom / femtosecond)
    Vector force;
    double potentialEnergy;
    string element;
    double sigma = 3.4; // Angstrom
    double epsilon = 119.4; // Kelvin
    double mass = 39.948; // g/mol

    [[nodiscard]] double kineticEnergy() const;
};
#endif //SMD_ATOM_H
