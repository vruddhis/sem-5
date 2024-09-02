n = int(input("Enter number of nodes"))
adjMat = [[0] * n for _ in range(n)]
e = int(input("Enter number of edges"))
for _ in range(e):
    s = int(input("Label of start node"))
    e = int(input("label of end node"))
    adjMat[s][e] = 1
    adjMat[e][s] = 1 #comment out for directed graph
h = []
for i in range(n):
    h.append(int(input("What is value of"+ str(i)+ "?")))
start = int(input("What is start node?"))

def hill_climbing(start, h):
    visited = [0] * n
    now = start
    visited[now] = 1
    while True:
        if 0 not in visited:
            print("All have been visited. So maxima is ", now)
            return
        max_indx = -1
        max_till_now = -1
        for i in range(n):
            if adjMat[now][i] == 1:
                if max_till_now < h[i]:
                    max_till_now = h[i]
                    max_indx = i
        if max_till_now > h[now]:
            print("We found a bigger node. Go to ", max_indx)
            now = max_indx
            visited[now] = 1
        else:
            print("No bigger neighbour. End here")
            return
hill_climbing(start, h)
