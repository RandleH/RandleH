# RH_LIB

## Overview





## Functions & Members 

| Name                                          | Description |
| --------------------------------------------- | ----------- |
| **API C Language**                            |             |
| [rh_libc__malloc_init](#rh_libc__malloc_init) |             |
| [rh_libc__malloc]()                           |             |
| [rh_libc__calloc]()                           |             |
| [rh_libc__free]()                             |             |
| [rh_libc__malloc_deinit]()                    |             |
|                                               |             |
|                                               |             |
|                                               |             |







## Perspective Solution

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

  - `step 1`

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

  - `step 2`

    >Initialize the above parameters to `0` or `NULL`.
    >
    >Set the `rh_static__memory_free` as `__nbyte`.
    >
    >Set the `rh_static__memory_size` as `__nbyte.`
    >
    >Set the `rh_static__memory_ptr` as the `__global_allocated_ptr`.

  - `setp 3`

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

  

- **Complexity (Time | Space)**

  `O(1)` | `O(1)`











