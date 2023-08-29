/**------------------------------------------
Test cases for Project 5: Priority Queue
Course: CS 251, Spring 2023, UIC
System: CLion on MacOs
Author: Baizhao Zhao
-------------------------------------------*/
/// @file tests.cpp
/// @date March 17, 2023

/// 
/// TODO

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

// Catch 1.0 Framework Testing
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "priorityqueue.h"

using namespace std;

TEST_CASE("(0) no tests") 
{
    REQUIRE(true);
}

/**
 * test case for default constructor
 */
TEST_CASE("constructor") {
    priorityqueue<string> queue;
    REQUIRE(queue.Size() == 0);
    REQUIRE(queue.getRoot() == nullptr);
    REQUIRE(queue.peek() == "");
}

/**
 * test case for operator = overload
 */
TEST_CASE("operator=") {
    priorityqueue<string> myQueue;
    myQueue.enqueue("Apple", 7);

    priorityqueue<string> queueCopy;
    queueCopy = myQueue;
    REQUIRE(&queueCopy != &myQueue);
    REQUIRE(queueCopy.Size() == myQueue.Size());
    REQUIRE(queueCopy.getRoot() != nullptr);
    REQUIRE(queueCopy.peek() == myQueue.peek());

    queueCopy.dequeue();
    myQueue = queueCopy;
    REQUIRE(myQueue.Size() == queueCopy.Size());
    REQUIRE(myQueue.getRoot() == nullptr);
    REQUIRE(myQueue.peek() == "");
}

/**
 * test cases for clear() function
 */
TEST_CASE("clear") {
    priorityqueue<string> myQueue;
    myQueue.enqueue("Apple", 5);
    REQUIRE(myQueue.Size() == 1);
    myQueue.clear();
    REQUIRE(myQueue.Size() == 0);
    REQUIRE(myQueue.getRoot() == nullptr);
    REQUIRE(myQueue.peek() == "");

    myQueue.enqueue("Pine", 6);
    myQueue.enqueue("Banana", 4);
    myQueue.enqueue("Water", 9);
    myQueue.enqueue("Pineapple", 4);
    REQUIRE(myQueue.Size() == 4);
    myQueue.clear();
    REQUIRE(myQueue.Size() == 0);
    REQUIRE(myQueue.getRoot() == nullptr);
    REQUIRE(myQueue.peek() == "");
}

/**
 * test cases for enqueue() function
 */
TEST_CASE("enqueue") {
    priorityqueue<string> myQueue;
    REQUIRE(myQueue.Size() == 0);
    myQueue.enqueue("Apple", 6);
    REQUIRE(myQueue.Size() == 1);
    myQueue.enqueue("Pear", 4);
    REQUIRE(myQueue.Size() == 2);
    myQueue.enqueue("Banana", 8);
    REQUIRE(myQueue.Size() == 3);
    myQueue.enqueue("Watermelon", 4);
    REQUIRE(myQueue.Size() == 4);
    myQueue.enqueue("Melon", 6);
    REQUIRE(myQueue.Size() == 5);
    REQUIRE(myQueue.getRoot() != nullptr);
    REQUIRE(myQueue.peek() == "Pear");

    myQueue.clear();
    REQUIRE(myQueue.Size() == 0);
    myQueue.enqueue("Peach", 6);
    REQUIRE(myQueue.Size() == 1);
    REQUIRE(myQueue.getRoot() != nullptr);
    REQUIRE(myQueue.peek() == "Peach");
}

/**
 * test cases for dequeue() function
 */
TEST_CASE("dequeue") {
    priorityqueue<char> myQueue;
    myQueue.enqueue('G', 8);
    myQueue.enqueue('F', 6);
    myQueue.enqueue('K', 11);
    myQueue.enqueue('g', 8);
    myQueue.enqueue('f',6);
    myQueue.enqueue('L', 12);
    REQUIRE(myQueue.Size() == 6);

    myQueue.dequeue();
    REQUIRE(myQueue.Size() == 5);
    REQUIRE(myQueue.dequeue() == 'f');
    REQUIRE(myQueue.Size() == 4);
    myQueue.dequeue();
    REQUIRE(myQueue.Size() == 3);
    REQUIRE(myQueue.dequeue() == 'g');
    REQUIRE(myQueue.Size() == 2);
    myQueue.dequeue();
    myQueue.dequeue();
    REQUIRE(myQueue.Size() == 0);
    REQUIRE(myQueue.dequeue() == 0);
}

/**
 * test cases for Size() function
 */
