// ADS Praktikum 2.1 Sortieren
// Name: Niklas
#include "sorting.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

namespace sorting
{

    //****************
    // InsertionSort *
    //****************
    void InsertionSort(vector<int> &arr, int n)
    {
        int i, j, key;
        for (i = 1; i < n; i++)
        {
            key = arr[i];
            j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        
    }

    //************
    // QuickSort *
    //************
    int median3(vector<int> &arr, int left, int right)
    {
        int center = (left + right) / 2;
        if (arr[center] < arr[left])
            swap(arr[left], arr[center]);
        if (arr[right] < arr[left])
            swap(arr[left], arr[right]);
        if (arr[right] < arr[center])
            swap(arr[center], arr[right]);

        swap(arr[center], arr[right]);
        return arr[right];
    }

    int partition(vector<int> &arr, int p, int r)
    {
        int pivot = median3(arr, p, r);

        int i = p - 1;

        for (int j = p; j <= r - 1; j++)
        {
            if (arr[j] <= pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[r]);
        return i + 1;
    }

    void QuickSort(vector<int> &arr, int left, int right)
    {
        if (left < right)
        {
            int partitionIndex = partition(arr, left, right);
            QuickSort(arr, left, partitionIndex - 1);
            QuickSort(arr, partitionIndex + 1, right);
        }
    }

    //************
    // MergeSort *
    //************
    void Merge(vector<int> &a, vector<int> &b, int low, int pivot, int high)
    {
        int leftEnd = pivot - 1;
        int tmpPos = low;
        int n = high - low + 1;

        while (low <= leftEnd && pivot <= high)
        {
            if (a[low] <= a[pivot])
            {
                b[tmpPos] = a[low];
                low++;
            }
            else
            {
                b[tmpPos] = a[pivot];
                pivot++;
            }
            tmpPos++;
        }
        while (low <= leftEnd)
        {
            b[tmpPos++] = a[low++];
        }
        while (pivot <= high)
        {
            b[tmpPos++] = a[pivot++];
        }
        int i = high - n + 1;
        while (i <= high)
        {
            a[i] = b[i];
            i++;
        }
    }

    void MergeSort(vector<int> &a, vector<int> &b, int low, int high)
    {
        if (low < high)
        {
            int pivot = (low + high) / 2;
            MergeSort(a, b, low, pivot);
            MergeSort(a, b, pivot + 1, high);
            Merge(a, b, low, pivot + 1, high);
        }
    }

    //************
    // Heapsort  *
    //************

    int leftChild(int i)
    {
        return 2 * i + 1;
    }

    void heapify(vector<int> &arr, int p, int n)
    {
        int child;
        int tmp = arr[p];
        int j = p;

        while (leftChild(j) < n)
        {
            child = leftChild(j);
            if (child != n - 1 && arr[child] < arr[child + 1])
            {
                child++;
            }
            if (tmp < arr[child])
            {
                arr[j] = arr[child];
            }
            else
            {
                break;
            }
            j = child;
        }
        arr[j] = tmp;
    }

    void HeapSort(vector<int> &arr, int n)
    {

        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(arr, i, n);
        }
        for (int j = n - 1; j > 0; j--)
        {
            swap(arr[0], arr[j]);
            heapify(arr, 0, j);
        }
    }

    //************
    // Shellsort *
    //************

    void shellSort(vector<int> &A, int gap)
    {
        int N = A.size();
        for (int i = gap; i < N; ++i)
        {
            int tmp = A[i];
            int j = i;
            while (j >= gap && tmp < A[j - gap])
            {
                A[j] = A[j - gap];
                j -= gap;
            }
            A[j] = tmp;
        }
    }
    // Hier soll Hibbard implementiert werden
    void ShellSort_2n(vector<int> &a, int n)
    {
        int N = a.size();

        int k = 1;
        while (pow(2, k) - 1 < N)
        {
            k++;
        }
        for (int i = k - 1; i >= 0; i--)
        {
            int gap = pow(2, i) - 1;
            shellSort(a, gap);
        }
    }

    // Hier soll 2^i implementiert werden
    void ShellSort_2Square(vector<int> &a, int n)
    {
        int N = a.size();

        int k = 0;
        while (pow(2, k) < N)
        {
            k++;
        }
        for (int i = k - 1; i >= 0; i--)
        {
            int gap = pow(2, i);
            shellSort(a, gap);
        }
    }

    //***************
    // CountingSort *
    //***************

    void CountingSort(vector<int> &a, int left, int right)
    {
        if (left >= right)
        {
            return;
        }
        int M = a[left];
        for (int i = left + 1; i <= right; i++)
        {
            if (a[i] > M)
            {
                M = a[i];
            }
        }

        vector<int> Count(M + 1, 0);

        for (int i = left; i <= right; i++)
        {
            Count[a[i]]++;
        }

        int i = left;
        for (int j = 0; j <= M; j++)
        {
            while (Count[j] > 0)
            {
                a[i] = j;
                i++;
                Count[j]--;
            }
        }
    }

    //************
    // RadixSort *
    //************
    int getDigit(int number, int k, int base)
    {
        for (int i = 1; i < k; i++)
        {
            number /= base;
        }
        return number % base;
    }
    void SortByDigit(vector<int> &arr, int left, int right, int k, int base)
    {
        int n = right - left + 1;
        vector<int> Count(base, 0);
        vector<int> Position(base, 0);
        vector<int> B(n);

        for (int i = left; i <= right; i++)
        {
            int j = getDigit(arr[i], k, base);
            Count[j]++;
        }

        Position[0] = 0;
        for (int i = 1; i < base; i++)
        {
            Position[i] = Position[i - 1] + Count[i - 1];
        }
        for (int i = left; i <= right; i++)
        {
            int j = getDigit(arr[i], k, base);
            B[Position[j]++] = arr[i];
        }
        for (int i = left; i <= right; i++)
        {
            arr[left + i] = B[i];
        }
    }
    void RadixSort(vector<int> &arr, int left, int right)
    {
        int base = 10;
        int k_max = arr[left];
        for (int i = left + 1; i <= right; i++)
        {
            if (arr[i] > k_max)
                k_max = arr[i];
        }

        int k_max_zif = 0;
        while (k_max > 0)
        {
            k_max /= base;
            k_max_zif++;
        }

        for (int k = 1; k <= k_max_zif; k++)
        {
            SortByDigit(arr, left, right, k, base);
        }
    }

    //*******************

    void randomizeVector(vector<int> &array, int n)
    {
        array.resize(n);

        for (unsigned int i = 0; i < array.size(); i++)
            array[i] = rand() % 1000000;
    }

}



