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
            if i != j:
                arr[i], arr[j] = arr[j], arr[i]
                swap_count += 1
    if i + 1 != high:
        arr[i + 1], arr[high] = arr[high], arr[i + 1]
        swap_count += 1
    return i + 1

def LumotoquickSort(arr, low, high):
    if low < high:
        pi = Lumotopartition(arr, low, high)
        LumotoquickSort(arr, low, pi - 1)
        LumotoquickSort(arr, pi + 1, high)


def hoare_partition(arr, low, high):
    global comparison_count, swap_count
    pivot_index = np.random.randint(low, high + 1, 1)[0]
    arr[low], arr[pivot_index] = arr[pivot_index], arr[low]
    pivot = arr[low]
    i = low
    j = high + 1

    while True:
        i += 1
        comparison_count += 1
        while i <= high and arr[i] < pivot:
            i += 1
            comparison_count += 1

        j -= 1
        comparison_count += 1
        while j >= low and arr[j] > pivot:
            j -= 1
            comparison_count += 1

        if i >= j:
            arr[low], arr[j] = arr[j], arr[low]
            return j

        arr[i], arr[j] = arr[j], arr[i]
        swap_count += 1

def hoare_quicksort(arr, low, high):
    if low < high:
        pi = hoare_partition(arr, low, high)
        hoare_quicksort(arr, low, pi-1)
        hoare_quicksort(arr, pi + 1, high)


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
hoare_quicksort(arr, 0, n-1)
end = time.time()
print("Time consumed in Hoare: ", end - start)
print("Total comparisons (Hoare):", comparison_count)
print("Total swaps (Hoare):", swap_count)



