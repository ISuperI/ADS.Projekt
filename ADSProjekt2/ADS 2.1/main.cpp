// ADS Praktikum 2.1 Sortieren
// Name: Niklas Haug
#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include <iostream>
#include <omp.h>
#include <chrono>
#include "sorting.h"

using namespace std;

void benchmark_all();

int main(int argc, char **argv)
{

	Catch::Session().run();

	std::cout << "\nPress Enter to run measurement" << std::endl;
	std::cin.get();

	benchmark_all();

	return 0;
}

void benchmark_all()
{
	// file stream
	ofstream insertion_measurement;
	insertion_measurement.open("insertion.txt", ios::out | ios::app);

	ofstream quicksort_measurement;
	quicksort_measurement.open("quicksort.txt", ios::out | ios::app);

	ofstream mergesort_measurement;
	mergesort_measurement.open("mergesort.txt", ios::out | ios::app);

	ofstream heapsort_measurement;
	heapsort_measurement.open("heapsort.txt", ios::out | ios::app);

	ofstream shellsort_measurement;
	shellsort_measurement.open("shellsort_2n.txt", ios::out | ios::app);

	ofstream counting_measurement;
	counting_measurement.open("counting.txt", ios::out | ios::app);

	ofstream radix_measurement;
	radix_measurement.open("radix.txt", ios::out | ios::app);

	// benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 10000;
	int n_end = 1000000;

	vector<int> V;

	// actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step)
	{

		//"progress bar"
		std::cout << "Running Benchmarks with n: " << n << std::endl;

		double timeSumQuick = 0;
		double timeSumMerge = 0;
		double timeSumHeap = 0;
		double timeSumShell = 0;
		double timeSumInsert = 0;
		double timeSumCounting = 0;
		double timeSumRadix = 0;

		for (int i = 0; i < 10; i++)
		{
			// generate n random integers
			sorting::randomizeVector(V, n);
			vector<int> V2(V);
			vector<int> V3(V);
			vector<int> V4(V);
			vector<int> V5(V);
			vector<int> V6(V);
			vector<int> V7(V);

			// start measurement
			// dtime = omp_get_wtime();
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

			// execute QuickSort
			sorting::QuickSort(V, 0, V.size() - 1);

			// stop time
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			auto dtime = end - begin;
			// dtime = omp_get_wtime() - dtime;
			timeSumQuick += dtime.count();

			begin = std::chrono::steady_clock::now();

			// execute MergeSort
			vector<int> temp_array;
			temp_array.resize(V2.size());
			sorting::MergeSort(V2, temp_array, 0, V2.size() - 1);

			// stop time
			end = std::chrono::steady_clock::now();
			dtime = end - begin;
			timeSumMerge += dtime.count();

			begin = std::chrono::steady_clock::now();

			// execute HeapSort
			sorting::HeapSort(V3, V3.size());

			// stop time
			end = std::chrono::steady_clock::now();
			dtime = end - begin;
			timeSumHeap += dtime.count();

			begin = std::chrono::steady_clock::now();

			// execute ShellSort_2n
			sorting::ShellSort_2n(V4, V4.size());

			// stop time
			end = std::chrono::steady_clock::now();
			dtime = end - begin;
			timeSumShell += dtime.count();

			begin = std::chrono::steady_clock::now();

			// execute InsertionSort
			// sorting::InsertionSort(V5, V5.size());

			// stop time
			end = std::chrono::steady_clock::now();
			dtime = end - begin;
			timeSumInsert += dtime.count();

			begin = std::chrono::steady_clock::now();

			// execute CountingSort
			sorting::CountingSort(V6, 0, V6.size() - 1);

			// stop time
			end = std::chrono::steady_clock::now();
			dtime = end - begin;
			timeSumCounting += dtime.count();

			begin = std::chrono::steady_clock::now();

			// execute RadixSort
			sorting::RadixSort(V7, 0, V7.size() - 1);

			// stop time
			end = std::chrono::steady_clock::now();
			dtime = end - begin;
			timeSumRadix += dtime.count();
		}

		// write to file
		quicksort_measurement << n << "\t" << setprecision(10) << scientific << timeSumQuick / 10 << endl;
		mergesort_measurement << n << "\t" << setprecision(10) << scientific << timeSumMerge / 10 << endl;
		heapsort_measurement << n << "\t" << setprecision(10) << scientific << timeSumHeap / 10 << endl;
		shellsort_measurement << n << "\t" << setprecision(10) << scientific << timeSumShell / 10 << endl;
		insertion_measurement << n << "\t" << setprecision(10) << scientific << timeSumInsert / 10 << endl;
		counting_measurement << n << "\t" << setprecision(10) << scientific << timeSumCounting / 10 << endl;
		radix_measurement << n << "\t" << setprecision(10) << scientific << timeSumRadix / 10 << endl;
	}

	// close file handle
	quicksort_measurement.close();
	mergesort_measurement.close();
	heapsort_measurement.close();
	shellsort_measurement.close();
	insertion_measurement.close();
	counting_measurement.close();
	radix_measurement.close();
}