#ifndef FUNCT_H
#define FUNCT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

#define MAX_ARG 32
int getOpt(int argc, char *argv[],char *ip, char *port, char *directory, bool &mode );
int fprintfTimeToLogFile(FILE *f, char* cmd);

int startEvLoop(int sport);

class Funct
{
public:
    Funct();
};

#endif // FUNCT_H
