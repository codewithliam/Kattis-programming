#include "SA.h"

SA::SA(std::vector<float>& x_vec, std::vector<float>& y_vec, int max_steps)
    : x_vector{ x_vec }, y_vector{ y_vec }, max_steps{ max_steps } {
    x_max = *std::max_element(x_vec.begin(), x_vec.end());
    x_min = *std::min_element(x_vec.begin(), x_vec.end());
    srand(static_cast<unsigned>(time(0)));
}

float SA::run() {
    float x = random_start();
    float cost = cost_function(x);
    float T;
    float fraction;
    float new_x;
    float new_cost;
    for (int step = 0; step < max_steps; step++) {
        fraction = step / static_cast<float>(max_steps);
        T = temperature(fraction);
        new_x = random_neighbour(x, fraction);
        new_cost = cost_function(new_x);

        if (acceptance_probability(cost, new_cost, T) > (static_cast<float>(rand()) / static_cast<float>(RAND_MAX))) {
            x = new_x;
            cost = new_cost;
        }
    }
    return x;
}

float SA::random_neighbour(float x, float fraction) {
    float amplitude = (x_max - x_min) * fraction / 10;
    float rnd = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float delta = -amplitude / 2 + amplitude * rnd;
    return clip(x + delta);
}

float SA::clip(float x) {
    return std::max(std::min(x, x_max), x_min);
}

float SA::random_start() {
    float point = x_min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (x_max - x_min)));
    return point;
}

float SA::cost_function(float x) {
    float max_dist = 0;
    float dist;

    for (int i = 0; i < x_vector.size(); i++) {
        dist = sqrt(pow(x_vector[i] - x, 2) + pow(y_vector[i], 2));
        max_dist = (dist > max_dist) ? dist : max_dist;
    }
    return max_dist;
}

float SA::acceptance_probability(float cost, float new_cost, float temperature) {
    if (new_cost < cost) {
        return 1;
    }
    else {
        return exp(-(new_cost - cost) / temperature);
    }
}

float SA::temperature(float fraction) {
    return std::max(1/(float)max_steps, std::min(1.0f, 1.0f - fraction));
}