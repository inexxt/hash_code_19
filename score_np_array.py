import numpy as np

def score_all(array):
    score = 0
    n_rows = len(array)
    for i in range(n_rows-1):
        score += score_rows(array[i],array[i+1])
    return score

def score_rows(arr1, arr2):
    c_arr1 = arr1[arr1 != 0]
    c_arr2 = arr2[arr2 != 0]
    common = np.intersect1d(c_arr1, c_arr2)
    if len(common) == 0:
        return 0
    else:
        arr1_diff = np.setdiff1d(c_arr1,common)
        arr2_diff = np.setdiff1d(c_arr2,common)
        return min(len(common),len(arr1_diff),len(arr2_diff))

#Przykład
arr = np.array([[1,2,3,4,0], [1,2,3,4,0], [4,3,5,7,0]])
score_all(arr)
