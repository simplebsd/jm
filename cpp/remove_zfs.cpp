#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

void remove(char *param1) {
    string line, delline;
    size_t pos;
    char jcom[100];

    delline = param1;

    ifstream jconfr("/etc/jail.conf");
    ofstream jconfw("/etc/jail_temp.conf");

    while(getline(jconfr, line)) {
        pos = line.find("# jm_" + delline);

        if(pos == string::npos) {
            jconfw << line << endl;
        }
    }

    jconfr.close();
    jconfw.close();
    remove("/etc/jail.conf");
    rename("/etc/jail_temp.conf", "/etc/jail.conf");

    sprintf(jcom, "zfs destroy -r zroot/jails/%s", param1);
    system(jcom);
}
