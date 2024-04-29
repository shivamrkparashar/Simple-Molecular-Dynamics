#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#define random (double)rand()/RAND_MAX
#define Nmax 1000

using namespace std;

class Particle{
public:
    double x;
    double y;
    double z;
    double xo;
    double yo;
    double zo;
    double vx;
    double vy;
    double vz;
    double fx;
    double fy;
    double fz;
    double energy;

    double kineticEnergy(){
        return 0.5*(vx*vx + vy*vy + vz*vz);
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
        particle[i].x = boxLength * random;
        particle[i].y = boxLength * random;
        particle[i].z = boxLength * random;

        particle[i].vx = random - 0.5;
        particle[i].vy = random - 0.5;
        particle[i].vz = random - 0.5;

        sumKineticEnergy += particle[i].kineticEnergy();
    }

    avgKineticEnergy = sumKineticEnergy/nParticles;
    velocityScaleFactor = pow(3*temperature/avgKineticEnergy,0.5);

    // scale the velocities at the given temperature
    for (int i=0; i<nParticles; i++){
        particle[i].vx *= velocityScaleFactor;
        particle[i].vy *= velocityScaleFactor;
        particle[i].vz *= velocityScaleFactor;

        // calculate the old position
        particle[i].xo = particle[i].x - particle[i].vx * dt;
        particle[i].yo = particle[i].y - particle[i].vy * dt;
        particle[i].zo = particle[i].z - particle[i].vz * dt;
    }
}


void integrate(vector <Particle> & particle, int nParticles, double boxLength){

    double xnew;
    double ynew;
    double znew;
    for (int i = 0; i < nParticles; i++){
        xnew = 2*particle[i].x - particle[i].xo;
        ynew = 2*particle[i].y - particle[i].yo;
        znew = 2*particle[i].z - particle[i].zo;

        // apply periodic boundary conditions
        if (xnew < 0) xnew += boxLength;
        if (ynew < 0) ynew += boxLength;
        if (znew < 0) znew += boxLength;
        if (xnew > boxLength) xnew -= boxLength;
        if (ynew > boxLength) ynew -= boxLength;
        if (znew > boxLength) znew -= boxLength;

        // update the old positions
        particle[i].xo = particle[i].x;
        particle[i].yo = particle[i].y;
        particle[i].zo = particle[i].z;

        // update the current positions
        particle[i].x = xnew;
        particle[i].y = ynew;
        particle[i].z = znew;
    }
}


void writexyz(ofstream &xyzfile,vector <Particle> & particle, int nParticles){

    xyzfile << nParticles << endl;
    xyzfile << "----" << endl;

    for (int i = 0; i<nParticles; i++){
        xyzfile << "Ar  " << particle[i].x << "\t" << particle[i].y << "\t" << particle[i].z << endl;
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
