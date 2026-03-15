// WK11 / TEH02
// Exercise 2: Write Extended_queue::full() for the linked implementation.
//             Discuss why it is still important to include it.

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

class Queue {
public:
    Queue() { front = rear = nullptr; }
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
        item = front->entry;
        return success;
    }

    ~Queue() { while (!empty()) serve(); }

    Queue(const Queue &original) {
        Node *orig = original.front;
        if (orig == nullptr) { front = rear = nullptr; return; }
        front = rear = new Node(orig->entry);
        while (orig->next != nullptr) {
            orig = orig->next;
            rear->next = new Node(orig->entry);
            rear = rear->next;
        }
    }

    void operator=(const Queue &original) {
        if (this == &original) return;
        Node *new_front = nullptr, *new_rear = nullptr;
        Node *orig = original.front;
        if (orig != nullptr) {
            new_front = new_rear = new Node(orig->entry);
            while (orig->next != nullptr) {
                orig = orig->next;
                new_rear->next = new Node(orig->entry);
                new_rear = new_rear->next;
            }
        }
        while (!empty()) serve();
        front = new_front; rear = new_rear;
    }

protected:
    Node *front, *rear;
};

// -----------------------------------------------------------------------
// Extended_queue  (Chapter 4.4)
// -----------------------------------------------------------------------
class Extended_queue : public Queue {
public:
    // -----------------------------------------------------------------------
    // full()  -- TEH02
    //
    // In a contiguous implementation full() checks against a fixed capacity.
    // In a LINKED implementation there is no fixed upper bound; the queue can
    // grow as long as dynamic memory (the free store / heap) is available.
    // Therefore full() tests whether a new Node can be allocated.
    //
    // Why include it at all?
    //   - Interface consistency: all Queue implementations expose full(), so
    //     client code can call it without knowing the underlying structure.
    //   - Portability: on embedded or memory-constrained systems the heap CAN
    //     be exhausted, so the check is meaningful.
    //   - Prevents silent overflow: append() returns overflow when new fails,
    //     but a client may call full() as a precondition guard BEFORE calling
    //     append().
    // -----------------------------------------------------------------------
    bool full() const
    /*
    Post: Returns true only if dynamic memory is exhausted; otherwise false.
    */
    {
        Node *test = new (nothrow) Node;
        if (test == nullptr) return true;   // heap is truly full
        delete test;
        return false;
    }

    int size() const
    /*
    Post: Returns the number of entries.  (textbook p. 104)
    */
    {
        Node *window = front;
        int count = 0;
        while (window != nullptr) {
            window = window->next;
            count++;
        }
        return count;
    }

    void clear();
    Error_code serve_and_retrieve(Queue_entry &item);
};

void Extended_queue::clear() {
    while (!empty()) serve();
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &item) {
    Error_code result = retrieve(item);
    if (result != success) return result;
    return serve();
}

int main()
{
    cout << "WK11 / TEH02 - Extended_queue::full() linkitetylle jonolle" << endl;

    Extended_queue eq;
    cout << "Tyhjan jonon full(): " << (eq.full() ? "true" : "false") << endl;

    for (char c = 'A'; c <= 'E'; c++) eq.append(c);
    cout << "Viiden alkion jonon full(): " << (eq.full() ? "true" : "false") << endl;
    cout << "Koko: " << eq.size() << endl;

    cout << endl;
    cout << "Miksi full() tarvitaan linkitetyssa toteutuksessa?" << endl;
    cout << "- Yhtenaisyys: asiakas ei tarvitse tietaa toteutuksesta." << endl;
    cout << "- Muistirajoitteiset ymparistot: heap VOI loppua." << endl;
    cout << "- Ehtosuojaus: asiakas voi kutsua full() ennen append():ia." << endl;

    return 0;
}