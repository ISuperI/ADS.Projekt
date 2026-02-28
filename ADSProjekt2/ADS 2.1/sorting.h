#ifndef SORTING_H
#define SORTING_H

#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

namespace sorting
{
    void InsertionSort(vector<int> &arr, int n);

    void QuickSort(vector<int> &arr, int left, int right);
    int median3(vector<int> &arr, int left, int right);
    int partition(vector<int> &arr, int left, int right, int pivot);

    void Merge(vector<int> &a, vector<int> &b, int low, int pivot, int high);
    void MergeSort(vector<int> &a, vector<int> &b, int low, int high);

    void HeapSort(vector<int> &a, int n);
    void heapify(vector<int> &a, int n, int i);
    void leftCild(int i);

    void ShellSort_2n(vector<int> &a, int n);
    void ShellSort_2Square(vector<int> &a, int n);
    void shellSort(vector<int> &A, int gap);

    void CountingSort(vector<int> &arr, int left, int right);

    void RadixSort(vector<int> &arr, int left, int right);
    int getDigit(int number, int k, int base);
    void SortByDigit(vector<int> &arr, int left, int right, int k, int base);

    void randomizeVector(vector<int> &array, int n);
}
#endif