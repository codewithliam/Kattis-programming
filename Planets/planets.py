import os

inputfile = open('sample.in')

#Store every case in arrayList. 
problem_vector = []

#Iterate through lines in text file
for line in inputfile: 
    problem_vector.append(line.strip().split())

""""
 This problem can be reformulated as solving a mathematical equation: 
Given earth starting position e0 and mars starting position m0, find the lowest n,m that fulfill: 

Eq 1: (365 - e0) + 365n = (678 - m0) + 687m """

answer_vec = []

#Loop that iterates through every case and solves it
for i in range(len(problem_vector)): 
    e0 = int(problem_vector[i][0])
    m0 = int(problem_vector[i][1])
    
    #To make the search efficient, we compare the most recent mars orbit with earth orbit in "real time", 
    #to do this we create a counter for each orbit, so that we can keep track of where we are in time. 
    earth_day_counter = 0
    mars_day_counter = 0

    while True: 
        #If we are already at the answer, append it to answers
        if e0 == 0 and m0== 0: 
            answer_vec.append(0)
            break

        # States equation according to Eq1, if it finds the solution, it appends it to answers
        if (365-e0) + earth_day_counter == (687-m0) + mars_day_counter:
            answer_vec.append(365-e0 + earth_day_counter)
            break

        # Counters for keeping track of where we are in time
        if earth_day_counter > mars_day_counter: 
            mars_day_counter += 687
        else: 
            earth_day_counter += 365

        if mars_day_counter > 10**8: 
            break
    

for i in range(len(answer_vec)): 
    with open('sample.ans', 'a') as f1:
        f1.write("Case " + str(i) + ": " + str(answer_vec[i]) + os.linesep)







