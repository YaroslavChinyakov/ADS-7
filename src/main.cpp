// Copyright 2022 NNTU-CS
#include <iostream>
#include "train.h"
#include <chrono>
#include <random>
#include <vector>
int main() {
    std::vector<int> ns;
    for (int n = 100; n <= 2000; n += 100) {
        ns.push_back(n);
    }

    enum Scenario { ALL_OFF, ALL_ON, RANDOM };
    const int M = 5; 

    std::vector<int> ops_off, ops_on, ops_rand;
    std::vector<double> time_off, time_on, time_rand;

    std::mt19937_64 rng(12345);

    for (int n : ns) {
        {
            Train t;
            for (int i = 0; i < n; ++i) t.addCar(false);
            int length = t.getLength();
            ops_off.push_back(t.getOpCount());
            double total = 0;
            for (int rep = 0; rep < M; ++rep) {
                auto start = std::chrono::high_resolution_clock::now();
                (void)t.getLength();
                auto end = std::chrono::high_resolution_clock::now();
                total += std::chrono::duration<double>(end - start).count();
            }
            time_off.push_back(total / M);
        }

        {
            Train t;
            for (int i = 0; i < n; ++i) t.addCar(true);
            int length = t.getLength();
            ops_on.push_back(t.getOpCount());
            double total = 0;
            for (int rep = 0; rep < M; ++rep) {
                auto start = std::chrono::high_resolution_clock::now();
                (void)t.getLength();
                auto end = std::chrono::high_resolution_clock::now();
                total += std::chrono::duration<double>(end - start).count();
            }
            time_on.push_back(total / M);
        }

        
        {
            Train t;
            std::uniform_int_distribution<int> dist(0, 1);
            for (int i = 0; i < n; ++i) t.addCar(dist(rng));
            int length = t.getLength();
            ops_rand.push_back(t.getOpCount());
            double total = 0;
            for (int rep = 0; rep < M; ++rep) {
                auto start = std::chrono::high_resolution_clock::now();
                (void)t.getLength();
                auto end = std::chrono::high_resolution_clock::now();
                total += std::chrono::duration<double>(end - start).count();
            }
            time_rand.push_back(total / M);
        }
    }
    std::ofstream fops("result/ops_data.csv");
    fops << "n,all_off,all_on,random\n";
    for (size_t i = 0; i < ns.size(); ++i) {
        fops << ns[i] << "," << ops_off[i] << "," << ops_on[i] << "," << ops_rand[i] << "\n";
    }
    fops.close();

    std::ofstream ftime("result/time_data.csv");
    ftime << "n,all_off,all_on,random\n";
    for (size_t i = 0; i < ns.size(); ++i) {
        ftime << ns[i] << "," << time_off[i] << "," << time_on[i] << "," << time_rand[i] << "\n";
    }
    ftime.close();

    std::cout << "Experiment data written to result/ops_data.csv and result/time_data.csv\n";
    return 0;
}

