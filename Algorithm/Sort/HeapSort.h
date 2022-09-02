#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_

#include <cstddef>
#include <array>

template <typename T, const std::size_t size>
void HeapSort(std::array<T, size>& array)
{
  auto MaxHeapfy = [&](auto&& lambda, const std::size_t& curr, const std::size_t& end) {
    std::size_t largest { curr };
    const std::size_t childL { curr * 2 + 1 };
    const std::size_t childR { curr * 2 + 2 };
    if( childL < end && array[childL] > array[largest] ) largest = childL;
    if( childR < end && array[childR] > array[largest] ) largest = childR;
    if( largest == curr ) return; // ? check if it is done
    std::swap(array[curr], array[largest]);
    lambda(lambda, largest, end); // ? recursion for [largest] sink down
  };

  // ? from subtree to upper node
  for(int i { (int)array.size() / 2 - 1 }; i >= 0; --i) MaxHeapfy(MaxHeapfy, i, array.size());

  for(int i { (int)array.size() - 1 }; i >= 0; --i) {
    std::swap(array[0], array[i]); // ? swap [0] & [curr last]
    MaxHeapfy(MaxHeapfy, 0, i);    // ? heapfy to make it always satisfy to max heap tree
  }
}

#endif // _HEAPSORT_H_