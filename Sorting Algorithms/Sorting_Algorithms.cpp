//
// Created by Hasanga Ranasinghe on 2023-06-02.
//

#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        if (i != arr.size() - 1) {
            cout << arr[i] << ", ";
        }
        else {
            cout << arr[i] << endl;
        }
    }
}

// Bubble Sort
// Time complexity = O(n^2)
vector<int> bubbleSort(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 1; j < arr.size() - i; j++) {
            if (arr[j] < arr[j - 1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
    return arr;
}

// Quick Sort
// Time complexity = O(nlogn)
vector<int> quickSort(vector<int> arr, int left, int right) {
    if (left >= right) {
        return arr;
    }
    int pivot = right;
    right--;

    while (left < right) {
        while (arr[left] < arr[pivot]) {
            left++;
        }
        while (arr[right] > arr[pivot]) {
            right--;
        }
        if (left < right) {
            swap(arr[left], arr[right]);
        }
    }

    swap(arr[left], arr[pivot]);

    return quickSort(quickSort(arr, 0, left - 1), left + 1, pivot);
}


// Insertion Sort
// Time complexity = O(n^2)
vector<int> insertionSort(vector<int> arr) {
    for (int i = 1; i < arr.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[i]) {
                int temp = arr[i];
                for (int k = i; k > j; k--) {
                    arr[k] = arr[k - 1];
                }
                arr[j] = temp;
            }
        }
    }
    return arr;
}

// Merge sort
// Time complexity = O(nlogn)
vector<int> merge(vector<int> arr1, vector<int> arr2) {
    vector<int> arr;

    int i = 0, j = 0;

    while (i < arr1.size() && j < arr2.size()) {
        if (arr1[i] < arr2[j]) {
            arr.push_back(arr1[i]);
            i++;
        }
        else if (arr2[j] < arr1[i]) {
            arr.push_back(arr2[j]);
            j++;
        }
        else {
            arr.push_back(arr1[i]);
            arr.push_back(arr2[j]);
            i++; j++;
        }
    }

    if (i < arr1.size()) {
        while (i < arr1.size()) {
            arr.push_back(arr1[i]);
            i++;
        }
    }

    else if (j < arr2.size()) {
        while (j < arr2.size()) {
            arr.push_back(arr2[j]);
            j++;
        }
    }

    return arr;
}

vector<int> merge(vector<int> array, int l1, int r1, int l2, int r2) {
    vector<int> arr;

    int i = l1, j = l2;

    while (i <= (r1 - l1) && j <= (r2 - l2)) {
        if (array[i] < array[j]) {
            arr.push_back(array[i]);
            i++;
        }
        else if (array[j] < array[i]) {
            arr.push_back(array[j]);
            j++;
        }
        else {
            arr.push_back(array[i]);
            arr.push_back(array[j]);
            i++; j++;
        }
    }

    if (i <= r1) {
        while (i <= r1) {
            arr.push_back(array[i]);
            i++;
        }
    }

    else if (j <= r2) {
        while (j <= r2) {
            arr.push_back(array[j]);
            j++;
        }
    }

    return arr;
}
vector<int> mergeSort(vector<int> arr) {
    if (arr.size() == 1) {
        return arr;
    }

    vector<int> left;
//    for (int i = 0; i < arr.size() / 2; i++) {
//        left.push_back(arr[i]);
//    }
//
    vector<int> right;
//    for (int i = arr.size() / 2; i < arr.size(); i++) {
//        right.push_back(arr[i]);
//    }

    left = mergeSort(arr, );
    right = mergeSort(arr, (r - l) / 2 + 1, r);

    return merge(arr, l, (r - l) / 2, (r - l) / 2 + 1, r);
}


int main() {

    vector<int> mainArr = {5, 3, 8, 2, 23, 78, 2, 9, 0, 45};
    printVector(mainArr);

    cout << "Bubble Sort" << endl;
    vector<int> bubbleArr = bubbleSort(mainArr);
    printVector(bubbleArr);

    cout << "Insertion Sort" << endl;
    vector<int> insertionArr = insertionSort(mainArr);
    printVector(insertionArr);

    cout << "Quick Sort" << endl;
    vector<int> quickArr = quickSort(mainArr, 0, mainArr.size() - 1);
    printVector(quickArr);

    cout << "Merge Sort" << endl;
    vector<int> mergeArr = mergeSort(mainArr, 0, 10);
    printVector(mergeArr);
}