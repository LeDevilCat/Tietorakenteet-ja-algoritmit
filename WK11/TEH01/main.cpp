// WK11 / TEH01
// Exercise 1: Write the following methods for linked queues:
//   (a) empty, (b) retrieve, (c) destructor,
//   (d) copy constructor, (e) overloaded assignment operator.
//
// The textbook (Chapter 4.4) gives Queue with front/rear Node pointers.
// append() and serve() are provided; we implement the five requested methods.

#include <iostream>
#include <new>
using namespace std;

typedef char Queue_entry;

enum Error_code { success, underflow, overflow };

// -----------------------------------------------------------------------
// Node struct (Chapter 4, Sect. 4.1)
// -----------------------------------------------------------------------
struct Node {
    Queue_entry entry;
    Node *next;

    Node() : next(nullptr) {}
    Node(Queue_entry item, Node *add_on = nullptr)
        : entry(item), next(add_on) {}
};

// -----------------------------------------------------------------------
// Queue class
// -----------------------------------------------------------------------
class Queue {
public:
    Queue();

    // --- methods given by the textbook ---
    Error_code append(const Queue_entry &item);
    Error_code serve();

    // --- (a) ---
    bool empty() const;

    // --- (b) ---
    Error_code retrieve(Queue_entry &item) const;

    // --- (c) ---
    ~Queue();

    // --- (d) ---
    Queue(const Queue &original);

    // --- (e) ---
    void operator=(const Queue &original);

protected:
    Node *front, *rear;
};

// Constructor
Queue::Queue()
/*
Post: The Queue is initialized to be empty.
*/
{
    front = rear = nullptr;
}

// append  (textbook p. 103)
Error_code Queue::append(const Queue_entry &item)
/*
Post: item is added to the rear.  Returns overflow if memory exhausted.
*/
{
    Node *new_rear = new (nothrow) Node(item);
    if (new_rear == nullptr) return overflow;
    if (rear == nullptr)
        front = rear = new_rear;
    else {
        rear->next = new_rear;
        rear = new_rear;
    }
    return success;
}

// serve  (textbook p. 103)
Error_code Queue::serve()
/*
Post: The front entry is removed.  Returns underflow if empty.
*/
{
    if (front == nullptr) return underflow;
    Node *old_front = front;
    front = old_front->next;
    if (front == nullptr) rear = nullptr;
    delete old_front;
    return success;
}

// -----------------------------------------------------------------------
// (a) empty
// -----------------------------------------------------------------------
bool Queue::empty() const
/*
Post: Returns true iff the Queue contains no entries.
*/
{
    return front == nullptr;
}

// -----------------------------------------------------------------------
// (b) retrieve
// -----------------------------------------------------------------------
Error_code Queue::retrieve(Queue_entry &item) const
/*
Post: The front entry is copied into item.
      Returns underflow if the Queue is empty.
*/
{
    if (front == nullptr) return underflow;
    item = front->entry;
    return success;
}

// -----------------------------------------------------------------------
// (c) destructor
// Policy (Chapter 4.3): every linked structure must have a destructor.
// -----------------------------------------------------------------------
Queue::~Queue()
/*
Post: All nodes are deleted; memory is returned to the free store.
*/
{
    while (!empty())
        serve();
}

// -----------------------------------------------------------------------
// (d) copy constructor
// Policy (Chapter 4.3): include a copy constructor to ensure value semantics.
// -----------------------------------------------------------------------
Queue::Queue(const Queue &original)
/*
Post: The Queue is initialized as a deep copy of original.
*/
{
    Node *original_node = original.front;
    if (original_node == nullptr) {
        front = rear = nullptr;
        return;
    }
    // Copy first node
    front = rear = new Node(original_node->entry);
    // Copy remaining nodes
    while (original_node->next != nullptr) {
        original_node = original_node->next;
        rear->next = new Node(original_node->entry);
        rear = rear->next;
    }
}

// -----------------------------------------------------------------------
// (e) overloaded assignment operator
// Chapter 4.3: build copy first, then clear old, then install copy.
// -----------------------------------------------------------------------
void Queue::operator=(const Queue &original)
/*
Post: The Queue is reset as a deep copy of original.
*/
{
    if (this == &original) return;   // guard against self-assignment

    // Step 1: duplicate original's nodes
    Node *new_front = nullptr, *new_rear = nullptr;
    Node *original_node = original.front;
    if (original_node != nullptr) {
        new_front = new_rear = new Node(original_node->entry);
        while (original_node->next != nullptr) {
            original_node = original_node->next;
            new_rear->next = new Node(original_node->entry);
            new_rear = new_rear->next;
        }
    }

    // Step 2: clear existing entries
    while (!empty())
        serve();

    // Step 3: install new entries
    front = new_front;
    rear  = new_rear;
}

// -----------------------------------------------------------------------
// Demo / driver
// -----------------------------------------------------------------------
int main()
{
    cout << "WK11 / TEH01 - Linked Queue metodit (a)-(e)" << endl;

    Queue q;
    // (a) empty on tyhjaalle jonolla
    cout << "(a) empty() tyhjalle: " << (q.empty() ? "true" : "false") << endl;

    q.append('A');
    q.append('B');
    q.append('C');
    cout << "(a) empty() kolmen alkion jonolla: " << (q.empty() ? "true" : "false") << endl;

    // (b) retrieve
    Queue_entry item = '?';
    q.retrieve(item);
    cout << "(b) retrieve() -> '" << item << "'  (jono ennallaan)" << endl;

    // (d) copy constructor
    Queue q_copy(q);
    q_copy.retrieve(item);
    cout << "(d) kopiokonstruktori: kopion front -> '" << item << "'" << endl;

    // Muuta kopiota; alkuperainen ei saa muuttua
    q_copy.serve();
    q.retrieve(item);
    cout << "    alkuperaisen front edelleen '" << item << "' (arvokopio toimii)" << endl;

    // (e) assignment operator
    Queue q_assigned;
    q_assigned.append('X');
    q_assigned = q;
    q_assigned.retrieve(item);
    cout << "(e) operator=: sijoitetun front -> '" << item << "'" << endl;

    // (c) destruktorit kutsutaan automaattisesti kun q, q_copy, q_assigned
    //     poistuvat skoopista -- muistivuotoa ei synny.
    cout << "(c) destruktori vapauttaa kaikki solmut automaattisesti." << endl;

    return 0;
}