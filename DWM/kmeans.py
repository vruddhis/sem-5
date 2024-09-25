import pandas as pd
import random
from collections import Counter

def distance(a, b):
    dimensions = len(a)
    ans = 0
    for i in range(dimensions):
        ans += (a[i] - b[i]) ** 2
    return ans

def calculate_centroids(points):
    dimensions = len(points[0])
    n = len(points)
    ans = []
    for i in range(dimensions):
        sum = 0
        for j in range(n):
            sum += points[j][i]
        ans.append(sum / n)
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
            cluster_assignment_centroid = min(distance_square_to_each_centroid, key=lambda item: item[0])[1]
            centroid_index = centroids.index(cluster_assignment_centroid)
            clusters[centroid_index].append(point)
        iterations += 1
        new_centroids = [calculate_centroids(cluster) for cluster in clusters]
        converged = (new_centroids == centroids)
        centroids = new_centroids
        if converged:
            return clusters


df = pd.read_csv('wine.csv')
labels = df.iloc[:, 0].values
data = df.iloc[:, 1:].values
points = [tuple(row) for row in data]
clusters = k_means_cluster(3, points)
point_to_label = {tuple(row): label for row, label in zip(data, labels)}
for i, cluster in enumerate(clusters):
    cluster_labels = [point_to_label[point] for point in cluster]
    label_counts = Counter(cluster_labels)
    most_common_label, common_count = label_counts.most_common(1)[0]

    print(f"Cluster {i + 1}: {len(cluster)} points, most common label is {most_common_label} with {common_count} matches.")

