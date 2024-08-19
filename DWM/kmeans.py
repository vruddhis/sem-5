import random 
 
def distance(a, b):
    dimensions = len(a)
    ans = 0
    for i in range(dimensions):
        ans += (a[i] - b[i]) * (a[i] - b[i])
    return ans

def calculate_centroids(points):
    dimensions = len(points[0])
    n = len(points)
    ans = []   
    for i in range(dimensions):
        sum = 0
        for j in range(n):
            sum += points[j][i]
        ans.append(sum/n)
    return tuple(ans)
def k_means_cluster(k, points):
    n = len(points)
    centroids = random.sample(points, k) 
    if n <= k:
        return [[i] for i in points]
    
    clusters = [[] for _ in range(k)]
    
    converged = False
    iterations = 1
    while not converged:
        clusters = [[] for _ in range(k)]
    
        for point in points:
            distance_square_to_each_centroid = [(distance(point, centroid), centroid) for centroid in centroids]
            cluster_assignment_centroid = min(distance_square_to_each_centroid,  key=lambda item: item[0])[1]
            centroid_index = centroids.index(cluster_assignment_centroid)
            clusters[centroid_index].append(point)
        print("Clusters for iteration ", iterations, " are ", clusters)
        iterations += 1
        new_centroids = [calculate_centroids(cluster) for cluster in clusters]
        
        converged = (new_centroids == centroids)
        centroids = new_centroids
        
        if converged:
            return clusters
clusters = k_means_cluster(7, [(1,2), (2,1), (3,4), (5,3), (7,8), (34, 2), (113, 1), (90, 4), (3, 2), (-2, -4)])
for i in range(len(clusters)):
    print("Cluster ", i + 1, " is ", clusters[i])