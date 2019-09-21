#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void stop(char *param1) {
    char jcom[100];

    sprintf(jcom, "service jail stop %s", param1);
    system(jcom);
}