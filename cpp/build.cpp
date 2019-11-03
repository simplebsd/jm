#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void build() {
    char rtext[100], jcom[100], jadd[500];
    string jname, jhostname, jipv4;

    string conf_arr[3] = {};

    ifstream rconf("./Jfile");
    if(rconf.fail()) {
        cout << "Can't find Jfile.";
    }
    else {

        for(int i = 0; i < (sizeof(conf_arr) / sizeof(conf_arr[0])); i++) {
            rconf.getline(rtext, 100);
            conf_arr[i] = rtext;
        }


        rconf.close();

        jname = conf_arr[0];
        jhostname = conf_arr[1];
        jipv4 = conf_arr[2];

        if(jname.substr(0, 7) != "jname: ") {
            cout << "Wrong parameter jname\n";
        }
        else if(jhostname.substr(0, 11) != "jhostname: ") {
            cout << "Wrong parameter jhostname\n";
        }
        else if(jipv4.substr(0, 7) != "jipv4: ") {
            cout << "Wrong parameter jipv4\n";
        }

        else {
            sprintf(jcom, "zfs clone zroot/jails/basejail@12.0-RELEASE zroot/jails/%s", jname.substr(7).c_str());
            system(jcom);

            sprintf(jadd, "%s { # jm_%s\n  host.hostname = \"%s\"; # jm_%s\n  interface = \"lo1\"; # jm_%s\n  ip4.addr = %s; # jm_%s\n} # jm_%s\n\n", jname.substr(7).c_str() , jname.substr(7).c_str(), jhostname.substr(11).c_str(), jname.substr(7).c_str(), jname.substr(7).c_str(), jipv4.substr(7).c_str(), jname.substr(7).c_str(), jname.substr(7).c_str());

            ofstream jconf("/etc/jail.conf", ios::app);
            jconf << jadd;
            jconf.close();

        }
    }
}
