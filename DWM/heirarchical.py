import pandas as pd
import numpy as np

def distance(a, b):
    return sum((a[i] - b[i]) ** 2 for i in range(len(a)))

def complete_linkage_clustering_tree(points):
    n = len(points)
    clusters = [[i] for i in range(n)]
    point_coordinates = {i: points[i] for i in range(n)}
    proximity_matrix = [[float('inf')] * n for _ in range(n)]
    
    for i in range(n):
        for j in range(i + 1, n):
            proximity_matrix[i][j] = proximity_matrix[j][i] = distance(points[i], points[j])
    
    merge_history = []
    
    while len(clusters) > 1:
        min_distance = float('inf')
        cluster_to_merge = (-1, -1)
        
        for i in range(len(clusters)):
            for j in range(i + 1, len(clusters)):
                max_dist = max(distance(point_coordinates[p1], point_coordinates[p2]) 
                               for p1 in clusters[i] for p2 in clusters[j])
                
                if max_dist < min_distance:
                    min_distance = max_dist
                    cluster_to_merge = (i, j)
        
        cluster1, cluster2 = cluster_to_merge
        new_cluster = clusters[cluster1] + clusters[cluster2]
        merge_history.append((clusters[cluster1], clusters[cluster2], min_distance))
        clusters[cluster1] = new_cluster
        del clusters[cluster2]
        
        for i in range(len(clusters)):
            if i != cluster1:
                max_dist = max(distance(point_coordinates[p1], point_coordinates[p2])
                               for p1 in clusters[i] for p2 in clusters[cluster1])
                proximity_matrix[i][cluster1] = proximity_matrix[cluster1][i] = max_dist

    return merge_history

df = pd.read_csv('wine.csv')
points = [tuple(x) for x in df.iloc[:, 1:].values]
tree = complete_linkage_clustering_tree(points)

for i, (cluster1, cluster2, dist) in enumerate(tree):
    print(f"Merge {i + 1}: Cluster {cluster1} and Cluster {cluster2}, Distance = {dist}")


