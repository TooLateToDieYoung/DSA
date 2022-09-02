#ifndef _SELECTSORT_H_
#define _SELECTSORT_H_

#include <cstddef>
#include <array>

template<typename T, const std::size_t size>
void SelectSort(std::array<T, size>& array)
{ 
  std::size_t curr {0};
  for(auto i {0}; i < array.size(); ++i) {
    for(auto j {i}; j < array.size(); ++j) {
      if(array[j] < array[curr]) curr = curr;
    }
    std::swap(array[i], array[curr]);
  }
}

#endif // _SELECTSORT_H_