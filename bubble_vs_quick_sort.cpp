#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h> // Za QueryPerformanceCounter
#include <fstream>
using namespace std;

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int Partition(int p, int r, int A[]) {
    int pivot = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= pivot) {
            i++;
            Swap(A[i], A[j]);
        }
    }
    Swap(A[i + 1], A[r]);
    return i + 1;
}

void QuickSort(int p, int r, int A[]) {
    if (p < r) {
        int q = Partition(p, r, A);
        QuickSort(p, q - 1, A);
        QuickSort(q + 1, r, A);
    }
}

void BubbleSort(int A[], int p, int r) {
    for (int i = p; i <= r; i++) {
        for (int j = p; j < r - (i - p); j++) {
            if (A[j] > A[j + 1]) {
                Swap(A[j], A[j + 1]);
            }
        }
    }
}

double GetDurationMilliseconds(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER freq) {
    return (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
}

int main() {
    srand((unsigned)time(NULL));
    int i, size;

    cout << "Unesi velicinu niza:" << endl;
    cin >> size;

    int* A = (int*)malloc(size * sizeof(int));
    int* B = (int*)malloc(size * sizeof(int));

    for (i = 0; i < size; i++) {
        A[i] = rand();
        B[i] = A[i]; // isti elementi za poštenu usporedbu
    }

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    // QuickSort
    QueryPerformanceCounter(&start);
    QuickSort(0, size - 1, A);
    QueryPerformanceCounter(&end);
    cout << "QuickSort vrijeme: " << GetDurationMilliseconds(start, end, freq) << " ms" << endl;

    ofstream file1("OutputQuickSort.txt");
    for (i = 0; i < size; i++) {
        file1 << A[i] << endl;
    }
    file1.close();
    free(A);

    // BubbleSort
    QueryPerformanceCounter(&start);
    BubbleSort(B, 0, size - 1);
    QueryPerformanceCounter(&end);
    cout << "BubbleSort vrijeme: " << GetDurationMilliseconds(start, end, freq) << " ms" << endl;

    ofstream file2("OutputBubbleSort.txt");
    for (i = 0; i < size; i++) {
        file2 << B[i] << endl;
    }
    file2.close();
    free(B);

    return 0;
}
