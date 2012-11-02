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

void merge(int arr[], int start, int mid, int end) {
    int buf_size = end - start + 1;
    int buf[buf_size]; // can we do it without a buffer?!!
    int buf_i = 0;
    int i = start;
    int j = mid + 1;
    while (buf_i < buf_size) {
        int *b = &buf[buf_i];
        int arr_i;
        if (i <= mid && j <= end) {
            if (arr[j] < arr[i]) {
                arr_i = j++;
            } else {
                arr_i = i++;
            }
        } else if (i <= mid) {
            arr_i = i++;
        } else {
            arr_i = j++;
        }
        *b = arr[arr_i];
        buf_i++;
    }
    for (int i = 0; i < buf_size; i++) {
        arr[start + i] = buf[i];
    }
}

void mergesort(int arr[], int start, int end) {
    if (end <= start) {
        return;
    }
    int mid = start + (end - start) / 2;
    mergesort(arr, start, mid);
    mergesort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}


int main() {
    const int n = 10;
    int a[] = {6, 9, 3, 4, 100, 6, 8, 7, 2, 10};
    cout << "original" << endl;
    dump(a, n);
    //bubblesort(a, n);
    mergesort(a, 0, n - 1);
    dump(a, n);
    return 0;
}
