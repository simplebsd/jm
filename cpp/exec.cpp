#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void exec(char *param1) {
    char jcom[100];

    sprintf(jcom, "jexec %s", param1);
    system(jcom);
}