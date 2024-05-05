#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <vector>

using namespace std;

double a, b;

inline double hx(double x){ return sin(x)/x; }

inline double MonteCarlo(int n){
    //Kahan summation to mitigate overflow
    srand(time(0));
    double sum = 0.0;
    //double compensation = 0.0;

    for(int i = 0; i < n; i++){
        double rdm = ((double)rand() / RAND_MAX) * (b - a) + a;
        //double y = hx(rdm) - compensation;
        //double t = sum + y;
        //compensation = (t - sum) - y;
        //sum = t;
        sum += hx(rdm);
    }

    double avg = sum / n * (b - a);
    return avg;
} 

int main (int argc, char* argv[]){
    if(argc != 5){
        cerr << "Format Error: ./integrate a b n n_threads\n";
        return 1;
    }

    //srand(time(0));

    a = stod(argv[1]);
    b = stod(argv[2]);

    if(a == b){ cerr << "Error: a cannot equal b\n"; return 1;}
    
    int n = stoi(argv[3]);
    int n_thread = stoi(argv[4]);
    int n_per_t = n/n_thread;
    int r = n % n_thread;

    vector<thread> tcontainer(n_thread);
    vector<double> results(n_thread);

    for(int i = 0; i < n_thread; i++){
        tcontainer[i] = thread([&results, i, n_per_t, r]() {
            results[i] = MonteCarlo(i < r ? n_per_t + 1 : n_per_t);
        });
    }

    for(int i = 0; i < n_thread; i++){
        tcontainer[i].join();
    }

    long double sum = 0.0;
    for(int i = 0; i < n_thread; i++){
        sum += results[i];
    }

    cout << sum/n_thread << endl;
    
    return 0;
}

