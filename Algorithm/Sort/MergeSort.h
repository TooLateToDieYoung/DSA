#ifndef _MERGESORT_H_
#define _MERGESORT_H_

#include <cstddef>
#include <array>

template <typename T, const std::size_t size>
void MergeSort(std::array<T, size>& array, const std::size_t head, const std::size_t tail)
{
  // ? recursion ends
  if( head == tail ) return;

  // ? split array
  const std::size_t half { ( head + tail ) / 2 };
  MergeSort<T, size>(array, head,     half);
  MergeSort<T, size>(array, half + 1, tail);

  // ? copy original datas
  std::size_t i {head};
  const std::size_t sizeL { half - head + 1 };
  const std::size_t sizeR { tail - half + 0 };
  T copyL[sizeL] { }; for(auto j {0}; i <= half; ++j) copyL[j] = array[i++];
  T copyR[sizeR] { }; for(auto j {0}; i <= tail; ++j) copyR[j] = array[i++];
  
  // ? sort & merge
  for(std::size_t I {head}, L {0}, R {0}; I <= tail; ++I) {
    if( L == sizeL ) { array[I] = copyR[R++]; continue; } 
    if( R == sizeR ) { array[I] = copyL[L++]; continue; }
    array[I] = ( copyL[L] < copyR[R] ) ? copyL[L++] : copyR[R++] ;
  }
}

#endif // _MERGESORT_H_