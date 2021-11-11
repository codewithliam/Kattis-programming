import sys
from collections import Counter
cat_coat = []

#inputfile = open('sample1.in')

#Iterate through lines in text file
for line in sys.stdin: 
    cat_coat.append(line.strip())

class FemaleCat:
  def __init__(self):

    self.color_dict = {
        "Black": [1, 0.5, 0, 0, 1, 0.5],
        "Blue": [1, 0.5, 0, 0, 0, 0], 
        "Chocolate": [0, 0, 0, 0, 1, 0.5], 
        "Lilac": [0, 0, 0, 0, 0, 0], 
        "Red": [0.5, 0.5, 1, 1, 1, 0.5], 
        "Cream": [0.5, 0.5, 1, 1, 0, 0], 
        "Black-Red Tortie": [1, 0.5, 1, 0, 1, 0.5], 
        "Blue-Cream Tortie": [1, 0.5, 1, 0, 0, 0], 
        "Chocolate-Red Tortie": [0, 0, 1, 0, 1, 0.5], 
        "Lilac-Cream Tortie": [0, 0, 1, 0, 0, 0]
    }
  def has_two_dominant_red(self, mother_gene, father_gene): 
        dom_from_mother_prob = (mother_gene[2] + mother_gene[3])/2 
        dom_from_father_prob = father_gene[2]
        prob = dom_from_mother_prob*dom_from_father_prob
        return prob

  def has_one_dominant_red(self, mother_gene, father_gene):

        dom_from_mother_prob = (mother_gene[2] + mother_gene[3])/2 
        dom_from_father_prob = father_gene[2]
        prob = (1 - (1-dom_from_mother_prob)*(1-dom_from_father_prob)) - self.has_two_dominant_red(mother_gene, father_gene)
        return prob

  def has_dominant_black(self, mother_gene, father_gene): 
        dom_from_mother_prob = (mother_gene[0] + mother_gene[1])/2 
        dom_from_father_prob = (father_gene[0] + father_gene[1])/2
        # Probability of dominant gene equals 1 - (probability of recessive genes passed from both mom and dad) 
        prob = 1 - (1-dom_from_mother_prob)*(1-dom_from_father_prob)
        return prob

  def has_dominant_dilution(self, mother_gene, father_gene): 
        dom_from_mother_prob = (mother_gene[4] + mother_gene[5])/2 
        dom_from_father_prob = (father_gene[3] + father_gene[4])/2
        # Probability of dominant gene equals 1 - (probability of recessive genes passed from both mom and dad) 
        prob = 1 - (1-dom_from_mother_prob)*(1-dom_from_father_prob)
        return prob

class MaleCat:
  def __init__(self):

    self.color_dict = {
        "Black": [1, 0.5, 0, 1, 0.5],
        "Blue": [1, 0.5, 0, 0, 0], 
        "Chocolate": [0, 0, 0, 1, 0.5], 
        "Lilac": [0, 0, 0, 0, 0], 
        "Red": [0.5, 0.5, 1, 1, 0.5], 
        "Cream": [0.5, 0.5, 1, 0, 0], 
    }

# Determines probability that male kitten has dominant red gene
  def has_dominant_red(self, mother_gene):
        prob= (mother_gene[2] + mother_gene[3])/2 
        return prob 

  def has_dominant_black(self, mother_gene, father_gene): 
        dom_from_mother_prob = (mother_gene[0] + mother_gene[1])/2 
        dom_from_father_prob = (father_gene[0] + father_gene[1])/2
        # Probability of dominant gene equals 1 - (probability of recessive genes passed from both mom and dad) 
        prob = 1 - (1-dom_from_mother_prob)*(1-dom_from_father_prob)
        return prob

  def has_dominant_dilution(self, mother_gene, father_gene): 
        dom_from_mother_prob = (mother_gene[4] + mother_gene[5])/2 
        dom_from_father_prob = (father_gene[3] + father_gene[4])/2
        # Probability of dominant gene equals 1 - (probability of recessive genes passed from both mom and dad) 
        prob = 1 - (1-dom_from_mother_prob)*(1-dom_from_father_prob)
        return prob

female = FemaleCat()
male = MaleCat()

mother_gene = female.color_dict[cat_coat[0]]
father_gene = male.color_dict[cat_coat[1]]

## Now we move on the the probability calculations

def calculate_male_outcomes(male, mother_gene, father_gene):
    outcome_dict = {}

    dominant_red = male.has_dominant_red(mother_gene)
    dominant_dilution = male.has_dominant_dilution(mother_gene, father_gene)
    dominant_black = male.has_dominant_black(mother_gene, father_gene)

    outcome_dict["Red"]=1/2*dominant_red*dominant_dilution
    outcome_dict["Cream"] = 1/2*dominant_red * (1-dominant_dilution)
    outcome_dict["Black"] = 1/2*(1-dominant_red) * dominant_dilution *dominant_black
    outcome_dict["Blue"] = 1/2*(1-dominant_red)*dominant_black*(1-dominant_dilution)
    outcome_dict["Chocolate"] = 1/2 * (1-dominant_red) * dominant_dilution * (1-dominant_black)
    outcome_dict["Lilac"] = 1/2*(1-dominant_red)*(1-dominant_black) * (1-dominant_dilution)
    return outcome_dict


def calculate_femalemale_outcomes(female, mother_gene, father_gene):
    outcome_dict = {}

    has_two_recessive_red = (1-female.has_one_dominant_red(mother_gene, father_gene) - female.has_two_dominant_red(mother_gene, father_gene))
    one_dominant_red = female.has_one_dominant_red(mother_gene, father_gene)
    two_dominant_red = female.has_two_dominant_red(mother_gene, father_gene)

    dominant_dilution = female.has_dominant_dilution(mother_gene, father_gene)
    dominant_black = female.has_dominant_black(mother_gene, father_gene)

    outcome_dict["Red"] = 1/2*two_dominant_red*dominant_dilution
    outcome_dict["Cream"] = 1/2*two_dominant_red*(1-dominant_dilution)
    outcome_dict["Black"] = 1/2 * has_two_recessive_red * dominant_black*dominant_dilution
    outcome_dict["Blue"] = 1/2 * has_two_recessive_red * dominant_black * (1-dominant_dilution)
    outcome_dict["Chocolate"] = 1/2 * has_two_recessive_red * dominant_dilution * (1-dominant_black)
    outcome_dict["Lilac"] = 1/2 * has_two_recessive_red * (1-dominant_black) * (1-dominant_dilution) 
    outcome_dict["Black-Red Tortie"] = 1/2 * one_dominant_red * dominant_black * dominant_dilution
    outcome_dict["Blue-Cream Tortie"] = 1/2 * one_dominant_red * dominant_black * (1-dominant_dilution)
    outcome_dict["Chocolate-Red Tortie"] = 1/2 * one_dominant_red * dominant_dilution * (1-dominant_black) 
    outcome_dict["Lilac-Cream Tortie"] = 1/2 * one_dominant_red * (1-dominant_dilution) * (1-dominant_black)
    
    return outcome_dict



male_outcomes = calculate_male_outcomes(male, mother_gene, father_gene)
female_outcomes = calculate_femalemale_outcomes(female, mother_gene, father_gene)

combined_dict = Counter(male_outcomes) + Counter(female_outcomes)
combined_dict = combined_dict.most_common()

    
for i in range(len(combined_dict)): 
    print(combined_dict[i][0] + " " + str(combined_dict[i][1]))

