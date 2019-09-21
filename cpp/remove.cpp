#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

//void remove(char *param1) {
int main() {
    char jcom[100], delline[100];
    char param1[100] = "git {";
    string line;

//    sprintf(jcom, "zfs - destroy -r zroot/jails/%s", param1);
//    system(jcom);
    ifstream jconf("~/jail.conf;");
    ofstream temp_jconf("~/jail_temp.conf");
    sprintf(delline, "%s {", param1);
    while(getline(jconf, line)) {
        if(line != delline) {
            temp_jconf << line << endl;
        }
    }
}