#Calculate probabilities of male outcomes using simple probability theory. The probability of becoming a male/female (0.5) is included in these calculations
def calculate_male_outcomes(male, mother_gene, father_gene):
    outcome_dict = {}

    #Setup help variables, so we only call the class functions once
    dominant_red = male.has_dominant_red(mother_gene)
    dominant_dilution = male.has_dominant_dilution(mother_gene, father_gene)
    dominant_black = male.has_dominant_black(mother_gene, father_gene)

    #Calculations according to problem description
    outcome_dict["Red"]=1/2*dominant_red*dominant_dilution
    outcome_dict["Cream"] = 1/2*dominant_red * (1-dominant_dilution)
    outcome_dict["Black"] = 1/2*(1-dominant_red) * dominant_dilution *dominant_black
    outcome_dict["Blue"] = 1/2*(1-dominant_red)*dominant_black*(1-dominant_dilution)
    outcome_dict["Chocolate"] = 1/2 * (1-dominant_red) * dominant_dilution * (1-dominant_black)
    outcome_dict["Lilac"] = 1/2*(1-dominant_red)*(1-dominant_black) * (1-dominant_dilution)
    return outcome_dict


def calculate_femalemale_outcomes(female, mother_gene, father_gene):
    outcome_dict = {}

    #Setup help variables, so we only call the class functions once
    has_two_recessive_red = (1-female.has_one_dominant_red(mother_gene, father_gene) - female.has_two_dominant_red(mother_gene, father_gene))
    one_dominant_red = female.has_one_dominant_red(mother_gene, father_gene)
    two_dominant_red = female.has_two_dominant_red(mother_gene, father_gene)

    dominant_dilution = female.has_dominant_dilution(mother_gene, father_gene)
    dominant_black = female.has_dominant_black(mother_gene, father_gene)

    #Calculations according to problem description
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