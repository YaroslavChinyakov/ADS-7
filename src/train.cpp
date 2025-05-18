// Copyright 2021 NNTU-CS
#include "train.h"
#include <stdexcept>
#include "train.h"

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

    bool allOff = true, allOn = true;
    const Car* detect = first;
    do {
        if (detect->light) allOff = false;
        else             allOn = false;
        detect = detect->next;
    } while (detect != first);

    if (allOff) {
        Car* p = first;
        do {
            if (p->light) p->light = false;
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

    if (allOn) {
        int nCars = 1;
        Car* cur = first->next;
        while (cur != first) {
            ++nCars;
            cur = cur->next;
        }
        Car* p = first;
        for (int k = 1; k <= nCars; ++k) {
            for (int i = 0; i < k; ++i) {
                p = p->next;
                ++countOp;
            }
        }
        for (int k = 1; k <= nCars; ++k) {
            for (int i = 0; i < k; ++i) {
                p = p->next;
                ++countOp;
            }
        }
        return nCars;
    }

    {
        Car* p = first;
        do {
            if (p->light) p->light = false;
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
}

int Train::getOpCount() {
    return countOp;
}
