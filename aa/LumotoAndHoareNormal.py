import numpy as np
import time

n = np.random.randint(0, 100000, 10)[0]
arr = np.random.randint(-10000000, 10000000, n)


def lomuto_partition(arr, low, high):
    global comparison_count, swap_count
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

def lomuto_quicksort(arr, low, high):
    if low < high:
        pi = lomuto_partition(arr, low, high)
        lomuto_quicksort(arr, low, pi - 1)
        lomuto_quicksort(arr, pi + 1, high)

def hoare_partition(arr, low, high):
    global comparison_count, swap_count
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


print("Array length", n)
comparison_count = 0
swap_count = 0
start = time.time()
lomuto_quicksort(arr.copy(), 0, n - 1)
end = time.time()
print("Time consumed in Lomuto: ", end - start)

print("Total comparisons:", comparison_count)
print("Total swaps:", swap_count)

comparison_count = 0
swap_count = 0
start = time.time()
hoare_quicksort(arr.copy(), 0, n - 1)
end = time.time()
print("Time consumed in Hoare: ", end - start)

print("Total comparisons:", comparison_count)
print("Total swaps:", swap_count)