n = int(input("Enter number of nodes"))
adjMat = [[0] * n for _ in range(n)]
e = int(input("Enter number of edges"))
for _ in range(e):
    s = int(input("Label of start node"))
    e = int(input("label of end node"))
    w = int(input("Enter weight"))
    adjMat[s][e] = w
    adjMat[e][s] = w #comment out for directed graph
goal = int(input("What is goal node?"))
h = []
for i in range(n):
    h.append(int(input("What is h("+ str(i)+ ")?")))
start = int(input("What is start node?"))
now = start
dis = 0
visited = [0] * n
flag = 0

while flag == 0 and 0 in visited:
    visited[now] = 1
    loop_flag = 0
    print("Unvisited neighbours of ", now, ", with their f = g + h are:")
    mini = h[start]
    min_indx = -1
    for i in range(n):
        if adjMat[now][i] != 0 and visited[i] == 0:
            loop_flag = 1
            print("h(",i,") = ",h[i])
            print("g(",i,") = ",dis," + ",adjMat[now][i]," = ",dis + adjMat[now][i])
            print("f(", i, ") = ",h[i]+dis+adjMat[now][i])
            if mini > h[i]+adjMat[now][i]:
                mini = h[i]+adjMat[now][i]
                min_indx = i
    
    print("Goal test on ", now)
    if loop_flag == 0:
        break
    if now == goal:
        print("Goal node found. Distance is ", dis)
        flag = 1
        break
    print("We go to next node ", min_indx)
    dis += adjMat[now][min_indx]
    now = min_indx

if flag==0:
    print("Unsuccessful search")      



    
