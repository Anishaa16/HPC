#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        #pragma omp parallel for shared(swapped)
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped in the inner loop, the array is sorted
        if (!swapped) break;
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int *arr = new int[n];
    cout << "Enter " << n << " elements for the array: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Sequential Bubble Sort
    clock_t start = clock();
    bubbleSort(arr, n);
    clock_t end = clock();

    cout << "Sequential Bubble Sort Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
    cout << "Sorted array after sequential bubble sort: ";
    printArray(arr, n);

    // Parallel Bubble Sort
    start = clock();
    bubbleSort(arr, n);
    end = clock();

    cout << "Parallel Bubble Sort Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
    cout << "Sorted array after parallel bubble sort: ";
    printArray(arr, n);

    delete[] arr;

    return 0;
}
