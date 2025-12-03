using namespace std;

template<typename T>
class RingBuffer {
public:
    RingBuffer(unsigned int capacity){
        // back of queue
        // either way to name these will be confusing
        // either name this head while it acts as the back
        // and output will be front first
        // [x1, x2, ... ... ...]
        // or name it tail and output will be the same

        // head is the data that will be popped next
        head_ = 0;
        
        // front of queue. 
        // Ring Buffer is a FIFO queue
        // tail is data that will be popped last
        tail_ = 0;
        size_ = 0;
        buffer_ = new T[capacity];
        capacity_ = capacity;
    };
    ~RingBuffer(){
        delete[] buffer_;
    };


    bool push(T item){
        // assume head index is managed correctly
        buffer_[head_] = item;

        // set new head index
        // eg:
        // 1+1 % 5 = 2
        // will just reset to zero soon as modulus is hit
        head_ = (head_ + 1) % capacity_;

        if (size_ == capacity_) {
        // the trickiest part.
        // This is the wrap-around behavior.
        // The buffer is full. When that happens the buffer needs to overwrite old data with new data.
        // Overwriting oldest data was handled on the line above with the modulus.
        // Now, if more data is added to the buffer THE NEXT READ must be THE OLDEST data.
        // At this moment, we know the buffer is full. 
        // So the oldest data is whatever is next in the buffer
        // right after brand new data was added to it.
            tail_ = (tail_ + 1) % capacity_;
        } else {
            // Buffer wasn't full
            size_++;
        }

        // a thing was set
        return true;
    };
    

    T pop(){
        if (empty()) {
            // self explanatory
            // return an empty item
            return T();
        }

        T ret = buffer_[tail_];
        tail_ = (tail_ + 1) % capacity_;
        size_--;

        return ret;
    };
    

    // backwards names. Head of queue is first out so this means
    // GET the closest to the item getting out
    T front(){
        if (empty()) {
            return false;
        }
        return buffer_[tail_];
    };
    
    // GET the last data added to the queue
    T back(){
        if (empty()) {
            return false;
        }
        return buffer_[head_];
    };
    
    bool empty(){
        return size_ == 0;
    };
    
    unsigned int size(){
        // cout << "size_: " << size_ << endl;
        return size_;
    };

    unsigned int capacity(){
        // cout << "capacity_: " << capacity_ << endl;
        return capacity_;
    };

    void clear(){
        delete[] buffer_;
        buffer_ = new T[capacity_];
    };

    // utility mostly for testing. 
    T at(int position) {
        return buffer_[position];
    }

    bool full() {
        return size() == capacity();
    }

private:
    T* buffer_;
    // total number of slots
    unsigned int capacity_;
    // front and rear of buffer
    unsigned int head_;      
    unsigned int tail_;

    // total items in the buffer at any moment
    unsigned int size_;
};
