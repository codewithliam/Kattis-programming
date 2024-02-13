#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include "SA.h"

using namespace std; 

void grid_calc(float x, vector<float>& x_vec, vector<float>& y_vec) {
    float step = 1e-5; 
    float x_max = x + 0.01; 
    float x_min = x - 0.01; 
    
    float x_min_index = 0; 
    float max_dist = 0;
    float total_min_dist = 1e10;
    float dist; 

    for (float x = x_min; x <= x_max; x = x + step)
    {
        max_dist = 0; 
        for (int i = 0; i < x_vec.size(); i++)
        {
            dist = sqrt(pow(x_vec[i] - x, 2) + pow(y_vec[i], 2)); 

            max_dist = (dist > max_dist) ? dist : max_dist; 
        }

        if (total_min_dist > max_dist) {
            total_min_dist= max_dist; 
            x_min_index = x; 
        }
    }

    cout << to_string(x_min_index) << " " << to_string(total_min_dist) << '\n';
}

float SA_calc(vector<float>& x_vec, vector<float>& y_vec) {

    int nbr_of_steps = 1e3; 
    SA sa = SA(x_vec, y_vec, nbr_of_steps); 
    float x = sa.run();

    return x; 


}

int main()
{
    int N;
    float x; 
    float y;
    string blank; 
    while (cin) {
        scanf_s("%d", &N);
        if (N == 0) {
            break; 
        }

        vector<float> x_vec(N); 
        vector<float> y_vec(N); 

        for (int i = 0; i < N; i++) {
            scanf_s("%f %f", &x, &y); 
            x_vec[i] = x;  
            y_vec[i] = y;
        }
        x = SA_calc(x_vec, y_vec); 
        grid_calc(x, x_vec, y_vec);
        getline(cin, blank);
    }


}



