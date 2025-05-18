// Copyright 2021 NNTU-CS
#include "train.h"
#include <stdexcept>
#include "train.h"
#include <stdexcept>

Train::Train()
    : countOp(0),
    first(nullptr) {
}

void Train::addCar(bool light) {
    
    Car* node = new Car;
    node->light = light;
    if (first == nullptr) {
        node->next = node;
        node->prev = node;
        first = node;
    }
    else {
        Car* last = first->prev;
        last->next = node;
        node->prev = last;
        node->next = first;
        first->prev = node;
    }
}

int Train::getLength() {
    countOp = 0;
    
    for (int k = 1;; ++k) {
        Car* p = first;
        for (int i = 0; i < k; ++i) {
            p = p->next;
            ++countOp;
        }
        if (p == first) {
            return k;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}


