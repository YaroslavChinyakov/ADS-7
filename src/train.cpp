// Copyright 2021 NNTU-CS
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
    if (!first) return 0;

    Car* p = first;
    do {
        if (p->light) {
            p->light = false;
        }
        p = p->next;
        ++countOp;
    } while (p != first);

    first->light = true;

    p = first->next;
    ++countOp;
    int length = 1;
    while (!p->light) {
        p = p->next;
        ++countOp;
        ++length;
    }

    first->light = false;

    return length;
}

int Train::getOpCount() {
    return countOp;
}
