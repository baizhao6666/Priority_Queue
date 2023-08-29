#include <iostream>
#include "priorityqueue.h"

int main() {
//    priorityqueue<string> bst;
//    bst.enqueue("Dolores", 5);
//    bst.enqueue("Bernard", 4);
//    bst.enqueue("Ford", 2);
//    bst.enqueue("Arnold", 8);
//    bst.enqueue("Jasmine", 6);
//    bst.enqueue("William", 8);
//    bst.enqueue("Teddy", 8);
//    bst.enqueue("Apple", 7);
//    bst.enqueue("Cat", 10);
//    bst.enqueue("Curry", 2);
//    bst.enqueue("James", 2);
//    bst.enqueue("Harden", 4);
////    cout << "before copy: " << endl;
////    cout << bst.toString();
//    priorityqueue<string> bstCopy;
////    cout << "after copy: " << endl;
//    bstCopy = bst;
////    bst.dequeue();
//    bst.enqueue("Carlos", 11);
////    cout << bstCopy.toString();
////    bst.begin();
////    int priority = 0;
////    string value;
////    while (bst.next(value, priority)) {
////        cout << priority << " value: " << value << endl;
////    }
////    cout << priority << " value: " << value << endl;
//
////    if (bst == bstCopy) {
////        cout << "they are equal" << endl;
////    } else {
////        cout << "they are not equal" << endl;
////    }
//
//    while (bst.Size() != 0) {
//        cout << bst.peek() << endl;
//        bst.dequeue();
//    }

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

    myQueue.begin();
    while (myQueue.next(value, priority)) {
        cout << priority << " value: " << value << endl;
    }
    cout << priority << " value: " << value << endl;

    cout << myQueue.next(value, priority) << endl;

    return 0;
}
