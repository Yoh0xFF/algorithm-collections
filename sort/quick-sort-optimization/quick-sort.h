#ifndef QUICK_SORT_H
#define	QUICK_SORT_H

#include <vector>

bool check_arr(const std::vector<int> &arr);

void print_arr_chunk(const std::vector<int> &arr, int l, int h);

void quick_sort_rec_opt(std::vector<int> &arr, int l, int h);

void quick_sort_iter_opt(std::vector<int> &arr, int l, int h);

void quick_sort_rec_std(std::vector<int> &arr, int l, int h);

#endif

