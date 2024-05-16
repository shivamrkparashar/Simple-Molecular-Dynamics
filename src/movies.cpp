//
// Created by shivam on 5/14/24.
//
#include <iostream>
#include <vector>
#include <fstream>
#include "atom.h"
#include "Vector.h"
#include "global.h"
using namespace std;


void writexyz(ofstream &xyzfile,vector <Particle> & particle){

    xyzfile << nParticles << endl;
    xyzfile << "----" << endl;

    for (int i = 0; i<nParticles; i++){
        // xyzfile << "Ar  " << particle[i].x << "\t" << particle[i].y << "\t" << particle[i].z << endl;
        xyzfile << "Ar  " << particle[i].position;
    }

}

void writepdb(FILE *FilePtr, vector <Particle> & particle)
{
    int i;
    static int Countmodel=0,Countatom=0;

    double angle = 90.00;
    Countmodel++;
    fprintf(FilePtr,"%s %9d\n","MODEL",Countmodel);
    fprintf(FilePtr,"%s%9.3lf%9.3lf%9.3lf%7.2lf%7.2lf%7.2lf\n","CRYST1",
            boxLength, boxLength, boxLength, angle, angle, angle);

    for(i=0;i<nParticles;i++)
    {
        Countatom++;
        fprintf(FilePtr,"%s%7d%s%12d    %8.3lf%8.3lf%8.3lf\n",
                "ATOM",Countatom,"  C",Countatom, particle[i].position.x,particle[i].position.y,particle[i].position.z);
    }
    fprintf(FilePtr,"%s\n","ENDMDL");
}
