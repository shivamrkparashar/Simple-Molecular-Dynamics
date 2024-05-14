#include <iostream>
#include <vector>
#include <cmath>
#include "energy.h"
#include "Vector.h"
#include "atom.h"
#include "global.h"
#include "movies.h"

using namespace std;

double cutoff;
double boxLength;
double nParticles;
double timestep;
double temperature;

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




int main() {
    boxLength = 40.0;  // Angstrom
    nParticles = 10;
    temperature = 300.0;  // Kelvin
    timestep = 1;  // femtoseconds
    cutoff = 17.0;
    int Nsteps = 10000;

    vector <Particle> particlesList(Nmax);
    ofstream xyzfile;
    xyzfile.open("traj.xyz", ios_base::app);
    FILE *pdbfile;
    pdbfile = fopen("traj.pdb", "w");

    initialize(particlesList);

    // time integration
    for (int i = 0; i<Nsteps; i++) {
        cout << "Timestep " << i << endl;
        // writexyz(xyzfile, particlesList);
        writepdb(pdbfile, particlesList);
        updateForce(particlesList);
        integrate(particlesList);
    }
    return 0;
}
