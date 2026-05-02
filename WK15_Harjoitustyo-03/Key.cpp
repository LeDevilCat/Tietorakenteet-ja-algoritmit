#include "Key.h"

// Initialize static members
long Key::comparisons = 0;
long Key::assignments = 0;

Key::Key() : value(0) {
}

Key::Key(int val) : value(val) {
}

int Key::getValue() const {
    return value;
}

void Key::setValue(int val) {
    value = val;
}

// Comparison operators - each comparison increments counter
bool Key::operator<(const Key& other) const {
    Key::comparisons++;
    return value < other.value;
}

bool Key::operator<=(const Key& other) const {
    Key::comparisons++;
    return value <= other.value;
}

bool Key::operator>(const Key& other) const {
    Key::comparisons++;
    return value > other.value;
}

bool Key::operator>=(const Key& other) const {
    Key::comparisons++;
    return value >= other.value;
}

bool Key::operator==(const Key& other) const {
    Key::comparisons++;
    return value == other.value;
}

bool Key::operator!=(const Key& other) const {
    Key::comparisons++;
    return value != other.value;
}

// Assignment operator - increments assignment counter
Key& Key::operator=(const Key& other) {
    Key::assignments++;
    if (this != &other) {
        value = other.value;
    }
    return *this;
}

// Static counter accessors
long Key::getComparisons() {
    return comparisons;
}

long Key::getAssignments() {
    return assignments;
}

void Key::resetCounters() {
    comparisons = 0;
    assignments = 0;
}
