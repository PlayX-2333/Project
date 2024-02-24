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

int number_burst(){
    double rand_uniform = drand48();
    return ceil(rand_uniform*64);
}

int CPU_burst_time(){
    return ceil(next_exp());
}

int IO_burst_time(){
    return ceil(next_exp());
}

void process_progress(int is_IO_bound, int process_code){
    double arrival_time = next_arrival_time();
    int Burst_number = number_burst();

    char process_name = static_cast<char>(process_code);
    string bound = is_IO_bound ? "IO" : "CPU";
    
    // Header info
    cout << bound << "-bound process " << process_name << ": arrival time " << arrival_time <<
        "ms; " << Burst_number << " CPU bursts" << endl;

    for(int i = 0; i < Burst_number-1; i++){
        int cpu_burst_time = CPU_burst_time();
        int io_burst_time = IO_burst_time();

        io_burst_time *= 10;
        cpu_burst_time *= 4;
        io_burst_time /= 8;
        
        // Print burst info
        cout << "--> CPU burst " << cpu_burst_time << "ms --> I/O burst " << io_burst_time << "ms" << endl;
    }

    // Special for the last CPU burst
    int final_cpu_burst_time = CPU_burst_time();
    final_cpu_burst_time *= 4;
    cout << "--> CPU burst " << final_cpu_burst_time << "ms" << endl;
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
    
    int asciiValue = 65;
    for (int i = 0; i < n; i++, asciiValue++){
        cout << "Process " << i << ": " << endl;
        if(i < n-1-n_CPU){
            process_progress(1, asciiValue);
        }
        else{
            process_progress(0, asciiValue);
        }
    }
}