//
// Created by shivam on 5/9/24.
//
#include <iostream>
#include <cmath>
#include "Vector.h"
#include "atom.h"
#include "global.h"



float ZBL(Particle &p1, Particle &p2){
return 0.0;
}

float LJEnergy(Particle &p1, Particle &p2){
    /*
     * Returns potentialEnergy in Kelvin
     *
     * */


    // Lorentz Berthelot mixing rules
    double sigma = 0.5*(p1.sigma + p2.sigma);
    double epsilon = pow(p1.epsilon*p2.epsilon, 0.5);

    Vector r = p2.position - p1.position;

    // apply periodic boundary conditions
    r.x = r.x - round(r.x/boxLength)*boxLength;
    r.y = r.y - round(r.y/boxLength)*boxLength;
    r.z = r.z - round(r.z/boxLength)*boxLength;

    double r2 = r.dot(r);
    if (r2 < pow(cutoff, 2)) {
        double r2i = 1 / r2;
        double r6i = pow(r2i, 3);

        return 4.0 * epsilon * (pow(sigma, 12) * pow(r6i,2) - pow(sigma, 6) * r6i);
    }
    else return 0.0;
}

Vector LJForce(Particle &p1, Particle&p2){
    /*
     * Returns force on particle 1 due to particle 2
     *
     */
    Vector force;

    // Lorentz Berthelot mixing rules
    double sigma = 0.5*(p1.sigma + p2.sigma);
    double epsilon = pow(p1.epsilon*p2.epsilon, 0.5);

    // vector from p1 towards p2
    Vector r = p2.position - p1.position;

    // apply periodic boundary conditions
    r.x = r.x - round(r.x/boxLength)*boxLength;
    r.y = r.y - round(r.y/boxLength)*boxLength;
    r.z = r.z - round(r.z/boxLength)*boxLength;

    double r2 = r.dot(r);

    if (r2 < pow(cutoff, 2)) {
        double r2i = 1 / r2;
        double r6i = pow(r2i, 3);

        force = r * 48.0 * epsilon * (-0.5 * pow(sigma, 6) * r6i + pow(sigma, 12) * pow(r6i, 2));
    }
    else {
        force = {0.0, 0.0, 0.0};
    }

    return force;

}