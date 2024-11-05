import random

w = int(input("Enter the weight you want to give to interest (marks will have weight 1): "))
n = int(input("Enter the number of positions: "))

positions = []
hired = []
total = 0

for i in range(n):
    positions.append(input("What is this position called? "))
    v = int(input("How many vacancies for this position? "))
    hired.append([-1] * v)

k = int(input("Enter number of candidates: "))
people = []

for i in range(k):
    name = input("Enter candidate name: ")
    posts = []
    for j in range(n):
        mark = int(input(f"Enter marks for {positions[j]} (0-10): "))
        priority = int(input(f"Enter interest for {positions[j]} (0-5): "))
        score = mark + (priority * w)
        posts.append([score, priority, j])
    posts.sort(key=lambda x: x[1], reverse=True)
    people.append([name, posts])

random.shuffle(people)

for i in range(k):
    print(people[i][0] + " is now being interviewed")
    for j in range(n):
        if people[i][1][j][1] == 0 and people[i][1][j][0] > 5:
            decision = input(f"Interest for {positions[people[i][1][j][2]]} is 0. Proceed with interview? (y/n): ")
            if decision == "y":
                print("Interviewed for", positions[people[i][1][j][2]])
                total += 1
                if -1 in hired[people[i][1][j][2]]:
                    indx = hired[people[i][1][j][2]].index(-1)
                    hired[people[i][1][j][2]][indx] = people[i][1][j][0]
                    print("Hired for", positions[people[i][1][j][2]])
                    total += 1
                    break
                elif people[i][1][j][0] > min(hired[people[i][1][j][2]]):
                    indx = hired[people[i][1][j][2]].index(min(hired[people[i][1][j][2]]))
                    hired[people[i][1][j][2]][indx] = people[i][1][j][0]
                    print("Replaced a less qualified candidate for", positions[people[i][1][j][2]])
                    total += 2
                    break
        elif people[i][1][j][0] > 5:
            total += 1
            print("Interviewed for", positions[people[i][1][j][2]])
            if -1 in hired[people[i][1][j][2]]:
                indx = hired[people[i][1][j][2]].index(-1)
                hired[people[i][1][j][2]][indx] = people[i][1][j][0]
                print("Hired for", positions[people[i][1][j][2]])
                total += 1
                break
            elif people[i][1][j][0] > min(hired[people[i][1][j][2]]):
                indx = hired[people[i][1][j][2]].index(min(hired[people[i][1][j][2]]))
                hired[people[i][1][j][2]][indx] = people[i][1][j][0]
                print("Replaced a less qualified candidate for", positions[people[i][1][j][2]])
                total += 2
                break

print("Total number of interviews, hires, and replacements:", total)

            
            
        


    
        
    
              