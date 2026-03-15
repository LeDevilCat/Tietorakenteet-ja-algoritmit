// WK11 / TEH03
// Exercise 3: Write Extended_queue methods:
//   (a) clear
//   (b) serve_and_retrieve

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

class Extended_queue : public Queue {
public:
    bool full() const {
        Node *test = new (nothrow) Node;
        if (test == nullptr) return true;
        delete test; return false;
    }

    int size() const {
        Node *window = front; int count = 0;
        while (window != nullptr) { window = window->next; count++; }
        return count;
    }

    // -----------------------------------------------------------------------
    // (a) clear
    //
    // Post: The Extended_queue is made empty; all nodes are freed.
    //       Achieved by repeatedly calling the inherited serve() which
    //       deletes each node and maintains front/rear correctly.
    // -----------------------------------------------------------------------
    void clear()
    /*
    Post: The Extended_queue is reset to empty.
    */
    {
        while (!empty())
            serve();
    }

    // -----------------------------------------------------------------------
    // (b) serve_and_retrieve
    //
    // Post: The front entry is copied into item AND removed from the queue.
    //       Returns underflow if the queue was empty.
    //       Strategy: retrieve first (copy without removing), then serve
    //       (remove without copying), matching the textbook pattern.
    // -----------------------------------------------------------------------
    Error_code serve_and_retrieve(Queue_entry &item)
    /*
    Post: The front entry is retrieved into item and served (removed).
          Returns underflow if empty.
    */
    {
        Error_code result = retrieve(item);   // copy front entry
        if (result != success) return result;  // was empty
        return serve();                        // remove front node
    }
};

int main()
{
    cout << "WK11 / TEH03 - Extended_queue: clear() ja serve_and_retrieve()" << endl;

    Extended_queue eq;
    eq.append('X');
    eq.append('Y');
    eq.append('Z');
    cout << "Koko ennen clear(): " << eq.size() << endl;

    // (a) clear
    eq.clear();
    cout << "(a) Koko clear():n jalkeen: " << eq.size() << endl;
    cout << "(a) empty(): " << (eq.empty() ? "true" : "false") << endl;

    // (b) serve_and_retrieve
    eq.append('1');
    eq.append('2');
    eq.append('3');
    cout << "Koko ennen serve_and_retrieve(): " << eq.size() << endl;

    Queue_entry item = '?';
    Error_code code = eq.serve_and_retrieve(item);
    cout << "(b) serve_and_retrieve() -> '" << item << "'  code="
         << (code == success ? "success" : "error") << endl;
    cout << "    Koko poiston jalkeen: " << eq.size() << endl;

    // Tyhjalle jonolle
    eq.clear();
    code = eq.serve_and_retrieve(item);
    cout << "(b) tyhjalle: " << (code == underflow ? "underflow (oikein)" : "virhe") << endl;

    return 0;
}