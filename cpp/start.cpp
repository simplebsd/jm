#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void start(char *param1) {
    char jcom[100];

    sprintf(jcom, "service jail start %s", param1);
    system(jcom);
}