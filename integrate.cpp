#include <iostream>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <vector>
#include <thread>
#include <cmath>
#include <limits>

using namespace std;

double a, b;

//function to integrate
inline double hx(double x){ return sin(x)/x; }

inline double MonteCarlo(int n){
    //sets random seed using system time, pid, and mem address
    unsigned seed = chrono::system_clock::now().time_since_epoch().count() + getpid() + reinterpret_cast<uintptr_t>(&n);
    srand(seed);
    double sum = 0.0;

    for(int i = 0; i < n; i++){
        double rdm = ((double)rand() / RAND_MAX) * (b - a) + a;
        while(rdm == 0)
            rdm = ((double)rand() / RAND_MAX) * (b - a) + a;
        sum += hx(rdm);
    }

    double avg = sum / n * (b - a);
    return avg;
} 

int main (int argc, char* argv[]){
    //params
    if(argc != 5){
        cerr << "Format Error: ./integrate a b n n_threads\n";
        return 1;
    }

    //input
    a = stod(argv[1]);
    b = stod(argv[2]);

    if(a == b){ cerr << "Error: a cannot equal b\n"; return 1;}
    
    int n = stoi(argv[3]);
    int n_thread = stoi(argv[4]);
    
    //divide the load evenly among threads
    int n_per_t = n/n_thread;
    int r = n % n_thread;

    vector<thread> tcontainer(n_thread);
    //store threaded results
    vector<double> results(n_thread);

    for(int i = 0; i < n_thread; i++){
        tcontainer[i] = thread([&results, i, n_per_t, r]() {
            results[i] = MonteCarlo(i < r ? n_per_t + 1 : n_per_t);
        });
    }

    for(int i = 0; i < n_thread; i++){
        tcontainer[i].join();
    }

    //calculate sum
    double sum = 0.0;
    for(int i = 0; i < n_thread; i++){
        sum += results[i];
    }

    cout << setprecision(numeric_limits<double>::max_digits10) << sum/n_thread << "\n";
    
    return 0;
}

