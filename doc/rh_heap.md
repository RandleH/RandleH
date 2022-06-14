# RH_HEAP

## Overview

This library provides some useful  functions to convert a data stream into heap order. Users only need to provide compare functions, data source, length and size. It is universal and not constraint by the data type. 

Function conforms to `ISO/IEC 9899:1990 (``ISO C90'')`.



## Demonstration

### Heapify

- **Step 1**: Create your own comparation method

  For example, if you want to compare two `int` value, you can reference the following code.

  ```C++
  static int compar_int_less(const void *a, const void *b){
      return (*(int*)a) < (*(int*)b);
  }
  
  static int compar_int_greater(const void *a, const void *b){
      return (*(int*)a) > (*(int*)b);
  }
  ```

   Appeartly, the function`compar_int_less` is equivalent to the std template `std::less<int>()`. So is `compar_int_greater`.

  

  Noting that the method function has to be consent to the following form:

  ```C++
  int your_compare_func (const void *, const void *);
  ```

  

- **Step 2**:  Figure out how many elements in your array. It is NOT the memory size.

  That is simply equivalent to `xxxx.size()` in C++.

  For an array, you may use the following way to find out size.

  ```C
  size_t size = sizeof(array)/sizeof(*array);
  ```

  

- **Step 3**: Figure out how many bytes does it count for a single element.

  For example, suppose we have an `int` array, the single element size is just the size of `int`.

  You  dmay use the following way to find out size.

  ```C
  size_t size = sizeof(int);
  ```

   

- **Step 4**: Fill out the function.

  ```C
  static int compar_int_less(const void *a, const void *b){
      return (*(int*)a) < (*(int*)b);
  }
  
  int array[]  = { 4,5,8,2,4,9,7,1,-3, 0};
  size_t nel   = sizeof(array)/sizeof(*array);
  size_t width = sizeof(int);
  
  // Call the function (Both works)
  rh_heap__heapify( &array[0], nel, width, compar_int_less);
  rh_heap__heapify( &array[0], sizeof(array)/sizeof(*array), sizeof(int), compar_int_less);
  
  // Now `array` is in heap order.
  
  // less    -> max-heap
  // greater -> min-heap
  ```

  







## Function & Method



