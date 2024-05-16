//
// Created by shivam on 5/14/24.
//

#ifndef SMD_GLOBAL_H
#define SMD_GLOBAL_H

#define random ((double)rand()/RAND_MAX)  // returns random number between 0 and 1
#define Nmax 1000
#define kb 1.380649e-23
#define Na 6.022e23

extern double cutoff;
extern double boxLength;
extern double nParticles;
extern double timestep;
extern double temperature;
extern int Nsteps;
#endif //SMD_GLOBAL_H
