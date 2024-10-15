import numpy as np
import pandas as pd

records = ["f","a","c","d","g","i","m","p","a","b","c","f","l","m","o","b","f","h","j","o","w","b", "c", "k", "s", "p","a", "f", "c", "e", "l", "p", "m", "n"]
records = np.array(records)
df = pd.DataFrame(records, columns=["items"])
df["incident_count"] = 1
indexNames = df[df['items'] == "nan" ].index
df.drop(indexNames , inplace=True)
df_table = df.groupby("items").sum().sort_values("incident_count", ascending=False).reset_index()

transaction = [["f","a","c","d","g","i","m","p"],["a","b","c","f","l","m","o"],["b","f","h","j","o","w"],["b", "c", "k", "s", "p"],["a", "f", "c", "e", "l", "p", "m", "n"]]
transaction = np.array(transaction)

from mlxtend.preprocessing import TransactionEncoder

te = TransactionEncoder()
te_ary = te.fit(transaction).transform(transaction)
dataset = pd.DataFrame(te_ary, columns=te.columns_)
print(df_table)
first5 = df_table["items"].head(5).values

dataset = dataset.loc[:,first5]
from mlxtend.frequent_patterns import fpgrowth

res=fpgrowth(dataset,min_support=0.6, use_colnames=True)
from mlxtend.frequent_patterns import association_rules
res=association_rules(res, metric="lift", min_threshold=1)
res.sort_values("confidence",ascending=False)
print(res)
