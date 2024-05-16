//
// Created by shivam on 5/16/24.
//

#include <vector>
#include <cmath>
#include "intialize.h"
#include "global.h"
#include "atom.h"


void initialize(vector <Particle> & particle){
    /*
     *  Assigns random initial positions and velocity to all particles to maintain the given temperature
     * */

    double sumKineticEnergy = 0.0;
    double avgKineticEnergy;
    double velocityScaleFactor;

    int N1d = pow(nParticles, 1.0/3.0) + 1;
    double spacing = boxLength/N1d;
    int count = 0;
    double x, y, z;

    x = 0.0;
    for (int i =0; i<N1d; i++){
        y = 0.0;
        for (int j = 0; j< N1d; j++){
            z = 0.0;
            for (int k =0; k < N1d; k++){
                if (count < nParticles){
                    particle[count].position = {x, y, z};
                    count ++;
                }
                z += spacing;
            }
            y += spacing;
        }
        x += spacing;
    }


    // assign initial positions randomly within the box
    for (int i=0; i<nParticles; i++){
        // these lines are valid only for implicit constructor
        // particle[i].position = boxLength*random, boxLength*random, boxLength*random;
        particle[i].velocity = {random-0.5, random-0.5, random-0.5};

        sumKineticEnergy += particle[i].kineticEnergy();
    }

    avgKineticEnergy = sumKineticEnergy/nParticles;
    velocityScaleFactor = pow(3*temperature/avgKineticEnergy,0.5);

    // scale the velocities at the given temperature
    for (int i=0; i<nParticles; i++){
        particle[i].velocity = particle[i].velocity * velocityScaleFactor;

        // calculate the old position
        particle[i].oldPosition = particle[i].position - particle[i].velocity*timestep;
    }
}
