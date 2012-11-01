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

void quicksort(int a[], int size, int start, int end) {
    if (size < 2) {
        return;
    }

}


int main() {
    const int n = 8;
    int a[] = {1, 90, 6, 120, 2, 4, 1, 94};
    cout << "original" << endl;
    dump(a, n);
    bubblesort(a, n);
    dump(a, n);
    return 0;
}
