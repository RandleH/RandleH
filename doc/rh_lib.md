# RH_LIB

## Overview

This library contains lower-level interface functions, aiming to provide useful and easy migratable methods upon system memory allocation, common bit operation, memory operation and sorting algorithms. This library contains the following files.

- [rh_lib.c](../src/rh_lib.c)
- [rh_lib.cc](../src/rh_lib.cc)
- [rh_lib.h](../inc/rh_lib.h)
- [rh_lib.hpp](../inc/rh_lib.hpp)



## Functions & Members 

| Name                                              | Description                                          |
| ------------------------------------------------- | ---------------------------------------------------- |
| **API in C**                                      |                                                      |
| [rh_libc__malloc_init](#rh_libc__malloc_init)     | Initialize the dynamic memory allocation program.    |
| [rh_libc__malloc](#rh_libc__malloc)               | Allocate memory.                                     |
| [rh_libc__calloc](#rh_libc__calloc)               | Allocate memory and reset values to `0x00`.          |
| [rh_libc__free](#rh_libc__free)                   | Deallocate the memory allocation pointed to by `ptr` |
| [rh_libc__malloc_deinit](#rh_libc__malloc_deinit) | Deinitialize the dynamic memory allocation program.  |
| [rh_libc__bin_itoa]                               |                                                      |
| [rh_libc__bin_ltoa]                               |                                                      |
| [rh_libc__bin_ftoa]                               |                                                      |
| [rh_libc__insert_sort]                            |                                                      |
| [rh_libc__shell_sort]                             |                                                      |
| **API in C++**                                    |                                                      |
|                                                   |                                                      |







## Function Manual Reference

---

### `rh_libc__malloc_init` 

<div id="rh_libc__malloc_init"></div>

- **Interface**

  ```C
  void*    rh_libc__malloc_init(void* __global_allocated_ptr, size_t __nbyte);
  ```

  | Params                   | Description                                   |
  | ------------------------ | --------------------------------------------- |
  | `__global_allocated_ptr` | The pointer to your allocation memory address |
  | `__nbyte`                | The size of the memory counted as bytes.      |

  

- **Implimentation**

  - **step 1**

    > There are six static variables maintaining the entire dynamic memory allocation process.
    >
    > `rh_static__memory_ptr` is the top address of your virtual allocation memory.
    >
    > `rh_static__memory_size` is the size of the memory counted as bytes.
    >
    > `rh_static__memory_free` denotes how many bytes are free to allocate.
    >
    > `rh_static__memory_allocated` denotes how many bytes have been allocated.
    >
    > `rh_static__memory_infoptr` is the top address of the information that includes the history allocation.
    >
    > `rh_static__memory_infocnt` denotes how many information blocks have been generated.

  - **step 2**

    >Initialize the above parameters to `0` or `NULL`.
    >
    >Set the `rh_static__memory_free` as `__nbyte`.
    >
    >Set the `rh_static__memory_size` as `__nbyte.`
    >
    >Set the `rh_static__memory_ptr` as the `__global_allocated_ptr`.

  - **step 3**

    > Set all the memory to `0x00` .
    >
    > Return the pointer given by user.

    

- **Complexity (Time | Space)**

  `O(1)` | `O(1)`

  

- **Return**

  If successful, return the pointer same as the given one.

  If there is an error, return `NULL`.



---

### `rh_libc__malloc` 

<div id="rh_libc__malloc"></div>

- **Interface**

  ```C
  void*    rh_libc__malloc(size_t size)
  ```

  | Params | Description                     |
  | ------ | ------------------------------- |
  | `size` | The bytes of the require memory |

- **Implimentation**

  - **step 1**

    > There are two strategies to search a valid dynamic memory ie.( `Best fit` and `Found then return` ). 
    >
    > In this function, it used `best fit` to maximumly avoid memory redundancy in the system. It wil first call `rh_libc__sbrk` to search which free memory pool best fits the requirement.
    > $$
    > \text{Best fit} := \min \bigg[ \text{byte(free pool)}-\text{byte(desire)} \bigg]
    > $$
    > If success, then `rh_libc__sbrk` will return a index that indicates the address of virtual heap array. Starting that index, there exists a free memory pool that best fits the requirement.
    >
    > If there is no memory pool that can meet the requirement, `rh_libc__sbrk` wil return `LONG_MAX`. If so, return `NULL`.
    >
    > For the impliment of `rh_libc__sbrk`, see [this](#rh_libc__sbrk).

  - **step 2**

    >Now introduce the memory block information. Given a pointer to something allocated by our malloc, we have no idea what size block is associated with it. A common trick to work around this is to store meta-information about a memory region in some space that we squirrel away just below the pointer that we return. Here is the structure of memory block information.
    >
    >```C
    >typedef struct MallocInfo_t{
    >size_t                   byte; // Block size
    >size_t                   idx;  // Distance from the heap top.
    >}MallocInfo_t;
    >```
    >
    >The meta-memory stored at the end of the heap array. For example, here is the preview of our heap memory.
    >
    >|  ✅   |  ☑️   |  ✅   |  ☑️   |  ☑️   |  ✅   |  ☑️   |  ☑️   |  ☑️   |  ☑️   |  ✅   | ...  |   ✅   |    ℹ️    |    ℹ️    |    ℹ️    |
    >| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | ---- | :---: | :-----: | :-----: | :-----: |
    >| `0`  | `1`  | `2`  | `3`  | `4`  | `5`  | `6`  | `7`  | `8`  | `9`  | `10` |      | `N-4` |  `N-3`  |  `N-2`  |  `N-1`  |
    >|      |  #   |      |  #   |  #   |      |  #   |  #   |  #   |  #   |      | ...  |       | `(1,1)` | `(3,2)` | `(6,4)` |
    >
    >☑️ - Memory that has been allocated, and it only can be access by user.
    >
    >✅ - Memory that was free to allocate.
    >
    >ℹ️ - Meta-memory block information.
    >
    >Noting that `(p,q)` means there are `q` bytes allocated starting from index `p`. The total heap size is `N` ( assumming the meta-memory unit takes 1 byte each, that is not true actually ).
    >
    >
    >
    >The meta-memory block was sorted by its member `idx`. That is very convenient and useful when calculating free memory size by compute the difference between neighbor.
    >
    > 
    >
    >From the table, we can conclude that 
    >
    >| Static variable name          | Value                         |
    >| ----------------------------- | ----------------------------- |
    >| `rh_static__memory_ptr`       | `(non-NULL)`                  |
    >| `rh_static__memory_size`      | `N`                           |
    >| `rh_static__memory_free`      | `N-7`                         |
    >| `rh_static__memory_allocated` | `7`                           |
    >| `rh_static__memory_infoptr`   | `rh_static__memory_ptr + N-3` |
    >| `rh_static__memory_infocnt`   | `3`                           |
    >
    > 
    
  - **step 3**

    >Insert meta information, we need to keep the meta-information sorted by its member `idx`, therefore it's reasonable to use **binary search** to insert an element.
    >
    >Here we have to use `memmove` since there exists the memory overlapping problem. After this operation, move the `rh_static__memory_infoptr` forward by one unit.
    >
    > 
    >
    >Adjust the  `rh_static__memory_free`  and `rh_static__memory_allocated` value.



- **Complexity (Time | Space)**

  `O(n)` | `O(1)`

   

- **Return**

  If successful, return the dynamic memory address.

  If there is an error, return `NULL`.



---

### `rh_libc__calloc` 

<div id="rh_libc__calloc"></div>

- **Interface**

  ```C
  void*    rh_libc__calloc(size_t count, size_t __nbyte);
  ```

  | Params    | Description           |
  | --------- | --------------------- |
  | `count`   | Number of elements    |
  | `__nbyte` | Size of each elements |

- **Implimentation**

  - **step 1**

    > Call the `rh_libc_malloc` first and set all elements zero.

    

- **Complexity (Time | Space)**

  `O(n)` | `O(1)`

   

- **Return**

  If successful, return the dynamic memory address.

  If there is an error, return `NULL`.



---

### `rh_libc__free` 

<div id="rh_libc__free"></div>

- **Interface**

  ```C
  void     rh_libc__free( void* ptr);
  ```

  | Params | Description                                   |
  | ------ | --------------------------------------------- |
  | `ptr`  | The pointer to your allocation memory address |

  

- **Implimentation**

  - **step 1**

    > First is to locate which meta-information this pointer correspond to. By calculating the difference from top of the heap, we get the index. Index, to some extend, is the offset address with respect to the top pointer.
    >
    > Using the **binary search** method, locate its meta-information. 
    >
    > If it was not found, abort the program. 

  - **step 2**

    >Remove the corresponding meta-information.
    >
    >Move the `rh_static__memory_infoptr` backward by one unit.

  - **setp 3**

    > Adjust the  `rh_static__memory_free`  and `rh_static__memory_allocated` value.

    

- **Complexity (Time | Space)**

  `O(logn)` | `O(1)`

  

- **Return**

  No return.



---

### `rh_libc__malloc_deinit` 

<div id="rh_libc__malloc_deinit"></div>

- **Interface**

  ```C
  void*    rh_libc__malloc_deinit(void);
  ```

  

- **Implimentation**

  - **step 1**

    > Set the heap array to zero.
    >
    > Reset all the static value that is `rh_static__memory_xxxx` to zero.

  - **step 2**

    >Release the heap array pointer and return it.

    

- **Complexity (Time | Space)**

  `O(1)` | `O(1)`

  

- **Return**

  Return the heap array pointer.



