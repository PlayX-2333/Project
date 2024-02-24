#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

int n, n_CPU, seed;
double lambda, upper_bound;

double next_exp(){
    //Exponential distribution pseudo-random number generation function
    double next_value;
    while(1){
        next_value = drand48();
        next_value = (-log(next_value) / lambda);
        if(next_value <= upper_bound){
            return next_value;
        }
    }
    return EXIT_FAILURE;
}

int next_arrival_time(){
    return floor(next_exp());
}

int burst_time(){
    double rand_uniform = drand48();
    return ceil(rand_uniform*64);
}

int main(int argc, char** argv)
{
    if (argc != 6){
        fprintf(stderr, "Error: Invalid number of arguments\n");
        return EXIT_FAILURE;
    }
    // argv[1]: number of process to stimulate; argv[2]: number of CPU;
    // argv[3]: the seed for psudo-random number sequense;
    // argv[4]: lamda, 1/lamda is the average arrival rate of the process;
    // argv[5]: upper_bound for the random number generation;
    try{
        n = stoi(argv[1]);
        n_CPU = stoi(argv[2]);
        seed = stoi(argv[3]);
        lambda = stod(argv[4]);
        upper_bound = stod(argv[5]);
    }
    catch(std::invalid_argument& e){
        fprintf(stderr, "Error: Invalid argument\n");
        return EXIT_FAILURE;
    }

    
    srand(seed);
    
    // for (int i = 0; i < n; i++){
    //     double next = next_exp();
    //     std::cout << next << std::endl;
    // }

    for(int i = 0; i < 100; i++){
        cout << burst_time() << endl;
    }
}