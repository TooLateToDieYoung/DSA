#ifndef _BUBBLESORT_H_
#define _BUBBLESORT_H_

#include <cstddef>
#include <array>

template<typename T, const std::size_t size>
void BubbleSort(std::array<T, size>& array)
{
  for(auto i {0}; i < array.size(); ++i)
    for(auto j {i}; j < array.size(); ++j)
      if(array[i] > array[j]) std::swap(array[i], array[j]);
}

#endif // _BUBBLESORT_H_