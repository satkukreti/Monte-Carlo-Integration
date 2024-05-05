#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>

using namespace std;

inline double hx (double x){ return sin(x)/x; }

int main (int argc, char* argv[]){
    /*if(argc != 5){
        cerr << "Format Error: ./integrate a b n n_threads\n";
        return 1;
    }*/

    srand(time(0));

    double a = 0;
    double b = 1;

    double avg;

    for(int i = 0; i < 1000; i++){
        double rdm = ((double)rand() / RAND_MAX)*(b - a) + a;
        double toIntegrate = hx(rdm);
        avg += toIntegrate;
    }

    avg /= 1000;
    avg *= (b-a);
    
    cout << avg << endl;

    return 0;
}

