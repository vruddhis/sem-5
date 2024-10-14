n = int(input("How many weights/inputs are there?"))

ans = 0
for i in range(1, n+1):
    w = (int(input("What is weight " + str(i) + "?")))
    x = (int(input("What is input " + str(i) + "?")))
    ans += w + x
print("Summation is ", ans)
print("Using signum function")
if ans > 0:
    print("Output is 1")
elif ans < 0:
    print("Output is -1")
else:
    print("Output is 0")
    
    