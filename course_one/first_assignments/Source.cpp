#include <cstring>
#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <algorithm>
using namespace std;
constexpr int arr_size = 10'000'000;
int static_buffer[arr_size];

void swap_ends(int arr[], int size)
{
	for (auto i = size / 2 - 1, j = size - 1; i >= 0; --i, --j)
		swap(arr[i], arr[j]);
}

void swap_ends(vector<int>& arr)
{
	for (int i = arr.size() / 2 - 1, j = arr.size() - 1; i >= 0; --i, --j)
		swap(arr[i], arr[j]);
}

void swap_ends_homebrew_one(int arr[], int size)
{
	memcpy(static_buffer, arr, sizeof(int)*size);
	swap_ends(static_buffer, size);
	memcpy(arr, static_buffer, sizeof(int) * size);
}

void swap_ends_homebrew_two(int arr[], int size)
{
	auto dynamic_buffer = new int[size];
	memcpy(dynamic_buffer, arr, sizeof(int) * size);
	swap_ends(dynamic_buffer, size);
	memcpy(arr, dynamic_buffer, sizeof(int) * size);

	delete dynamic_buffer;
}

int* array_sort(int arr[], int size)
{
	auto dynamic_buffer = new int[size];
	memcpy(dynamic_buffer, arr, sizeof(int) * size);
	sort(dynamic_buffer, dynamic_buffer + size);
	
	return dynamic_buffer;
}

int main()
	{
		int scramble_arr[] = { 4,8,6,2,3,1,5 };
		int c_arr[] = { 1,2,3,4,5,6,7,8,9,10 };
		vector<int> vec = { 1,2,3,4,5,6,7,8,9 };
		vector<int>* vecd = new vector<int>{ 1,2,3,4,5,6,7,8 };
		
		auto start = std::chrono::steady_clock::now();
		swap_ends(c_arr, sizeof(c_arr) / sizeof(int));
		auto end = std::chrono::steady_clock::now();
		std::chrono::nanoseconds elapsed_time = end - start;
		std::cout << "elapsed time:" << elapsed_time.count() << endl;

		start = std::chrono::steady_clock::now();
		swap_ends(vec);
		end = std::chrono::steady_clock::now();
		elapsed_time = end - start;
		std::cout << "elapsed time:" << elapsed_time.count() << endl;

		start = std::chrono::steady_clock::now();
		swap_ends(*vecd);
		end = std::chrono::steady_clock::now();
		elapsed_time = end - start;
		std::cout << "elapsed time:" << elapsed_time.count() << endl;
		
		int* sorted_array = array_sort(scramble_arr, sizeof(scramble_arr) / sizeof(int));

		for (auto i : c_arr) cout << i << "";
		cout << endl;

		for (auto i : vec) cout << i << "";
		cout << endl;

		for (auto i : *vecd) cout << i << "";
		cout << endl;

		for (int i = 0; i <= 6; i++) cout << sorted_array[i] << "";
		cout << endl;

		delete vecd;
		return 0;
	}
