// quicksort.cpp

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>

// Helper functions
void test_randomize(int *, int);
void randomize(int *, int);
void print_array(int *, int);
void swap_elements(int *, int, int);

// Main functions
int hoare_partition(int *, int, int);
void quicksort(int *, int, int);

//We will be taking two command line arguments.
//The first command line argument is the array size (N) to work with.
//The second command line argument is the name of the file to append the results to.
int main(int argc, char * argv[]) {
  const int SIZE = atoi(argv[1]);
  int * arr = new int[SIZE]; 
  std::ofstream myfile;

  randomize(arr, SIZE);
  std::cout << "BEGIN QUICKSORT" << std::endl;
  std::cout << "ARRAY SIZE: " << SIZE << std::endl;

  //Start the timer
  auto t_start = std::chrono::high_resolution_clock::now();

  quicksort(arr, 0, SIZE-1);

  std::cout << "FINISHED QUICKSORT" << std::endl;

  //End the timer
  auto t_end = std::chrono::high_resolution_clock::now();

  // UNCOMMENT ONLY FOR TESTING. OTHERWISE NOT RECOMMENDED TO PRINT VALUES WHERE ARRAY SIZE IS LARGE.
  //print_array(arr, SIZE);
  std::cout << "ELAPSED TIME: " 
            << std::chrono::duration<double, std::milli>(t_end-t_start).count()
            << " ms\n";

  myfile.open(argv[2], std::fstream::out | std::fstream::app);
  myfile << std::chrono::duration<double, std::milli>(t_end-t_start).count() << '\n';
  return 0;
}

// The quicksort implementation as described by Levitin.
// INPUT: array of integers and the INDEX positions of the leftmost and rightmost elements
// OUTPUT: a sorted array thanks to quicksort
void quicksort(int * arr, int l, int r) {
  if(l < r) {
    //S is our split position retrieved from hoare partinioning our array
    int s = hoare_partition(arr, l, r);
 
    //Run quicksort on the left and right side of the split positions
    quicksort(arr, l, s-1);
    quicksort(arr, s+1, r);
  }
}

// Helper function hoare partition will partition our subarray
// and return the split position. It will also ensure that left and
// right values of the split position is smaller and larger respectively.
int hoare_partition(int * arr, int l, int r) {
  int p, i, j;
  p = arr[l];
  i = l;
  j = r + 1;
  while(i < j) {
    do {
      ++i;
    } while(arr[i] < p);
    do {
      --j;
    } while(arr[j] > p);
    swap_elements(arr, i, j);
  }
  swap_elements(arr, i, j);
  swap_elements(arr, l, j);
  return j;
}

// Utility function to fill array with random integers
void randomize(int * arr, int length) {
  for(int i = 0; i < length; ++i) {
    arr[i] = rand() % length;
  }
}

// Utility function to swap two elements in an array of integers
void swap_elements(int * arr, int indexA, int indexB) {
  int temp = arr[indexA];
  arr[indexA] = arr[indexB];
  arr[indexB] = temp;
}


// Utility function to print an array
void print_array(int * arr, int length) {
  for(int i = 0; i < length; ++i) {
    std::cout << arr[i] << std::endl;
  }
}
