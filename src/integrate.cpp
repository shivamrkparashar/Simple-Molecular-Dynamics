//
// Created by shivam on 5/16/24.
//
#include <vector>
#include <cmath>
#include "integrate.h"
#include "atom.h"
#include "global.h"
#include "energy.h"


void apply_pbc(Vector &position){
    /*
     * Applies periodic boundary condition to position vector
     */

    if (position.x < 0) position.x += boxLength;
    if (position.y < 0) position.y += boxLength;
    if (position.z < 0) position.z += boxLength;
    if (position.x > boxLength) position.x -= boxLength;
    if (position.y > boxLength) position.y -= boxLength;
    if (position.z > boxLength) position.z -= boxLength;
}

void updateForce(vector <Particle> & particle){
    /*
     * updates forces and potentialEnergy for each particle
     *
     */
    // initalize forces to zero at each time step
    for (int i = 0; i<nParticles; i++) {
        particle[i].force = {0.0, 0.0, 0.0};
        particle[i].potentialEnergy = 0.0;
    }


    for (int i = 0; i<nParticles; i++){
        for (int j = i+1; j<nParticles; j++){
            Vector fij =  LJForce(particle[i], particle[j]);
            particle[i].force = particle[i].force + fij;
            particle[j].force = particle[j].force - fij;

            double eij = LJEnergy(particle[i], particle[j]);
            particle[i].potentialEnergy += eij;
            particle[j].potentialEnergy += eij;

        }
    }
}


void integrate(vector <Particle> & particle){

    Vector newPosition;
    Vector newVelocity;
    double fullEnergy = 0.0;
    for (int i = 0; i < nParticles; i++){
        // velocity Verlet
        // conversion from Kelvin/Angstrom (fs)^2 /(mol/g) to Angstrom
        newPosition = particle[i].position * 2.0 - particle[i].oldPosition +
                      particle[i].force/particle[i].mass * pow(timestep,2) * 1e-7 *kb*Na ;

        // new velocity
        newVelocity = (newPosition - particle[i].oldPosition)/(2*timestep);

        // apply periodic boundary conditions
        if (newPosition.x < 0) newPosition.x += boxLength;
        if (newPosition.y < 0) newPosition.y += boxLength;
        if (newPosition.z < 0) newPosition.z += boxLength;
        if (newPosition.x > boxLength) newPosition.x -= boxLength;
        if (newPosition.y > boxLength) newPosition.y -= boxLength;
        if (newPosition.z > boxLength) newPosition.z -= boxLength;

        // update the old positions
        particle[i].oldPosition = particle[i].position;

        // update the current positions
        particle[i].position = newPosition;

        // update the current velocity
        particle[i].velocity = newVelocity;

        fullEnergy += 0.5*particle[i].potentialEnergy + particle[i].kineticEnergy();

    }
    cout << "Energy [K] = " << fullEnergy << endl;
}
