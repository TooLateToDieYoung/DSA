#ifndef _INSERTSORT_H_
#define _INSERTSORT_H_

#include <cstddef>
#include <array>

template<typename T, const std::size_t size>
void InsertSort(std::array<T, size>& array)
{ 
  T   temp;
  int j;
  for(int i {1}; i < (int)array.size(); ++i) {
    temp = array[i];
    j = i - 1;
    while( j >= 0 && array[j] > temp ) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = temp;
  }
}

#endif // _INSERTSORT_H_