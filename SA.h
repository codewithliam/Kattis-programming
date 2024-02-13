#ifndef SA_H
#define SA_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>

class SA {
public:
    float x_max;
    float x_min;
    int max_steps;
    std::vector<float>& x_vector;
    std::vector<float>& y_vector;

    SA(std::vector<float>& x_vec, std::vector<float>& y_vec, int max_steps);

    float run();

private:
    float random_neighbour(float x, float fraction);
    float clip(float x);
    float random_start();
    float cost_function(float x);
    float acceptance_probability(float cost, float new_cost, float temperature);
    float temperature(float fraction);
};

#endif