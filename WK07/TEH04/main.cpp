#include <iostream>
#include <iomanip>
using namespace std;

// Virheenkäsittelykoodit
enum Error_code { success, fail, overflow, underflow };

const int maxsize = 100; // Pinon/jonon maksimikoko

// ===================================================================
// PINO-LUOKKA
// ===================================================================
template <class Stack_entry>
class Stack {
public:
    Stack();
    bool empty() const;
    bool full() const;
    Error_code push(const Stack_entry &item);
    Error_code pop();
    Error_code top(Stack_entry &item) const;
    int size() const;
    void print() const;

private:
    int count;
    Stack_entry entry[maxsize];
};

template <class Stack_entry>
Stack<Stack_entry>::Stack() {
    count = 0;
}

template <class Stack_entry>
bool Stack<Stack_entry>::empty() const {
    return count == 0;
}

template <class Stack_entry>
bool Stack<Stack_entry>::full() const {
    return count >= maxsize;
}

template <class Stack_entry>
Error_code Stack<Stack_entry>::push(const Stack_entry &item) {
    if (full())
        return overflow;
    entry[count] = item;
    count++;
    return success;
}

template <class Stack_entry>
Error_code Stack<Stack_entry>::pop() {
    if (empty())
        return underflow;
    count--;
    return success;
}

template <class Stack_entry>
Error_code Stack<Stack_entry>::top(Stack_entry &item) const {
    if (empty())
        return underflow;
    item = entry[count - 1];
    return success;
}

template <class Stack_entry>
int Stack<Stack_entry>::size() const {
    return count;
}

template <class Stack_entry>
void Stack<Stack_entry>::print() const {
    if (empty()) {
        cout << "[empty]";
    } else {
        cout << "[";
        for (int i = count - 1; i >= 0; i--) {  // Print from top to bottom
            cout << entry[i];
            if (i > 0) cout << " ";
        }
        cout << "]";
    }
}

// ===================================================================
// JONO-LUOKKA
// ===================================================================
template <class Queue_entry>
class Queue {
public:
    Queue();
    bool empty() const;
    bool full() const;
    Error_code append(const Queue_entry &item);
    Error_code serve();
    Error_code retrieve(Queue_entry &item) const;
    int size() const;
    void print() const;

private:
    int count;
    int front, rear;
    Queue_entry entry[maxsize];
};

template <class Queue_entry>
Queue<Queue_entry>::Queue() {
    count = 0;
    rear = maxsize - 1;
    front = 0;
}

template <class Queue_entry>
bool Queue<Queue_entry>::empty() const {
    return count == 0;
}

template <class Queue_entry>
bool Queue<Queue_entry>::full() const {
    return count >= maxsize;
}

template <class Queue_entry>
Error_code Queue<Queue_entry>::append(const Queue_entry &item) {
    if (full()) 
        return overflow;
    count++;
    rear = ((rear + 1) == maxsize) ? 0 : (rear + 1);
    entry[rear] = item;
    return success;
}

template <class Queue_entry>
Error_code Queue<Queue_entry>::serve() {
    if (empty()) 
        return underflow;
    count--;
    front = ((front + 1) == maxsize) ? 0 : (front + 1);
    return success;
}

template <class Queue_entry>
Error_code Queue<Queue_entry>::retrieve(Queue_entry &item) const {
    if (empty()) 
        return underflow;
    item = entry[front];
    return success;
}

template <class Queue_entry>
int Queue<Queue_entry>::size() const {
    return count;
}

template <class Queue_entry>
void Queue<Queue_entry>::print() const {
    if (empty()) {
        cout << "[empty]";
    } else {
        cout << "[";
        int current = front;
        for (int i = 0; i < count; i++) {  // Print from front to rear
            cout << entry[current];
            if (i < count - 1) cout << " ";
            current = ((current + 1) == maxsize) ? 0 : (current + 1);
        }
        cout << "]";
    }
}

// ===================================================================
// ULKOISET FUNKTIOT (käyttävät vain julkista rajapintaa)
// ===================================================================

