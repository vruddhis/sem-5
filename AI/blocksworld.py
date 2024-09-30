def neighbours(now):
    n = len(now)
    num_empty = 0
    for i in range(n):
        if now[i] == []:
            num_empty += 1

    ans = []
    marked = 0
    for i in range(n):
        if now[i] == []:
            break
        else:
            for j in range(n):
                if j != i:
                    new_state = [stack.copy() for stack in now]  
                    block = new_state[i].pop()  
                    new_state[j].append(block)  
                    ans.append(new_state)
    return ans


def find_below(goal):
    below = {}
    for i in range(len(goal)):
        for j in range(len(goal[i])):
            if j==0:
                below[goal[i][j]] = 0
            else:
                below[goal[i][j]] = goal[i][j-1]
    return below
def heuristic(now, below):
    ans = 0
    for i in range(len(now)):
        for j in range(len(now[i])):
            if j==0:
                if below[now[i][j]] == 0:
                    ans += 1
                else:
                    ans -= 1
            else:
                if below[now[i][j]] == now[i][j-1]:
                    ans += 1
                else:
                    ans -= 1
    return ans



def hill_climbing(start, below):
    now = start
    while True:
        n = len(neighbours(now))
        max_till_now = -1
        for i in range(n):
            if max_till_now < heuristic(neighbours(now)[i], below):
                    max_till_now = heuristic(neighbours(now)[i], below)
                    max_indx = i
        if max_till_now > heuristic(now, below):
            print("We found a bigger node. Go to ", neighbours(now)[max_indx] )
            now = neighbours(now)[max_indx]
        else:
            print("No bigger neighbour. End here")
            return
        
n = int(input("Enter number of stacks"))
initial = [[] for _ in range(n)]
final = [[] for _ in range(n)]

for i in range(n):
    m = int(input("For initial state, how big is is stack"+ str(i+1)))
    for j in range(m):
        initial[i].append(input("Write label of block (bottom to top)"))
    m = int(input("For final state, how big is is stack" + str( i+1)))
    for j in range(m):
        final[i].append(input("Write label of block (bottom to top)"))
below = find_below(final)
print(below)
hill_climbing(initial, below)