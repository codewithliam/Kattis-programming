#include <cstring>
#include <iostream>
using namespace std;
#include "cat_classes.h"
#include <vector>
#include <algorithm>


void name_to_array(string name, double* genes) {
	double *temp = new double[6] {1,1, 1, 1, 1, 1};

	if (name == "Black") {
		double temparray[] = {0,0, 1, 0.5, 1, 0.5};
		memcpy(temp, temparray, sizeof(temparray));
	}
	if (name == "Blue") {
		double temparray[] = {0,0, 1, 0.5, 0, 0};
		memcpy(temp, temparray, sizeof(temparray));
	}
	if (name == "Chocolate") {
		double temparray[] = {0,0, 0, 0, 1, 0.5};
		memcpy(temp, temparray, sizeof(temparray));
	}
	if (name == "Lilac") {
		double temparray[] = {0,0, 0, 0, 0, 0};
		memcpy(temp, temparray, sizeof(temparray));
	}
	if (name == "Red") {
		double temparray[] = {1,1, 0.5, 0.5, 1, 0.5};
		memcpy(temp, temparray, sizeof(temparray));
	}
	if (name == "Cream") {
		double temparray[] = {1,1, 0.5, 0.5, 0, 0};
		memcpy(temp, temparray, sizeof(temparray));
	}
	if (name == "Black-Red Tortie") {
		double temparray[] = {1,0, 1, 0.5, 1, 0.5};
		memcpy(temp, temparray, sizeof(temparray));
	}
	if (name == "Blue-Cream Tortie") {
		double temparray[] = {1,0, 1, 0.5, 0, 0};
		memcpy(temp, temparray, sizeof(temparray));
	}
	if (name == "Chocolate-Red Tortie") {
		double temparray[] = {1,0, 0, 0, 1, 0.5};
		memcpy(temp, temparray, sizeof(temparray));
	}
	if (name == "Lilac-Cream Tortie") {
		double temparray[] = {1,0, 0, 0, 0, 0};
		memcpy(temp, temparray, sizeof(temparray));
	}

	for(int i=0; i<6; i++)
	{
		genes[i]=temp[i];
	}

}

Cat::Cat(string maleColor, string femaleColor, bool male)
	{
		double father_genes[6];
		double mother_genes[6];
		name_to_array(maleColor, father_genes);
		name_to_array(femaleColor, mother_genes);
		ProbCalc(probabilities, father_genes, mother_genes, male);
	}

void Cat::RedCalc(double* probs, double m1, double m2, double f1, double f2, bool male) {
	double Pf = (f1 + f2)/2;
	double Pm = (m1 + m2)/2;

	if(male==false) {
		probs[0] = Pf*Pm;
		probs[2] = (1-Pf)*(1-Pm);
		probs[1] = 1 - (probs[0] + probs[2]);
}
	else {
		probs[0] = Pf;
		probs[1] = 0;
		probs[2] = 1-Pf;
	}

}

void Cat::ColorCalc(double* probs, double m1, double m2, double f1, double f2) {
	double Pf = (f1 + f2)/2;
	double Pm = (m1 + m2)/2;

	probs[1] = (1-Pf)*(1-Pm);
	probs[0] = 1-probs[1];
}

