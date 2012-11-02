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

void quicksort(int arr[], int start, int end) {
    if (end <= start) {
        return;
    }
    int pivot_i = start + (end - start) / 2;
    int pivot = arr[pivot_i];
    swap(&arr[pivot_i], &arr[end]);
    int store_i = start;
    for (int i = start; i < end; i++) {
        if (arr[i] < pivot) {
            swap(&arr[i], &arr[store_i]);
            store_i += 1;
        }
    }
    swap(&arr[store_i], &arr[end]);
    quicksort(arr, start, store_i - 1);
    quicksort(arr, store_i + 1, end);
}


int main() {
    const int n = 10;
    int a[] = {6, 2, 3, 4, 100, 6, 7, 8, 9, 10};
    cout << "original" << endl;
    dump(a, n);
    //bubblesort(a, n);
    quicksort(a, 0, n - 1);
    dump(a, n);
    return 0;
}
