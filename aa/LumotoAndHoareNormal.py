
import numpy as np
n = np.random.randint(0, 100000, 10)[0]
arr = np.random.randint(-10000000, 10000000, n)

def Lumotopartition(arr, low, high):
    
  
    pivot = arr[high] 
    
   
    i = (low - 1)
    for j in range(low, high):
        
        if (arr[j] <= pivot):
            i += 1 
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return (i + 1)
    

def LumotoquickSort(arr, low, high):
    if (low < high):
        
    
        pi = Lumotopartition(arr, low, high)
        
    
        LumotoquickSort(arr, low, pi - 1)
        LumotoquickSort(arr, pi + 1, high)

def Hoarepartition(arr, low, high):

    pivot = arr[low]
    i = low - 1
    j = high + 1

    while (True):
        i += 1
        while (arr[i] < pivot):
            i += 1

        j -= 1
        while (arr[j] > pivot):
            j -= 1

        
        if (i >= j):
            return j

        arr[i], arr[j] = arr[j], arr[i]




def HoarequickSort(arr, low, high):
   
    if (low < high):

        pi = Hoarepartition(arr, low, high)
        HoarequickSort(arr, low, pi)
        HoarequickSort(arr, pi + 1, high)

arr_copy = arr.copy()
import time
start = time.time()
LumotoquickSort(arr_copy, 0, n-1)
end = time.time()
print("Time consumed in Lumoto: ",end - start)
start = time.time()
HoarequickSort(arr, 0, n-1)
end = time.time()
print("Time consumed in Hoare: ",end - start)