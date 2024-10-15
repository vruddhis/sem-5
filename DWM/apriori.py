import pandas as pd
from apyori import apriori
store_data = pd.read_csv('Lab2_store_data.csv', header=None)
records = []
for i in range(0, len(store_data)):
    records.append([str(store_data.values[i,j]) for j in range(0, store_data.shape[1])])


x = float(input("What is min support?"))
y = float(input("What is min confidence?"))
association_rules = apriori(records, min_support=x, min_confidence=y)
association_results = list(association_rules)
print(association_results)