// (a) Siirrä kaikki alkiot pinosta jonoon
template <class T>
void stack_to_queue(Stack<T> &s, Queue<T> &q) {
    T item;
    while (!s.empty()) {
        if (s.top(item) == success && !q.full()) {
            q.append(item);
            s.pop();
        } else {
            break; // Queue is full or error occurred
        }
    }
}

// (b) Siirrä kaikki alkiot jonosta pinoon
template <class T>
void queue_to_stack(Queue<T> &q, Stack<T> &s) {
    T item;
    while (!q.empty()) {
        if (q.retrieve(item) == success && !s.full()) {
            s.push(item);
            q.serve();
        } else {
            break; // Stack is full or error occurred
        }
    }
}

// (c) Tyhjennä pino toiseen pinoon säilyttäen järjestys
template <class T>
void stack_to_stack_keep_order(Stack<T> &source, Stack<T> &dest) {
    Stack<T> temp;  // Paikallinen väliaikaispino
    T item;
    
    // Ensin siirretään kaikki alkiot lähteestä väliaikaiseen (kääntää järjestyksen)
    while (!source.empty()) {
        if (source.top(item) == success) {
            temp.push(item);
            source.pop();
        }
    }
    
    // Sitten siirretään kaikki alkiot väliaikaisesta kohteeseen (kääntää uudestaan, palauttaen järjestyksen)
    while (!temp.empty()) {
        if (temp.top(item) == success) {
            dest.push(item);
            temp.pop();
        }
    }
}

// (d) Tyhjennä pino toiseen pinoon kääntäen järjestys
template <class T>
void stack_to_stack_reverse_order(Stack<T> &source, Stack<T> &dest) {
    T item;
    
    // Siirretään suoraan lähteestä kohteeseen (kääntää järjestyksen)
    while (!source.empty()) {
        if (source.top(item) == success) {
            dest.push(item);
            source.pop();
        }
    }
}

// (e) Käytä paikallista pinoa jonon järjestyksen kääntämiseen
template <class T>
void reverse_queue(Queue<T> &q) {
    Stack<T> temp;  // Paikallinen väliaikaispino
    T item;
    
    // Siirretään kaikki alkiot jonosta pinoon
    while (!q.empty()) {
        if (q.retrieve(item) == success) {
            temp.push(item);
            q.serve();
        }
    }
    
    // Siirretään kaikki alkiot pinosta takaisin jonoon (nyt käännettyjä)
    while (!temp.empty()) {
        if (temp.top(item) == success) {
            q.append(item);
            temp.pop();
        }
    }
}

// (f) Käytä paikallista jonoa pinon järjestyksen kääntämiseen
template <class T>
void reverse_stack(Stack<T> &s) {
    Queue<T> temp;  // Paikallinen väliaikaisjono
    T item;
    
    // Siirretään kaikki alkiot pinosta jonoon
    while (!s.empty()) {
        if (s.top(item) == success) {
            temp.append(item);
            s.pop();
        }
    }
    
    // Siirretään kaikki alkiot jonosta takaisin pinoon (nyt käännettyjä)
    while (!temp.empty()) {
        if (temp.retrieve(item) == success) {
            s.push(item);
            temp.serve();
        }
    }
}

// ===================================================================
// APUFUNKTIOT RAKENTEIDEN TÄYTTÄMISEEN TESTAAMISTA VARTEN
// ===================================================================
template <class T>
void fill_stack(Stack<T> &s, T items[], int n) {
    for (int i = 0; i < n; i++) {
        s.push(items[i]);
    }
}

template <class T>
void fill_queue(Queue<T> &q, T items[], int n) {
    for (int i = 0; i < n; i++) {
        q.append(items[i]);
    }
}

