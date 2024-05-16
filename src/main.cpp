#include <iostream>
#include <vector>
#include "atom.h"
#include "global.h"
#include "movies.h"
#include "integrate.h"
#include "intialize.h"

using namespace std;

double cutoff;
double boxLength;
double nParticles;
double timestep;
double temperature;
int Nsteps;


int main() {
    boxLength = 40.0;  // Angstrom
    nParticles = 10;
    temperature = 300.0;  // Kelvin
    timestep = 1;  // femtoseconds
    cutoff = 17.0;  // Angstrom
    Nsteps = 10000;

    vector <Particle> particlesList(Nmax);
    //ofstream xyzfile;
    //xyzfile.open("traj.xyz", ios_base::app);
    FILE *pdbfile;
    pdbfile = fopen("traj.pdb", "w");

    initialize(particlesList);

    // time integration
    for (int i = 0; i<Nsteps; i++) {
        cout << "Timestep " << i << endl;
        // writexyz(xyzfile, particlesList);

        updateForce(particlesList);
        integrate(particlesList);
        writepdb(pdbfile, particlesList);
    }
    return 0;
}
