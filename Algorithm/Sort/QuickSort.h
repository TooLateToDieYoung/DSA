#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

#include <cstddef>
#include <array>

template <typename T, const std::size_t size>
void QuickSort(std::array<T, size>& array, const std::size_t head, const std::size_t tail)
{
  std::size_t temp {head};
  
  for(std::size_t curr {head}; curr != tail; ++curr)
    if(array[curr] < array[tail]) std::swap(array[temp++], array[curr]);

  std::swap(array[temp], array[tail]);

  if( head < temp ) QuickSort(array, head, temp - 1);
  if( temp < tail ) QuickSort(array, temp + 1, tail);
}

#endif // _QUICKSORT_H_