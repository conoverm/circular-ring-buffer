#include <gtest/gtest.h>
#include "ringbuffer/ring_buffer.hpp"


class RingBufferTest : public ::testing::Test {
// protected:
//     void SetUp() override {

//     }

//     void TearDown() override {

//     }
};


TEST_F(RingBufferTest, Construction) {
    RingBuffer<int> rb(5);
    EXPECT_EQ(rb.capacity(), 5);
    EXPECT_EQ(rb.size(), 0);
    EXPECT_TRUE(rb.empty());
    EXPECT_FALSE(rb.full());
}


TEST_F(RingBufferTest, SizeTest) {
    RingBuffer<int> rb(5);
    int ten = 10;
    int twenty = 20;
    EXPECT_EQ(rb.size(), 0);
    
    rb.push(ten);
    EXPECT_EQ(rb.size(), 1);
    
    rb.push(twenty);
    EXPECT_EQ(rb.size(), 2);
    
    rb.pop();
    EXPECT_EQ(rb.size(), 1);
}


TEST_F(RingBufferTest, Push) {
    int one = 1;
    RingBuffer<int> rb(3);
    bool success = rb.push(one);
    EXPECT_TRUE(success);
    EXPECT_EQ(rb.size(), 1);
    EXPECT_FALSE(rb.empty());
}

TEST_F(RingBufferTest, Pop) {
    int one = 1;
    RingBuffer<int> rb(3);

    int zero = 0;
    // test buffer empty pop
    int fail = rb.pop();
    EXPECT_EQ(fail, zero);
    EXPECT_TRUE(rb.empty());

    rb.push(one);

    int success = rb.pop();
    EXPECT_EQ(success, one);
    EXPECT_TRUE(rb.empty());
}

// Test circular behavior
TEST_F(RingBufferTest, CircularBehavior) {
    int one = 1;
    int two = 2;
    int three = 3;
    RingBuffer<int> rb(3);
    rb.push(one);
    rb.push(two);
    rb.push(three);
    EXPECT_TRUE(rb.full());
    
    // now wraparound
    int four = 4;
    rb.push(four);
    EXPECT_TRUE(rb.full());
    EXPECT_EQ(rb.at(0), four);

}

TEST_F(RingBufferTest, Full){
    RingBuffer<int> rb(1);
    EXPECT_TRUE(rb.empty());

    rb.push(66);

    EXPECT_TRUE(rb.full());

    rb.pop();
    
    bool sz = rb.full();
    // cout << sz << "---sz" << endl;

    EXPECT_TRUE(rb.empty());
    EXPECT_FALSE(rb.full());
};

TEST_F(RingBufferTest, Capacity){
    RingBuffer<int> rb(3);
    rb.push(8);
    rb.push(11);
    rb.push(7);
    EXPECT_EQ(rb.at(0), 8);
    rb.push(1111);
    // cout << rb.at(3) << endl;
    EXPECT_EQ(rb.at(2), 7);
    EXPECT_EQ(rb.at(4), 0);
    EXPECT_EQ(rb.at(0), 1111);
};


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
