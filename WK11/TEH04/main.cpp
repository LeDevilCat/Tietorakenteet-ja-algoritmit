// WK11 / TEH04
// Exercise 4: Consider adding a count data member to linked Extended_queue.
//   - What changes must be made to all other methods?
//   - Discuss advantages and disadvantages.

#include <iostream>
#include <new>
using namespace std;

typedef char Queue_entry;

enum Error_code { success, underflow, overflow };

struct Node {
    Queue_entry entry;
    Node *next;
    Node() : next(nullptr) {}
    Node(Queue_entry item, Node *add_on = nullptr)
        : entry(item), next(add_on) {}
};

// =======================================================================
// Version A: Extended_queue WITHOUT a count member (original from textbook)
// size() traverses the entire chain -- O(n).
// =======================================================================
class Queue_A {
public:
    Queue_A() { front = rear = nullptr; }
    bool empty() const { return front == nullptr; }

    Error_code append(const Queue_entry &item) {
        Node *new_rear = new (nothrow) Node(item);
        if (new_rear == nullptr) return overflow;
        if (rear == nullptr) front = rear = new_rear;
        else { rear->next = new_rear; rear = new_rear; }
        return success;
    }

    Error_code serve() {
        if (front == nullptr) return underflow;
        Node *old_front = front;
        front = old_front->next;
        if (front == nullptr) rear = nullptr;
        delete old_front;
        return success;
    }

    Error_code retrieve(Queue_entry &item) const {
        if (front == nullptr) return underflow;
        item = front->entry; return success;
    }

    ~Queue_A() { while (!empty()) serve(); }

    Queue_A(const Queue_A &original) {
        Node *orig = original.front;
        if (orig == nullptr) { front = rear = nullptr; return; }
        front = rear = new Node(orig->entry);
        while (orig->next != nullptr) {
            orig = orig->next; rear->next = new Node(orig->entry); rear = rear->next;
        }
    }

    void operator=(const Queue_A &original) {
        if (this == &original) return;
        Node *nf = nullptr, *nr = nullptr;
        Node *orig = original.front;
        if (orig != nullptr) {
            nf = nr = new Node(orig->entry);
            while (orig->next != nullptr) {
                orig = orig->next; nr->next = new Node(orig->entry); nr = nr->next;
            }
        }
        while (!empty()) serve();
        front = nf; rear = nr;
    }

protected:
    Node *front, *rear;
};

class Extended_queue_A : public Queue_A {
public:
    bool full() const {
        Node *test = new (nothrow) Node;
        if (test == nullptr) return true; delete test; return false;
    }
    // O(n) -- traverses entire chain
    int size() const {
        Node *window = front; int count = 0;
        while (window != nullptr) { window = window->next; count++; }
        return count;
    }
    void clear()        { while (!empty()) serve(); }
    Error_code serve_and_retrieve(Queue_entry &item) {
        Error_code r = retrieve(item);
        if (r != success) return r; return serve();
    }
};

// =======================================================================
// Version B: Extended_queue WITH a count member
//
// Changes required to each method:
//   - Constructor:          initialise count = 0              (NEW)
//   - append():             count++ on successful insert      (CHANGED)
//   - serve():              count-- on successful remove      (CHANGED)
//   - clear():              reset count = 0                   (CHANGED)
//   - serve_and_retrieve(): no extra change (calls serve())   (unchanged)
//   - copy constructor:     copy count from original          (CHANGED)
//   - operator=:            copy count after clone            (CHANGED)
//   - size():               return count directly -- O(1)     (SIMPLIFIED)
//   - full(), empty(), retrieve(), ~Queue_B:  unchanged.
// =======================================================================
class Queue_B {
public:
    Queue_B() { front = rear = nullptr; count = 0; }   // count initialised
    bool empty() const { return front == nullptr; }

    Error_code append(const Queue_entry &item) {
        Node *new_rear = new (nothrow) Node(item);
        if (new_rear == nullptr) return overflow;
        if (rear == nullptr) front = rear = new_rear;
        else { rear->next = new_rear; rear = new_rear; }
        count++;                                        // CHANGED
        return success;
    }

    Error_code serve() {
        if (front == nullptr) return underflow;
        Node *old_front = front;
        front = old_front->next;
        if (front == nullptr) rear = nullptr;
        delete old_front;
        count--;                                        // CHANGED
        return success;
    }

