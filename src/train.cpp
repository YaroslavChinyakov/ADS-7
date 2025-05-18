// Copyright 2021 NNTU-CS
#include "train.h"
#include <stdexcept>

Train::Train() : countOp_(0), first_(nullptr) {}

void Train::addCar(bool light) {
    Car* node = new Car(light);
    if (!first_) {
        first_ = node;
    }
    else {
        Car* last = first_->prev;
        last->next = node;
        node->prev = last;
        node->next = first_;
        first_->prev = node;
    }
}

int Train::getLength() {
    countOp_ = 0;
    for (int k = 1;; ++k) {
        Car* p = first_;
        for (int i = 0; i < k; ++i) {
            p = p->next;
            ++countOp_;
        }
        if (p == first_) {
            return k;
        }
    }
}

int Train::getOpCount() const {
    return countOp_;
}

