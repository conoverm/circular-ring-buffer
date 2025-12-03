# Ring Buffer Implementation

A circular ring buffer implementation with tests.

sources:
https://www.youtube.com/watch?v=iTJxxsIwGWk
https://www.youtube.com/watch?v=KyreJSKEagg
https://www.youtube.com/shorts/HqWTsRUgiLk

https://algocademy.com/blog/when-to-consider-using-a-circular-buffer-a-comprehensive-guide/

VS Code extensions for CMAKE

How to setup tests:
https://google.github.io/googletest/quickstart-cmake.html
https://learn.microsoft.com/en-us/visualstudio/test/how-to-use-google-test-for-cpp?view=visualstudio



## Building

```bash
mkdir build && cd build
cmake ..
// for macs: 
// cmake -DCMAKE_OSX_ARCHITECTURES=arm64 ..
make
```

## Running Tests

```bash
cd build
./tests
```

## Project Structure

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