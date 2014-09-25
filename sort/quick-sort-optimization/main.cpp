/*
 Quick sort optimization using median and insertion sort 
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "quick-sort.h"

using namespace std;

void test_2();
void test_1();

int main()
{  
    test_1();
}

void test_2()
{
    const int N = 1000;
    srand(time(0));

    bool ok = true;
    for (int j = 0; j < 10000; ++j)
    {
        vector<int> arr1;
        for (int i = 0; i < N; ++i) arr1.push_back(rand() % 5000);

        quick_sort_iter_opt(arr1, 0, N - 1);
        
        if (!check_arr(arr1)) 
        {
            ok = false;
            break;
        }
    }
    
    cout << (ok ? "TRUE" : "FALSE") << endl;
}

void test_1()
{
    const int N = 10000000;

    srand(time(0));

    vector<int> arr1;
    for (int i = 0; i < N; ++i) arr1.push_back(rand() % 1000000000);
    vector<int> arr2(arr1);
    vector<int> arr3(arr1);

    clock_t start = clock();
    quick_sort_rec_opt(arr1, 0, N - 1);
    cout << "optimized quick sort, recursion, time taken: " << (double) (clock() - start) / CLOCKS_PER_SEC << endl;

    start = clock();
    quick_sort_iter_opt(arr2, 0, N - 1);
    cout << "optimized quick sort, iteration, time taken: " << (double) (clock() - start) / CLOCKS_PER_SEC << endl;

    start = clock();
    quick_sort_rec_std(arr3, 0, N - 1);
    cout << "standard quick sort, recursion, time taken: " << (double) (clock() - start) / CLOCKS_PER_SEC << endl;
    
    // print_arr(arr1);
    // print_arr(arr2);
    // print_arr(arr3);
}

