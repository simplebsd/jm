#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include "build_zfs.cpp"
#include "list.cpp"
#include "start.cpp"
#include "stop.cpp"
#include "exec.cpp"
#include "remove_zfs.cpp"
#include "update.cpp"
using namespace std;

char *param1, *param2;

int main(int argc, char *argv[]) {

	param1 = argv[2];
	param2 = argv[3];

	if(argc < 2)  {
		cout << "\e[1mNAME\e[0m\n";
		cout << "\tJm - Jail manager\n\n";
		cout << "\e[1mDESCRIPTION\e[0m\n";
		cout << "\tJm is a simple Jail manager. It helps to build and manage jails on FreeBSD with ZFS file system.\n\n";
		cout << "\e[1mOPTIONS\e[0m\n";
		cout << "\tbuild \033[4m.\033[24m\t Build new jail.\n\n";
		cout << "\tps\t List all jails.\n\n";
		cout << "\tstart \033[4mjail name\033[24m\t Start jail.\n\n";
		cout << "\tstop \033[4mjail name\033[24m\t Stop a jail.\n\n";
		cout << "\trestart \033[4mjail name\033[24m\t Restart jail.\n\n";
		cout << "\texec \033[4mjail name\033[24m\t Shell access to the jail.\n\n";
		cout << "\trm \033[4mjail name\033[24m\t Remove jail.\n\n";
		cout << "\tupdate\t Update jm programm.\n\n";

	}

	else {
		if(!strcmp(argv[1], "build") && !strcmp(argv[2], ".")) build();
		else if(!strcmp(argv[1], "ps")) list();
		else if(!strcmp(argv[1], "start") && !strcmp(argv[2], param1)) start(param1);
		else if(!strcmp(argv[1], "stop") && !strcmp(argv[2], param1)) stop(param1);
		else if(!strcmp(argv[1], "restart") && !strcmp(argv[2], param1)) {
			stop(param1);
			start(param1);
		}
		else if(!strcmp(argv[1], "exec") && !strcmp(argv[2], param1)) exec(param1);
    	        else if(!strcmp(argv[1], "rm") && !strcmp(argv[2], param1)) remove(param1);
		else if(!strcmp(argv[1], "update")) update();

		else {
			cout << "\n";
			cout << "Not enough parameters.\n";
			cout << "Run jm without parameters to see the manual.\n\n";
		}

	}

	return 0;
}