TEST_CASE("Size") {
    priorityqueue<string> myQueue;
    REQUIRE(myQueue.Size() == 0);
    myQueue.enqueue("Dolores", 5);
    REQUIRE(myQueue.Size() == 1);
    myQueue.enqueue("Bernard", 4);
    REQUIRE(myQueue.Size() == 2);
    myQueue.enqueue("Ford", 2);
    REQUIRE(myQueue.Size() == 3);
    myQueue.dequeue();
    REQUIRE(myQueue.Size() == 2);
    myQueue.enqueue("Arnold", 8);
    REQUIRE(myQueue.Size() == 3);
    myQueue.enqueue("Jasmine", 6);
    REQUIRE(myQueue.Size() == 4);
    myQueue.dequeue();
    REQUIRE(myQueue.Size() == 3);
    myQueue.enqueue("William", 8);
    REQUIRE(myQueue.Size() == 4);
    myQueue.dequeue();
    myQueue.dequeue();
    REQUIRE(myQueue.Size() == 2);
    myQueue.dequeue();
    REQUIRE(myQueue.Size() == 1);
}

/**
 * test cases for begin() and next() functions
 */
TEST_CASE("begin_and_next") {
    priorityqueue<string> myQueue;
    myQueue.enqueue("Dolores", 5);
    myQueue.enqueue("Bernard", 4);
    myQueue.enqueue("Ford", 2);
    myQueue.enqueue("Arnold", 8);
    myQueue.enqueue("William", 8);
    myQueue.enqueue("Teddy", 8);
    myQueue.enqueue("Curry", 2);
    myQueue.enqueue("James", 2);
    myQueue.enqueue("Harden", 4);

    int priority;
    string value;
    int cnt = 0;
    myQueue.begin();
    while (myQueue.next(value, priority)) {
        cnt++;
    }
    cnt++;
    REQUIRE(cnt == 9);

    myQueue.begin();
    myQueue.next(value, priority);
    REQUIRE(priority == 2);
    REQUIRE(value == "Ford");
    myQueue.next(value, priority);
    myQueue.next(value, priority);
    myQueue.next(value, priority);
    myQueue.next(value, priority);
    REQUIRE(priority == 4);
    REQUIRE(value == "Harden");
    myQueue.next(value, priority);
    myQueue.next(value, priority);
    REQUIRE(priority == 8);
    REQUIRE(value == "Arnold");
    myQueue.next(value, priority);
    myQueue.next(value, priority);
    REQUIRE(priority == 8);
    REQUIRE(value == "Teddy");
    REQUIRE(myQueue.next(value, priority) == false);
}

/**
 * test cases for peek() function
 */
TEST_CASE("peek") {
    priorityqueue<string> myQueue;
    REQUIRE(myQueue.peek() == "");
    myQueue.enqueue("Dolores", 5);
    REQUIRE(myQueue.peek() == "Dolores");
    myQueue.enqueue("Bernard", 4);
    REQUIRE(myQueue.peek() == "Bernard");
    myQueue.enqueue("Ford", 2);
    REQUIRE(myQueue.peek() == "Ford");
    myQueue.enqueue("Arnold", 8);
    REQUIRE(myQueue.peek() == "Ford");

    myQueue.dequeue();
    REQUIRE(myQueue.peek() == "Bernard");
    myQueue.dequeue();
    myQueue.dequeue();
    REQUIRE(myQueue.peek() == "Arnold");
    myQueue.dequeue();
    REQUIRE(myQueue.peek() == "");
}

/**
 * test cases for operator== overload
 */
TEST_CASE("operator==") {
    priorityqueue<string> myQueue;
    myQueue.enqueue("Dolores", 5);
    myQueue.enqueue("Bernard", 4);
    myQueue.enqueue("Ford", 2);
    myQueue.enqueue("Arnold", 8);
    myQueue.enqueue("William", 8);

    priorityqueue<string> queueCopy;
    queueCopy = myQueue;
    REQUIRE(myQueue == queueCopy);
    myQueue.enqueue("Cat", 10);
    REQUIRE(!(myQueue == queueCopy));
    queueCopy = myQueue;
    REQUIRE(myQueue == queueCopy);
    myQueue.enqueue("Harden", 4);
    REQUIRE(!(myQueue == queueCopy));

}

/**
 * test cases for getRoot() function
 */
TEST_CASE("getRoot") {
    priorityqueue<string> myQueue;
    REQUIRE(myQueue.getRoot() == nullptr);
    myQueue.enqueue("Dolores", 5);
    REQUIRE(myQueue.getRoot() != nullptr);

    myQueue.dequeue();
    REQUIRE(myQueue.getRoot() == nullptr);
    myQueue.dequeue();
    REQUIRE(myQueue.getRoot() == nullptr);
}