    Error_code retrieve(Queue_entry &item) const {
        if (front == nullptr) return underflow;
        item = front->entry; return success;
    }

    ~Queue_B() { while (!empty()) serve(); }

    Queue_B(const Queue_B &original) {                 // CHANGED
        Node *orig = original.front;
        if (orig == nullptr) { front = rear = nullptr; count = 0; return; }
        front = rear = new Node(orig->entry);
        while (orig->next != nullptr) {
            orig = orig->next; rear->next = new Node(orig->entry); rear = rear->next;
        }
        count = original.count;                        // copy count
    }

    void operator=(const Queue_B &original) {          // CHANGED
        if (this == &original) return;
        Node *nf = nullptr, *nr = nullptr;
        Node *orig = original.front;
        if (orig != nullptr) {
            nf = nr = new Node(orig->entry);
            while (orig->next != nullptr) {
                orig = orig->next; nr->next = new Node(orig->entry); nr = nr->next;
            }
        }
        while (!empty()) serve();
        front = nf; rear = nr;
        count = original.count;                        // copy count
    }

protected:
    Node *front, *rear;
    int count;                                         // NEW member
};

class Extended_queue_B : public Queue_B {
public:
    bool full() const {
        Node *test = new (nothrow) Node;
        if (test == nullptr) return true; delete test; return false;
    }
    // O(1) -- direct return
    int size() const { return count; }                 // SIMPLIFIED

    void clear() {
        while (!empty()) serve();                      // serve() updates count
        // count is now 0 because serve() decrements it each time
    }

    Error_code serve_and_retrieve(Queue_entry &item) {
        Error_code r = retrieve(item);
        if (r != success) return r; return serve();    // serve() updates count
    }
};

void print_discussion()
{
    cout << "\nAnalyysi - count-jasenen lisaaminen Extended_queue-luokkaan:" << endl;
    cout << "\nVaadittavat muutokset:" << endl;
    cout << "  Konstruktori:       count = 0 alustus (uusi)" << endl;
    cout << "  append():           count++ onnistuneen lisayksen jalkeen" << endl;
    cout << "  serve():            count-- onnistuneen poiston jalkeen" << endl;
    cout << "  clear():            ei erillistarvetta, serve() hoitaa laskurin" << endl;
    cout << "  serve_and_retrieve: ei muutosta (kutsuu serve():a)" << endl;
    cout << "  Kopiokonstruktori:  count kopioitava originaalista" << endl;
    cout << "  operator=:          count kopioitava kloonauksen jalkeen" << endl;
    cout << "  size():             yksinkertaistuu: return count; (O(1))" << endl;
    cout << "\nEdut:" << endl;
    cout << "  + size() on O(1) eika O(n); nopea toistuvissa kutsuissa." << endl;
    cout << "  + Ei tarvitse lapikayta koko ketjua laskentaan." << endl;
    cout << "\nHaitat:" << endl;
    cout << "  - Jokainen rakenteen muuttava metodi on paivitettava." << endl;
    cout << "  - Virheriski: jos count unohtuu paivittaa, se menee epatahdissa." << endl;
    cout << "  - Yksi int lisaa muistia jokaiselle oliolle (marginaalinen)." << endl;
    cout << "  - Kopiokonstruktori ja operator= monimutkaistuvat hieman." << endl;
}

int main()
{
    cout << "WK11 / TEH04 - count-jasen Extended_queue-luokassa" << endl;

    // Demo Version A (ei laskuria)
    Extended_queue_A a;
    a.append('P'); a.append('Q'); a.append('R');
    cout << "\nVersio A (ilman count):" << endl;
    cout << "  size() = " << a.size() << "  (laskee lapikaynnilla O(n))" << endl;

    // Demo Version B (laskurilla)
    Extended_queue_B b;
    b.append('P'); b.append('Q'); b.append('R');
    cout << "\nVersio B (count-jasenella):" << endl;
    cout << "  size() = " << b.size() << "  (palautetaan suoraan O(1))" << endl;
    b.serve();
    cout << "  size() serve():n jalkeen = " << b.size() << endl;

    // Kopio - varmistetaan count kopioidaan
    Extended_queue_B b2(b);
    cout << "  Kopioidun jonon size() = " << b2.size() << endl;

    print_discussion();
    return 0;
}