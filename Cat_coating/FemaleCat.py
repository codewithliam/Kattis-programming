#Helpclass to define the different coat outcomes for female cat. Both FemaleCat and MaleCat could inherit from a Cat superclass to make the solution more elegant
class FemaleCat:
  def __init__(self):

      # The gene compositions for different coats are written as vectors, with Black (B) being the first two elements, Red (O) the two middle ones, and Dilution (D) as the two last
      # 1 mean it's a dominant gene (B, O, D), 0 means a recessive (b, o ,d), and 0.5 means it's unknown (B/b, O/o, D/d), and the probability of a dominant gene is 0.5. 
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
        #Calculates the probability of the offpring recieving two dominant red genes, given a mother gene composition, and a father gene composition
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
        #Calculates the probability of the offpring recieving one dominant black gene, given a mother gene composition, and a father gene composition

        dom_from_mother_prob = (mother_gene[0] + mother_gene[1])/2 
        dom_from_father_prob = (father_gene[0] + father_gene[1])/2
        # Probability of dominant gene equals 1 - (probability of recessive genes passed from both mom and dad) 
        prob = 1 - (1-dom_from_mother_prob)*(1-dom_from_father_prob)
        return prob

  def has_dominant_dilution(self, mother_gene, father_gene): 
      #Calculates the probability of the offpring recieving one dominant Dilution gene, given a mother gene composition, and a father gene composition

        dom_from_mother_prob = (mother_gene[4] + mother_gene[5])/2 
        dom_from_father_prob = (father_gene[3] + father_gene[4])/2
        # Probability of dominant gene equals 1 - (probability of recessive genes passed from both mom and dad) 
        prob = 1 - (1-dom_from_mother_prob)*(1-dom_from_father_prob)
        return prob