void Cat::ProbCalc(double* probs, double arr1 [], double arr2 [], bool male)  {
	double red_probs[3];
	double black_probs[2];
	double diluted_probs[2];
	RedCalc(red_probs, arr1[0], arr1[1], arr2[0], arr2[1], male);
	ColorCalc(black_probs, arr1[2], arr1[3], arr2[2], arr2[3]);
	ColorCalc(diluted_probs, arr1[4], arr1[5], arr2[4], arr2[5]);
	probs[0] = red_probs[0];
	probs[1] = red_probs[1];
	probs[2] = red_probs[2];
	probs[3] = black_probs[0];
	probs[4] = black_probs[1];
	probs[5] = diluted_probs[0];
	probs[6] = diluted_probs[1];
}

	void calcNoRedProbs(vector<coat>& coats, double* male_probs, double* female_probs) {
		double recessive_red_prob = (male_probs[2] + female_probs[2])/2;
		double black_prob = recessive_red_prob*(female_probs[3]*female_probs[5] + male_probs[3]*male_probs[5])/2;
		if (black_prob > 0) {
		    coat black;
		    black.name = "Black";
			black.prob = black_prob;
			coats.push_back(black);}
		double blue_prob =recessive_red_prob*(female_probs[3]*female_probs[6] + male_probs[3]*male_probs[6])/2;
		if (blue_prob > 0) {
		    coat blue;
		    blue.name = "Blue";
		    blue.prob = blue_prob;
			coats.push_back(blue);}

		double choco_prob =recessive_red_prob*(female_probs[4]*female_probs[5] + male_probs[4]*male_probs[5])/2;
			if (choco_prob > 0) {
			    coat choco;
			    choco.name = "Chocolate";
			    choco.prob = choco_prob;
				coats.push_back(choco);}

		double lilac_prob =recessive_red_prob*(female_probs[4]*female_probs[6] + male_probs[4]*male_probs[6])/2;
			if (lilac_prob > 0) {
			    coat lilac;
			    lilac.name = "Lilac";
			    lilac.prob = lilac_prob;
				coats.push_back(lilac);}
	}

	void calcRedProbs(vector<coat>& coats, double* male_probs, double* female_probs) {

		double red_prob = (female_probs[0]*female_probs[5] + male_probs[0]*male_probs[5])/2;
		if (red_prob > 0) {
		    coat red;
		    red.name = "Red";
		    red.prob = red_prob;
			coats.push_back(red);}
		double cream_prob = (female_probs[0]*female_probs[6] + male_probs[0]*male_probs[6])/2;
		if (cream_prob > 0) {
		    coat cream;
		    cream.name = "Cream";
		    cream.prob = cream_prob;
			coats.push_back(cream);}

		double black_tortie_prob = 0.5*(female_probs[1]*female_probs[5]*female_probs[3]);
		if(black_tortie_prob > 0) {
		    coat black_tortie;
		    black_tortie.name = "Black-Red Tortie";
		    black_tortie.prob = black_tortie_prob;
			coats.push_back(black_tortie);}

		double blue_tortie_prob = 0.5*(female_probs[1]*female_probs[6]*female_probs[3]);
		if(blue_tortie_prob > 0) {
		    coat blue_tortie;
		    blue_tortie.name = "Blue-Cream Tortie";
		    blue_tortie.prob = blue_tortie_prob;
			coats.push_back(blue_tortie);}

		double choco_tortie_prob = 0.5*(female_probs[1]*female_probs[5]*female_probs[4]);
		if(choco_tortie_prob > 0) {
		    coat choco_tortie;
		    choco_tortie.name = "Chocolate-Red Tortie";
		    choco_tortie.prob = choco_tortie_prob;
			coats.push_back(choco_tortie);}

		double lilac_tortie_prob = 0.5*(female_probs[1]*female_probs[4]*female_probs[6]);

		if(lilac_tortie_prob > 0) {
		    coat lilac_tortie;
		    lilac_tortie.name = "Lilac-Cream Tortie";
		    lilac_tortie.prob = lilac_tortie_prob;
			coats.push_back(lilac_tortie);}
		}

	void sort_coats(vector<coat>& coats)
	{
		 sort(coats.begin(), coats.end(), [](const coat& a, const coat& b) {
			return
				a.prob > b.prob
				||
				(a.prob == b.prob &&
				 a.name < b.name);}
		 );

	}

	void print_coats(vector<coat> coats)
	{
		 for(unsigned int i = 0; i < coats.size(); i++)
		 {
			 cout << coats[i].name << " " << coats[i].prob << '\n';
		 }
	}

	void kattis_submit() {
		string male;
		string female;
		getline(cin, female);
		getline(cin, male);

		Cat male_cat = Cat(male, female, true);
		Cat female_cat = Cat(male, female, false);

		double *male_probs = male_cat.probabilities;
		double *female_probs = female_cat.probabilities;

		vector<coat> coats = {};

		calcNoRedProbs(coats, male_probs, female_probs);
		calcRedProbs(coats, male_probs, female_probs);
		sort_coats(coats);
		print_coats(coats);

	}

	int main (){
		kattis_submit();
		//sumTest();
	}




