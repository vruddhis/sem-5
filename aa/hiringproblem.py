
import random
w = int(input("What is the weight you want to give to interest? Weight for marks will be 1"))
n = int(input("Enter number of posts"))

positions = []
hired = []
total = 0
for i in range(n):
    positions.append(input("What is this position called?"))
    v = int(input("How many jobs are vacant for this position?"))
    
    hired.append([-1] * v)
k = int(input("How many candidates?"))
people = []
for i in range(k):
    name = input("Enter name of person")
    posts = []
    for j in range(n):

        mark = (int(input(f"What are the marks scored by this person in the test for {positions[j]}, on a scale of 0 to 10?")))
        priority = (int(input(f"On a scale of 0 to 5, what is the interest of this person for {positions[j]}?")))
        posts.append([mark, priority, j])
    posts.sort(key = lambda x:x[1], reverse = True)
    people.append([name, posts])
random.shuffle(people)

for i in range(k):
    print(people[i][0] + " has come for interviews")
    for j in range(n):
        if people[i][1][j][1] == 0 and people[i][1][j][0] > 5:
            print("You put in your interest for ", positions[people[i][1][j][2]], " as 0. Do you want to give interview?")
            decision = input("Type y for yes ")
            if decision == y:
                print("Interviewed for ", positions[people[i][1][j][2]])
                total += 1
                if -1 in hired[people[i][1][j][2]]:
                    print("As a position was vacant, we hire candidate for this position")
                    total += 1
                    indx = hired[people[i][1][j][2]].index(-1)
                    hired[people[i][1][j][2]][indx] = people[i][1][j][0] * 0.5 * w
                    break
                elif people[i][1][j][0] * 0.5 * w > min(hired[people[i][1][j][2]]):
                    print("This candidate is better than the worst candidate we have for this position. We fire and hire")
                    total += 2
                    indx = hired[people[i][1][j][2]].index(min(hired[people[i][1][j][2]]))
                    hired[people[i][1][j][2]][indx] = people[i][1][j][0] * 0.5 * w
                    break
        elif people[i][1][j][0] > 5:
            total += 1
            print("Interviewed for ", positions[people[i][1][j][2]])
            if -1 in hired[people[i][1][j][2]]:
                    print("As a position was vacant, we hire candidate for this position")
                    total += 1
                    indx = hired[people[i][1][j][2]].index(-1)
                    hired[people[i][1][j][2]][indx] = people[i][1][j][0] * people[i][1][j][1] * w
                    break
            elif people[i][1][j][0] * people[i][1][j][1] * w > min(hired[people[i][1][j][2]]):
                    print("This candidate is better than the worst candidate we have for this position. We fire and hire")
                    total += 2
                    indx = hired[people[i][1][j][2]].index(min(hired[people[i][1][j][2]]))
                    hired[people[i][1][j][2]][indx] = people[i][1][j][0] * people[i][1][j][1] * w
                    break
print("Total number of interviews, hires and fires are ", total)
            
            
            
        


    
        
    
              