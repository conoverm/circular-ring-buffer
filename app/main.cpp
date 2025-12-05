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


void print_buffer_state(RingBuffer<int>& rb) {
    cout << "  [Buffer state: size=" << rb.size() 
         << "/" << rb.capacity() 
         << ", " << (rb.full() ? "full" : "not full") << "]" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Use: \"ring buffer capacity\" \"first int\" \"second int\" etc..."<< endl;
        cout << "Example:  3 11 22 33 44 50" << endl;
        return 1;
    }
    
    int buffer_capacity = atoi(argv[1]);
    if (buffer_capacity < 1) {
        cout << "buffer must be greater than 1 and first arg" << endl;
        return 1;
    }
    
    int num_values = argc - 2;
    RingBuffer<int> rb(buffer_capacity);
    
    cout << "Ring Buffer faux stream" << endl;
    cout << "Buffer capacity: " << rb.capacity() << endl;
    cout << "Number of values passed to ring buffer: " << num_values << endl;
    cout << endl;
    
    cout << "Processing..." << endl;
    
    // "i[2]" is the first integer passed
    // i[0] = "./ringbuffer_app"
    // i[1] = ring buffer capacity
    for (int i = 2; i < argc; i++) {
        int value = atoi(argv[i]);
        int encoded = encode(value);
        
        if (rb.full()) {
            cout << "Buffer full! Popping and decoding" << endl;
            int popped_encoded = rb.pop();
            int decoded = decode(popped_encoded);
            cout << "decoded: " << decoded << endl;
            print_buffer_state(rb);
        }
        
        rb.push(encoded);
        cout << "popped, at least once space in buffer available" << endl;
        cout << "value, encoded: " << value <<","<< encoded << endl;
        print_buffer_state(rb);
        cout << endl;
    }
    
    if (!rb.empty()) {
        cout << "Processing the rest of the buffer..." << endl;
        
        while (!rb.empty()) {
            int encoded = rb.pop();
            int decoded = decode(encoded);
            cout << "  << Popped and decoded: " << decoded << " (was: " << encoded << ")" << endl;
            print_buffer_state(rb);
        }
    }
    
    cout << endl;
    cout << "no data left in \"stream\"" << endl;
    cout << "Buffer empty? " << (rb.empty() ? "yes" : "no") << endl;
    
    return 0;
}