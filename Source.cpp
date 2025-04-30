#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<iostream>

using namespace std;
int flag;
void Swap(int A[], int i, int j) {
	int temp= 0;
	temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}
void Heapify(int A[], int i, int m) {

	int l = 2 * i;
	int r = 2 * i + 1;
	int max = i;
	if (l <= m && A[l] > A[max])
		max = l;
	if (r <= m && A[r] > A[max])
		max = r;
	if (max != i) {
		Swap(A, i,max);
		Heapify(A, max, m);
	}
		


}
void Heapify2(int A[], int i, int m) {
	while (i <= m) {

		int l = 2 * i;
		int r = 2 * i + 1;
		int max = i;
		if (l <= m && A[l] > A[max])
			max = l;
		if (r <= m && A[r] > A[max])
			max = r;
		if (i != max) {
			Swap(A, i, max);
			i = max;
		}
		else {
			break;
		}
			
	}

}
void BuildHeap(int n, int A[]) {
	int i;
	for (i = (n - 1) / 2; i >= 0; i--)
		if (flag == 0)
			Heapify(A, i, n - 1);
		else
			Heapify2(A, i, n - 1);
}
void HeapSort(int n, int A[]) {
	int m;
	BuildHeap(n, A);
	m = n - 1;
	while (m >= 1) {
		Swap(A, 0, m);
		m = m - 1;
		Heapify(A, 0, m);
	}
}
void HeapSort2(int n, int A[]) {
	int m;
	BuildHeap(n, A);
	m = n - 1;
	while (m >= 1) {
		Swap(A, 0, m);
		m = m - 1;
		Heapify2(A, 0, m);
	}
}
int main() {
	LARGE_INTEGER freq, start1, start2, end1, end2;
	QueryPerformanceFrequency(&freq);
	double elapsedTime1, elapsedTime2  = 0.0;
		char c;
	int vrijeme1, vrijeme2, vrijeme3, vrijeme4, i, size;
	cout << "Unesi velicinu niza" << endl;
	cin >> size;
	int* A = (int*)malloc(size * sizeof(int));
	int* B = (int*)malloc(size * sizeof(int));
	if (A == NULL || B == NULL) {
		cout << "Nema doboljno memorije za polje ove velicine." << endl;
		return 0;
	}
	else {
		for (i = 0; i < size; i++) {
			A[i] = rand();
			B[i] = A[i];
		}
		flag = 0;
		QueryPerformanceCounter(&start1);
		HeapSort(size, A);
		QueryPerformanceCounter(&end1);
		elapsedTime1 = (double)(end1.QuadPart - start1.QuadPart) / freq.QuadPart;
		cout << "vrijeme Heap Sort sa rekurzivnim Heapify: " << elapsedTime1 << " [s] ili u ms: " << elapsedTime1*1000 << "\n" << endl;
		flag = 1;
		QueryPerformanceCounter(&start2);
		HeapSort2(size, B);
		QueryPerformanceCounter(&end2);
		elapsedTime2 = (double)(end2.QuadPart - start2.QuadPart) / freq.QuadPart;
		cout << "vrijeme Heap Sort sa iterativnim Heapify: " << elapsedTime2  << "[s] ili u ms : " << elapsedTime2*1000 << "\n" << endl;
		free(A);
		//system("pause");
		return 0;
	}
}