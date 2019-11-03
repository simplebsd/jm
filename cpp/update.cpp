#include <iostream>
#include <stdlib.h>
using namespace std;

void update() {
    system("rm -rf /tmp/jm");
    system("/usr/local/bin/git clone https://github.com/simplebsd/jm /tmp/jm");
    system("clang++ /tmp/jm/cpp/jm.cpp -o /usr/local/bin/jm");
    system("rm -rf /tmp/jm");
}
