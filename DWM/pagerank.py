def pagerank(graph):
    damping_factor=0.85
    n=len(graph)  
    pr=[1.0/n]*n  
    while True:
        new_pr=[0.0]*n  
        for i in range(n):
            for j in range(n):
                if graph[j][i]==1:  
                    outbound_links=sum(graph[j])  
                    if outbound_links>0:
                        new_pr[i]+=pr[j]/outbound_links  

            new_pr[i]=(1-damping_factor)+damping_factor*new_pr[i]
        if new_pr==pr:  # convergence
            break

        pr=new_pr  
        print("After one iteration:")
        print(pr)
    return pr

graph=[
    [0,1,1,0],  # A to others
    [0,0,1,0],  # B to others
    [1,0,0,0],  # C to others
    [0,0,1,0]   # D to others
]

pagerank_values=pagerank(graph)
print("PageRank values:", pagerank_values)

