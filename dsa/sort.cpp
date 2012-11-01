#include <iostream>

using std::cout;
using std::endl;

void dump(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bubblesort(int arr[], int size) {
    if (size < 2) {
        return;
    }
    while(size) {
        int swapped = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] > arr[i+1]) {
                swap(&arr[i], &arr[i+1]);
                swapped = i + 1;
            }
        }
        // we don't need to recheck items
        // after the last swap
        size = swapped;
    }
}

void quicksort(int arr[], int size, int start, int end) {
    if (size < 2) {
        return;
    }
    int pivot = arr[start];
    int pivot_i = start;
    for (int i = start + 1; i < end; i++) {
        if (arr[i] < pivot) {
            int v = arr[i];
            for (int j = i; j > pivot_i; j--) {
                arr[j] = arr[j-1];
            }
            arr[pivot_i] = v;
            pivot_i += 1;
        }
    }
    quicksort(arr, pivot_i - start, start, pivot_i);
    quicksort(arr, end - pivot_i, pivot_i + 1, end);
}


int main() {
    const int n = 10;
    int a[] = {6, 2, 3, 4, 100, 6, 7, 8, 9, 10};
    cout << "original" << endl;
    dump(a, n);
    //bubblesort(a, n);
    quicksort(a, n, 0, n);
    dump(a, n);
    return 0;
}
