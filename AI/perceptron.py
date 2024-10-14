import math
def sig(x):
 return 1/(1 + math.exp(-x))
def sign(x):
    if x>0: return 1
    return -1
n = int(input("How many weights/inputs are there?"))

ans = 0
for i in range(1, n+1):
    w = (int(input("What is weight " + str(i) + "?")))
    x = (int(input("What is input " + str(i) + "?")))
    ans += w + x
print("Summation is ", ans)
print("Using sigmoidal function")
y = sig(ans)
print("Output is ", y)
print("Using sign function")
y = sign(ans)
print("Output is ", y)
    
    
