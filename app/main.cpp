#include <iostream>
#include "ringbuffer/ring_buffer.hpp"

using namespace std;

// demo encoding. This isn't doing anything interesting
int encode(int value) {
    return value * 99;
}

int decode(int encoded_value) {
    return encoded_value / 99;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Provide a series of integers seperated by a space. eg: 7 928 12 847" << endl;
        return 1;
    }
    
    int num_values = argc - 1;
    RingBuffer<int> rb(num_values);
    
    cout << "Ring Buffer demo: " << endl;
    cout << "Buffer capacity: " << rb.capacity() << endl;
    cout << endl;
    
    cout << "encoding and filling ring buffer:" << endl;
    for (int i = 1; i < argc; i++) {
        int value = atoi(argv[i]);
        int encoded = encode(value);
        rb.push(encoded);
        cout << "Input: " << value << ".... Encoded: " << encoded << endl;
    }
    
    cout << endl;
    cout << "Buffer size: " << rb.size() << "/" << rb.capacity() << endl;
    cout << "Buffer full: " << (rb.full() ? "yes" : "no") << endl;
    cout << endl;
    
    cout << "Retrieving and decoding values:" << endl;
    while (!rb.empty()) {
        int encoded = rb.pop();
        int decoded = decode(encoded);
        cout << "Popped from buffer: " << encoded << ".... Decoded: " << decoded << endl;
    }
    
    cout << endl;
    cout << "Buffer empty: " << (rb.empty() ? "yes" : "no") << endl;
    
    return 0;
}