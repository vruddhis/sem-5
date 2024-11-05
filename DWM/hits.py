import math

def adjacent_matrix(outlinks):
    rows = len(outlinks[0])
    col = len(outlinks)
    for i in range(rows):
        for j in range(col):
            print(outlinks[i][j], end=" ")
        print()

def authority_hub_score(outlinks):
    size = len(outlinks[0])
    hub_scores = [1.0 for i in range(size)]
    authority_scores = [1.0 for i in range(size)]
    for _ in range(3):
        # Calculating the hub scores of the nodes
        temp_au = authority_scores[:]
        for j in range(size):
            temp_auth = 0.0
            for i in range(size):
                if outlinks[i][j] == 1:
                    temp_auth += hub_scores[i]
            authority_scores[j] = temp_auth
        for i in range(size):
            temp_hub = 0.0
            for j in range(size):
                if outlinks[i][j] == 1:
                    temp_hub += temp_au[j]
            hub_scores[i] = temp_hub
        sum_of_square_hubs = sum(map(lambda i: i, hub_scores))
        print(hub_scores)
        for i in range(len(hub_scores)):
            hub_scores[i] /= sum_of_square_hubs
        sum_of_square_authorities = sum(map(lambda i: i, authority_scores))
        for i in range(len(authority_scores)):
            authority_scores[i] /= sum_of_square_authorities

    return authority_scores, hub_scores

outlinks = [
    [0, 1, 1, 1],
    [0, 0, 1, 1],
    [1, 0, 0, 1],
    [0, 0, 0, 1]
]

print("Adjacency matrix of the graph:")
adjacent_matrix(outlinks)
authority_scores, hub_scores = authority_hub_score(outlinks)
print("Hub Scores of each node:")
for i in (hub_scores):
    print(round(i, 5))
print("Authority Scores of each node:")
for i in (authority_scores):
    print(round(i, 5))
