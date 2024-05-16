//
// Created by shivam on 5/16/24.
//

#ifndef SMD_INTEGRATE_H
#define SMD_INTEGRATE_H

#include <vector>
#include <cmath>
#include "integrate.h"
#include "atom.h"
#include "global.h"

void apply_pbc(Vector &position);
void integrate(vector <Particle> & particle);
void updateForce(vector <Particle> & particle);
#endif //SMD_INTEGRATE_H

