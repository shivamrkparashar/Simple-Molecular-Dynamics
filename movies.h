//
// Created by shivam on 5/14/24.
//

#ifndef SMD_MOVIES_H
#define SMD_MOVIES_H
#include <iostream>
#include <vector>
#include <fstream>
#include "atom.h"
#include "Vector.h"
#include "global.h"
void writexyz(ofstream &xyzfile,vector <Particle> & particle);
void writepdb(FILE *FilePtr, vector <Particle> & particle);

#endif //SMD_MOVIES_H
