## Circular Ring Buffer with Very Simple Encoding/Decoding demo

### Introduction

A circular ring buffer is the standard solution for handling streams of data. It's used in audio and video software, IoT data streams, tracking undo actions in editors, and logging. A problem that requires a data to be stored and processed in some manner, often for a long period of time, would benefit from a ring buffer.

### Features

The ring buffer is so-named because it is a standard array or vector managed by two indexes. One index tracks the front, which is data most recently added to the buffer. The other index tracks the back, data added last. Once the buffer is full, data is then overwritten by adding data to the front of the queue. The front index value will have changed given the size of the buffer and data added to it. It can also be the case that the buffer can be emptied before it is filled, changing the "tail" index. Generally, the buffer is filled up, then data can is processed and removed.

The core behavior of the ring buffer which makes it a unique structure is the wrap-around behavior. Once the buffer is filled, the oldest data is over-written, but not actually deleted. Marking data stale means incrementing the index that marks which space in the buffer to write to next. There's a function in this project "empty". You'll see it does not iterate over the array checking for null values. It checks if the head index is equal to the tail index. The data is still in the buffer, it's just considered stale. 

The point of a ring buffer is to manage memory as efficiently as possible. The data structure itself has constant complexity, 0(1). There are no loops, only adding data to array slots and incrementing or decrementing integers. The capacity of the buffer and individual array slots determines the space complexity. The space complexity can be very carefully managed.


### Time and Space Complexity
| Operation | Average Case | Worst Case |
|-----------|--------------|------------|
| push | O(1) | O(1) |
| Search | n/a | n/a |
| pop | O(1) | O(1) |

## File Structure

I took the lead from previous assignments, online guides, and VS Code extensions on the project structure. 

/include/<header_file.hpp> was probably the new idea. Also, putting all the code in the header file instead of a skeleton definition then the implementation details going into a .cpp file.

```
ringbuffer/
├── CMakeLists.txt          
├── include/
│   └── ringbuffer/
│       └── ring_buffer.hpp 
├── src/
│   └── ring_buffer.cpp     
├── app/
│   └── main.cpp            
├── tests/
│   └── test_ring_buffer.cpp 
└── build/                   
```
## Installation / Setup

This project uses cmake 3.10, just like the assignments.

```bash
git clone https://github.com/conoverm/circular-ring-buffer/
cd ringbuffer
```bash
mkdir build && cd build
cmake ..
// for Apple Silicon macs: 
// cmake -DCMAKE_OSX_ARCHITECTURES=arm64 ..
make

```

## Usage
```bash
./tests/test_ring_buffer.cpp
```

This will create a ring buffer of capacity two and run the demo. The "demo"—very sarcastic quotes—takes an integer and multiples it by 99. That's encoding. Decoding occurs after ringbuffer#pop and divides by 99.

```bash
./ringbuffer_app 2 55 77 88
```



## References

sources:
https://www.youtube.com/watch?v=iTJxxsIwGWk
https://www.youtube.com/watch?v=KyreJSKEagg
https://www.youtube.com/shorts/HqWTsRUgiLk

https://algocademy.com/blog/when-to-consider-using-a-circular-buffer-a-comprehensive-guide/

VS Code extensions for CMAKE

How to setup tests:
https://google.github.io/googletest/quickstart-cmake.html
https://learn.microsoft.com/en-us/visualstudio/test/how-to-use-google-test-for-cpp?view=visualstudio

## Optional Sections

### Future Improvements

On reading about ring buffers, I learned every tiny corner of the buffer could be modified and expanded. This buffer simply handles integers. But the Array slots themselves could be modified to handle data different types of data. The slots could have hard limits on the bits allowed in the slot. The buffer slots could then hold portions of data, requiring popping multiple slots for decoding and full item at a time. This would make sense for extremely large video files, for example.
