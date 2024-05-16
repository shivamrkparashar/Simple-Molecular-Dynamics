//
// Created by shivam on 5/9/24.
//
#include "Vector.h"
#include "atom.h"
#include "global.h"


double Particle::kineticEnergy() const{
    // conversion from g/mol * (Angstrom/fs)^2  to Kelvin
    return 0.5*mass*velocity.dot( velocity)*1e7/Na/kb;  // Kelvin
}
