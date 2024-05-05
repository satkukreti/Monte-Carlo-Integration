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

    double a = stod(argv[1]);
    double b = stod(argv[2]);

    if(a == b){ cerr << "Error: a cannot equal b\n"; return 1;}
    
    int n = stoi(argv[3]);

    //Kahan summation to mitigate overflow
    double sum = 0.0;
    double compensation = 0.0;

    for(int i = 0; i < n; i++){
        double rdm = ((double)rand() / RAND_MAX) * (b - a) + a;
        double y = hx(rdm) - compensation;
        double t = sum + y;
        compensation = (t - sum) - y;
        sum = t;
    }

    double avg = sum / n * (b - a);
    
    cout << avg << endl;

    return 0;
}

