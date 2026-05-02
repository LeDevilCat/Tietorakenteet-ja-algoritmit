#ifndef KEY_H
#define KEY_H

class Key {
private:
    int value;
    static long comparisons;
    static long assignments;

public:
    Key();
    Key(int val);
    
    int getValue() const;
    void setValue(int val);
    
    // Comparison operators
    bool operator<(const Key& other) const;
    bool operator<=(const Key& other) const;
    bool operator>(const Key& other) const;
    bool operator>=(const Key& other) const;
    bool operator==(const Key& other) const;
    bool operator!=(const Key& other) const;
    
    // Assignment operator
    Key& operator=(const Key& other);
    
    // Static counter accessors
    static long getComparisons();
    static long getAssignments();
    static void resetCounters();
};

#endif
