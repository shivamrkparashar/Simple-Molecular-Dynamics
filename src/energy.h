//
// Created by shivam on 5/14/24.
//

#ifndef SMD_ENERGY_H
#define SMD_ENERGY_H

#include "Vector.h"
#include "atom.h"
float LJEnergy(Particle &p1, Particle &p2);
Vector LJForce(Particle &p1, Particle&p2);

#endif //SMD_ENERGY_H