// ===================================================================
// PÄÄOHJELMA
// ===================================================================
int main() 
{
    cout << "========================================================================" << endl;
    cout << "  Stack and Queue Manipulation Functions" << endl;
    cout << "  Exercise 4: Parts A-F" << endl;
    cout << "========================================================================" << endl;
    cout << endl;

    // ===================================================================
    // OSA A: Siirrä kaikki alkiot pinosta jonoon
    // ===================================================================
    cout << "========================================================================" << endl;
    cout << "PART A: Move all entries from a Stack into a Queue" << endl;
    cout << "========================================================================" << endl;
    cout << "Operation: stack_to_queue(s, q)" << endl;
    cout << "Result: Items popped from stack and appended to queue" << endl;
    cout << endl;
    
    {
        Stack<char> s;
        Queue<char> q;
        char items[] = {'A', 'B', 'C', 'D', 'E'};
        
        fill_stack(s, items, 5);
        
        cout << "Before:" << endl;
        cout << "  Stack (top->bottom): ";
        s.print();
        cout << endl;
        cout << "  Queue (front->rear):  ";
        q.print();
        cout << endl;
        
        stack_to_queue(s, q);
        
        cout << "After stack_to_queue():" << endl;
        cout << "  Stack (top->bottom): ";
        s.print();
        cout << endl;
        cout << "  Queue (front->rear):  ";
        q.print();
        cout << " (reversed order)" << endl;
        cout << endl;
    }
    
    cout << "========================================================================" << endl;
    cout << endl;

    // ===================================================================
    // OSA B: Siirrä kaikki alkiot jonosta pinoon
    // ===================================================================
    cout << "========================================================================" << endl;
    cout << "PART B: Move all entries from a Queue onto a Stack" << endl;
    cout << "========================================================================" << endl;
    cout << "Operation: queue_to_stack(q, s)" << endl;
    cout << "Result: Items served from queue and pushed onto stack" << endl;
    cout << endl;
    
    {
        Queue<char> q;
        Stack<char> s;
        char items[] = {'A', 'B', 'C', 'D', 'E'};
        
        fill_queue(q, items, 5);
        
        cout << "Before:" << endl;
        cout << "  Queue (front->rear):  ";
        q.print();
        cout << endl;
        cout << "  Stack (top->bottom): ";
        s.print();
        cout << endl;
        
        queue_to_stack(q, s);
        
        cout << "After queue_to_stack():" << endl;
        cout << "  Queue (front->rear):  ";
        q.print();
        cout << endl;
        cout << "  Stack (top->bottom): ";
        s.print();
        cout << " (same order)" << endl;
        cout << endl;
    }
    
    cout << "========================================================================" << endl;
    cout << endl;

    // ===================================================================
    // OSA C: Tyhjennä pino toiseen pinoon säilyttäen järjestys
    // ===================================================================
    cout << "========================================================================" << endl;
    cout << "PART C: Empty one Stack onto another Stack (keep order)" << endl;
    cout << "========================================================================" << endl;
    cout << "Operation: stack_to_stack_keep_order(source, dest)" << endl;
    cout << "Result: Items maintain their relative order using temporary stack" << endl;
    cout << endl;
    
    {
        Stack<char> source, dest;
        char items[] = {'A', 'B', 'C', 'D', 'E'};
        
        fill_stack(source, items, 5);
        
        cout << "Before:" << endl;
        cout << "  Source Stack (top->bottom): ";
        source.print();
        cout << endl;
        cout << "  Dest Stack   (top->bottom): ";
        dest.print();
        cout << endl;
        
        stack_to_stack_keep_order(source, dest);
        
        cout << "After stack_to_stack_keep_order():" << endl;
        cout << "  Source Stack (top->bottom): ";
        source.print();
        cout << endl;
        cout << "  Dest Stack   (top->bottom): ";
        dest.print();
        cout << " (same order)" << endl;
        cout << endl;
    }
    
    cout << "========================================================================" << endl;
    cout << endl;

    // ===================================================================
    // OSA D: Tyhjennä pino toiseen pinoon kääntäen järjestys
    // ===================================================================
    cout << "========================================================================" << endl;
    cout << "PART D: Empty one Stack onto another Stack (reverse order)" << endl;
    cout << "========================================================================" << endl;
    cout << "Operation: stack_to_stack_reverse_order(source, dest)" << endl;
    cout << "Result: Items are in reverse of their original order" << endl;
    cout << endl;
    
    {
        Stack<char> source, dest;
        char items[] = {'A', 'B', 'C', 'D', 'E'};
        
        fill_stack(source, items, 5);
        
        cout << "Before:" << endl;
        cout << "  Source Stack (top->bottom): ";
        source.print();
        cout << endl;
        cout << "  Dest Stack   (top->bottom): ";
        dest.print();
        cout << endl;
        
        stack_to_stack_reverse_order(source, dest);
        
        cout << "After stack_to_stack_reverse_order():" << endl;
        cout << "  Source Stack (top->bottom): ";
        source.print();
        cout << endl;
        cout << "  Dest Stack   (top->bottom): ";
        dest.print();
        cout << " (reversed)" << endl;
        cout << endl;
    }
    
    cout << "========================================================================" << endl;
    cout << endl;

    // ===================================================================
    // OSA E: Käytä paikallista pinoa jonon kääntämiseen
    // ===================================================================
    cout << "========================================================================" << endl;
    cout << "PART E: Use a local Stack to reverse the order of a Queue" << endl;
    cout << "========================================================================" << endl;
    cout << "Operation: reverse_queue(q)" << endl;
    cout << "Result: Queue entries are reversed using a temporary stack" << endl;
    cout << endl;
    
    {
        Queue<char> q;
        char items[] = {'A', 'B', 'C', 'D', 'E'};
        
        fill_queue(q, items, 5);
        
        cout << "Before:" << endl;
        cout << "  Queue (front->rear): ";
        q.print();
        cout << endl;
        
        reverse_queue(q);
        
        cout << "After reverse_queue():" << endl;
        cout << "  Queue (front->rear): ";
        q.print();
        cout << " (reversed)" << endl;
        cout << endl;
    }
    
    cout << "========================================================================" << endl;
    cout << endl;

    // ===================================================================
    // OSA F: Käytä paikallista jonoa pinon kääntämiseen
    // ===================================================================
    cout << "========================================================================" << endl;
    cout << "PART F: Use a local Queue to reverse the order of a Stack" << endl;
    cout << "========================================================================" << endl;
    cout << "Operation: reverse_stack(s)" << endl;
    cout << "Result: Stack entries are reversed using a temporary queue" << endl;
    cout << endl;
    
    {
        Stack<char> s;
        char items[] = {'A', 'B', 'C', 'D', 'E'};
        
        fill_stack(s, items, 5);
        
        cout << "Before:" << endl;
        cout << "  Stack (top->bottom): ";
        s.print();
        cout << endl;
        
        reverse_stack(s);
        
        cout << "After reverse_stack():" << endl;
        cout << "  Stack (top->bottom): ";
        s.print();
        cout << " (reversed)" << endl;
        cout << endl;
    }
    
    cout << "========================================================================" << endl;
    cout << endl;

    // ===================================================================
    // YHTEENVETO
    // ===================================================================
    cout << "========================================================================" << endl;
    cout << "SUMMARY" << endl;
    cout << "========================================================================" << endl;
    cout << endl;
    cout << "All six external functions have been implemented and tested:" << endl;
    cout << endl;
    cout << "A. stack_to_queue()              - Moves Stack to Queue (reverses)" << endl;
    cout << "B. queue_to_stack()              - Moves Queue to Stack (preserves)" << endl;
    cout << "C. stack_to_stack_keep_order()   - Stack to Stack (preserves order)" << endl;
    cout << "D. stack_to_stack_reverse_order()- Stack to Stack (reverses order)" << endl;
    cout << "E. reverse_queue()               - Reverses Queue using Stack" << endl;
    cout << "F. reverse_stack()               - Reverses Stack using Queue" << endl;
    cout << endl;
    cout << "Note: All functions use only the public interface of Stack and Queue." << endl;
    cout << "      They do not access internal data members directly." << endl;
    cout << endl;
    cout << "========================================================================" << endl;
    
    return 0;
}
