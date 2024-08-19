import numpy as np
import time

n = np.random.randint(0, 100000, 10)[0]
arr = np.random.randint(-10000000, 10000000, n)

comparison_count = 0
swap_count = 0

def Lumotopartition(arr, low, high):
    global comparison_count, swap_count
  
    pivot_index = np.random.randint(low, high + 1, 1)[0]
    arr[high], arr[pivot_index] = arr[pivot_index], arr[high]
    swap_count += 1
    pivot = arr[high] 

    i = low - 1
    for j in range(low, high):
        comparison_count += 1
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
            swap_count += 1
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    swap_count += 1
    return i + 1

def LumotoquickSort(arr, low, high):
    if low < high:
        pi = Lumotopartition(arr, low, high)
        LumotoquickSort(arr, low, pi - 1)
        LumotoquickSort(arr, pi + 1, high)

def Hoarepartition(arr, low, high):
    global comparison_count, swap_count
  
    pivot_index = np.random.randint(low, high + 1, 1)[0]
    pivot = arr[pivot_index]
    i = low - 1
    j = high + 1

    while True:
        i += 1
        comparison_count += 1
        while arr[i] < pivot:
            i += 1
            comparison_count += 1

        j -= 1
        comparison_count += 1
        while arr[j] > pivot:
            j -= 1
            comparison_count += 1

        if i >= j:
            return j

        arr[i], arr[j] = arr[j], arr[i]
        swap_count += 1

def HoarequickSort(arr, low, high):
    if low < high:
        pi = Hoarepartition(arr, low, high)
        HoarequickSort(arr, low, pi)
        HoarequickSort(arr, pi + 1, high)

arr_copy = arr.copy()

start = time.time()
LumotoquickSort(arr_copy, 0, n-1)
end = time.time()
print("Time consumed in Lomuto: ", end - start)
print("Total comparisons (Lomuto):", comparison_count)
print("Total swaps (Lomuto):", swap_count)

comparison_count = 0
swap_count = 0
arr_copy = arr.copy()

start = time.time()
HoarequickSort(arr, 0, n-1)
end = time.time()
print("Time consumed in Hoare: ", end - start)
print("Total comparisons (Hoare):", comparison_count)
print("Total swaps (Hoare):", swap_count)



