#pragma once // Header guard to prevent multiple inclusions

#include <cstring>
#include <iostream>
#include <string>
#include <vector>


void name_to_array(std::string name, double* genes);

struct coat
{
    string name;
    double prob;
};

class Cat {
public:
    double probabilities[7];

    Cat(std::string maleColor, std::string femaleColor, bool male);

    void RedCalc(double* probs, double m1, double m2, double f1, double f2, bool male);

    void ColorCalc(double* probs, double m1, double m2, double f1, double f2);

    void ProbCalc(double* probs, double arr1[], double arr2[], bool male);
};

void printNoRedProbs(double* male_probs, double* female_probs);

void printRedProbs(double* male_probs, double* female_probs);
