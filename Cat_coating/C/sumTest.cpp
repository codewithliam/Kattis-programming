#include <cstring>
#include <iostream>
using namespace std;
#include "cat_classes.h"
#include<windows.h>
#include <stdio.h>



double calcNoRedProbs(double* male_probs, double* female_probs) {
	double recessive_red_prob = (male_probs[2] + female_probs[2])/2;
	double black_prob = recessive_red_prob*(female_probs[3]*female_probs[5] + male_probs[3]*male_probs[5])/2;

	double blue_prob =recessive_red_prob*(female_probs[3]*female_probs[6] + male_probs[3]*male_probs[6])/2;


	double choco_prob =recessive_red_prob*(female_probs[4]*female_probs[5] + male_probs[4]*male_probs[5])/2;


	double lilac_prob =recessive_red_prob*(female_probs[4]*female_probs[6] + male_probs[4]*male_probs[6])/2;

	double sum = black_prob + blue_prob + choco_prob + lilac_prob;

	return sum;


}

double calcRedProbs(double* male_probs, double* female_probs) {

	double red_prob = (female_probs[0]*female_probs[5] + male_probs[0]*male_probs[5])/2;

	double cream_prob = (female_probs[0]*female_probs[6] + male_probs[0]*male_probs[6])/2;


	double black_tortie_prob = 0.5*(female_probs[1]*female_probs[5]*female_probs[3]);

	double blue_tortie_prob = 0.5*(female_probs[1]*female_probs[6]*female_probs[3]);

	double choco_tortie_prob = 0.5*(female_probs[1]*female_probs[5]*female_probs[4]);

	double lilac_tortie_prob = 0.5*(female_probs[1]*female_probs[4]*female_probs[6]);

	double sum = red_prob + cream_prob + black_tortie_prob + blue_tortie_prob + choco_tortie_prob + lilac_tortie_prob;

	return sum;

	}


void sumTest() {
	string male;
	string female;

	const char* femaleColors[10] = {"Black", "Blue", "Chocolate",
	"Lilac", "Red", "Cream", "Black-Red Tortie", "Blue-Cream Tortie",
	"Chocolate-Red Tortie", "Lilac-Cream Tortie"};

	const char* maleColors[6] = {"Black", "Blue", "Chocolate",
	"Lilac", "Red", "Cream"};

	for(int i=0; i<10; i++)
	{
	for(int j=0; j<6; j++) {
		Sleep(0.01);

		string female = femaleColors[i];
		string male = maleColors[j];
		Cat male_cat = Cat(male, female, true);
		Cat female_cat = Cat(male, female, false);

		double *male_probs = male_cat.probabilities;
		double *female_probs = female_cat.probabilities;

		double sum = 0;

		sum += calcNoRedProbs(male_probs, female_probs);
		sum += calcRedProbs(male_probs, female_probs);

		if(sum == 1) {
			cout << "Success! " << female << " " << male <<" Sum: " << sum << '\n';
		}
		else {cout << "Fail! " << female << " " << male <<" Sum: " << sum << '\n';}

		}

	}
	}

