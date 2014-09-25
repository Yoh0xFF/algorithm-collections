#include "quick-sort.h"

#include <vector>
#include <iostream>

static int partition(std::vector<int> &arr, int l, int h);

static int mediana_index(const std::vector<int> &arr, int a, int b, int c);

static void mediana(std::vector<int> &arr, int l, int h);

static void insertion_sort(std::vector<int> &arr, int l, int h);

static int partition(std::vector<int> &arr, int l, int h)
{
    int x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++)
    {
        if (arr[j] <= x)
        {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    ++i;
    std::swap(arr[i], arr[h]);

    return (i);
}

static int mediana_index(const std::vector<int> &arr, int a, int b, int c)
{
    return (arr[a] < arr[b] ?
            (arr[b] < arr[c] ? b : arr[a] < arr[c] ? c : a) :
            (arr[b] > arr[c] ? b : arr[a] > arr[c] ? c : a));
}

static void mediana(std::vector<int> &arr, int l, int h)
{
    int len = h - l + 1;
        
    if (len > 7)
    {
        int a = l, b = l + (len >> 2), c = h;
        if (len > 40)
        {
            int s = len / 8;
            a = mediana_index(arr, a, a + s, a + s * 2);
            b = mediana_index(arr, b - s, b, b + s);
            c = mediana_index(arr, c - s * 2, c - s, c);
        }
        b = mediana_index(arr, a, b, c);
        std::swap(arr[b], arr[h]);
    }   
}

void insertion_sort(std::vector<int> &arr, int l, int h)
{
    int val = 0, pos = 0;
    for (int i = (l + 1); i <= h; ++i)
    {
        val = arr[i];
        pos = i;
        while (pos > 0 && val < arr[pos - 1])
        {
            arr[pos] = arr[pos - 1];
            --pos;
        }
        arr[pos] = val;
    }
}

bool check_arr(const std::vector<int> &arr)
{
    for (int i = 1; i < arr.size(); ++i)
    {
        if (arr[i - 1] > arr[i]) return false;
    }

    return true;
}

void print_arr_chunk(const std::vector<int> &arr, int l, int h)
{
    for (int i = l; i <= h; ++i)
    {
        std::cout << arr[i] << ',';
        if (i != 0 && i % 20 == 0) std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void quick_sort_rec_opt(std::vector<int> &arr, int l, int h)
{
    if (l < h)
    {
        if ((h - l + 1) > 7)
        {
            mediana(arr, l, h);
            int p = partition(arr, l, h);
            quick_sort_rec_opt(arr, l, p - 1);
            quick_sort_rec_opt(arr, p + 1, h);
        } else
        {
            insertion_sort(arr, l, h);
        }
    }
}

void quick_sort_iter_opt(std::vector<int> &arr, int l, int h)
{
    std::vector<int> stack(h - l + 1);
    int top = -1;

    stack[++top] = l;
    stack[++top] = h;

    while (top >= 0)
    {
        h = stack[top--];
        l = stack[top--];

        if ((h - l + 1) > 7)
        {
            mediana(arr, l, h);

            int p = partition(arr, l, h);

            if (p - 1 > l)
            {
                stack[++top] = l;
                stack[++top] = p - 1;
            }

            if (p + 1 < h)
            {
                stack[++top] = p + 1;
                stack[++top] = h;
            }
        } else
        {
            insertion_sort(arr, l, h);
        }
    }
}

void quick_sort_rec_std(std::vector<int> &arr, int l, int h)
{
    if (l < h)
    {
        int p = partition(arr, l, h);
        quick_sort_rec_std(arr, l, p - 1);
        quick_sort_rec_std(arr, p + 1, h);
    }
}