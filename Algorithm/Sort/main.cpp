#include "QuickSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "InsertSort.h"
#include "SelectSort.h"
#include "BubbleSort.h"

#include <iostream>
#include <array>
#include <windows.h>

template<typename T, const std::size_t size>
void Print(const std::array<T, size>& array) 
{
  for(auto& c : array) std::cout << c;
  std::cout << std::endl;
}

int main(void) 
{
  constexpr std::size_t size { 62 * 5 + 1 };

  std::array<char, size> array { "POgastyu13IUf28m9DSdKJHGiop7vb0nF6YT4wCXZerAREWQLzxcMjklqNBVh5POgastyu13IUf28m9DSdKJHGiop7vb0nF6YT4wCXZerAREWQLzxcMjklqNBVh5POgastyu13IUf28m9DSdKJHGiop7vb0nF6YT4wCXZerAREWQLzxcMjklqNBVh5POgastyu13IUf28m9DSdKJHGiop7vb0nF6YT4wCXZerAREWQLzxcMjklqNBVh5POgastyu13IUf28m9DSdKJHGiop7vb0nF6YT4wCXZerAREWQLzxcMjklqNBVh5" } ;

  Print<char, size>(array);

LARGE_INTEGER begin, end;

QueryPerformanceCounter(&begin);

  // QuickSort<char, size>(array, 0, array.size() - 1); // ? 480 ~ 520

  // MergeSort<char, size>(array, 0, array.size() - 1); // ? 490 ~ 900

  // HeapSort<char, size>(array); // ? 820 ~ 1500

  // InsertSort<char, size>(array); // ? 2400 ~ 5700

  // SelectSort<char, size>(array); // ? 3800 ~ 6200

  // BubbleSort<char, size>(array); // ? 6500 ~ 10000

QueryPerformanceCounter(&end);

  Print<char, size>(array);

  std::cout << "ticks: " << end.QuadPart - begin.QuadPart << std::endl; 

  return 0;
}