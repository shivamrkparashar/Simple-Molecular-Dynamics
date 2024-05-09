#include <iostream>
#include <vector>
#include <cmath>
#include "Vector.h"
#include <fstream>

#define random ((double)rand()/RAND_MAX)  // returns random number between 0 and 1
#define Nmax 1000

using namespace std;

class Particle{
public:
    Vector position;
    Vector oldPosition;
    Vector velocity;
    Vector force;
    double energy;

    double kineticEnergy(){
        return 0.5*velocity.dot( velocity);
    }
};


void initialize(vector <Particle> & particle, int nParticles, double temperature, double boxLength, double dt){
    /*
     *  Assigns random initial positions and velocity to all particles to maintain the given temperature
     * */

    double sumKineticEnergy = 0.0;
    double avgKineticEnergy;
    double velocityScaleFactor;

    // assign initial positions randomly within the box
    for (int i=0; i<nParticles; i++){
        // these lines are valid only for implicit constructor
        particle[i].position = boxLength*random, boxLength*random, boxLength*random;
        particle[i].velocity = random-0.5, random-0.5, random-0.5;

        sumKineticEnergy += particle[i].kineticEnergy();
    }

    avgKineticEnergy = sumKineticEnergy/nParticles;
    velocityScaleFactor = pow(3*temperature/avgKineticEnergy,0.5);

    // scale the velocities at the given temperature
    for (int i=0; i<nParticles; i++){
        particle[i].velocity = particle[i].velocity * velocityScaleFactor;

        // calculate the old position
        particle[i].oldPosition = particle[i].position - particle[i].velocity*dt;
    }
}


void integrate(vector <Particle> & particle, int nParticles, double boxLength){

    Vector newPosition;
    for (int i = 0; i < nParticles; i++){
        newPosition = particle[i].position * 2.0 - particle[i].oldPosition;

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
    }
}


void writexyz(ofstream &xyzfile,vector <Particle> & particle, int nParticles){

    xyzfile << nParticles << endl;
    xyzfile << "----" << endl;

    for (int i = 0; i<nParticles; i++){
        // xyzfile << "Ar  " << particle[i].x << "\t" << particle[i].y << "\t" << particle[i].z << endl;
        xyzfile << "Ar  " << particle[i].position;
    }

}


int main() {
    double boxLength = 20.0;  // Angstrom
    int nParticles = 5;
    double temperature = 300;  // Kelvin
    double timestep = 0.01;  // seconds

    vector <Particle> particlesList(Nmax);
    ofstream xyzfile;
    xyzfile.open("traj.xyz", ios_base::app);

    initialize(particlesList, nParticles, temperature, boxLength, timestep);

    // time integration
    for (int i = 0; i<1000; i++) {
        integrate(particlesList, nParticles, boxLength);
        writexyz(xyzfile, particlesList, nParticles);
    }
    return 0;
}
