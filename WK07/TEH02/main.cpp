#include <iostream>
#include <iomanip>
using namespace std;

// Virheenkäsittelykoodit
enum Error_code { success, fail, overflow, underflow };

// Jonon alkiotyyppi (merkki)
typedef char Queue_entry;

const int maxqueue = 100; // Jonon maksimikoko

// Perus-jonorakenne
class Queue {
public:
    Queue();
    bool empty() const;
    Error_code append(const Queue_entry &item);
    Error_code serve();
    Error_code retrieve(Queue_entry &item) const;
    
    // Apufunktio jonon sisällön tulostamiseen
    void print_queue() const;
    int size() const;

protected:
    int count;
    int front, rear;
    Queue_entry entry[maxqueue];
};

// Queue-luokan toteutus
Queue::Queue() {
    count = 0;
    rear = maxqueue - 1;
    front = 0;
}

bool Queue::empty() const {
    return count == 0;
}

Error_code Queue::append(const Queue_entry &item) {
    if (count >= maxqueue) 
        return overflow;
    count++;
    rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
    entry[rear] = item;
    return success;
}

Error_code Queue::serve() {
    if (count <= 0) 
        return underflow;
    count--;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);
    return success;
}

Error_code Queue::retrieve(Queue_entry &item) const {
    if (count <= 0) 
        return underflow;
    item = entry[front];
    return success;
}

int Queue::size() const {
    return count;
}

void Queue::print_queue() const {
    if (empty()) {
        cout << "[empty]";
    } else {
        cout << "[";
        int current = front;
        for (int i = 0; i < count; i++) {
            cout << entry[current];
            if (i < count - 1) cout << ", ";
            current = ((current + 1) == maxqueue) ? 0 : (current + 1);
        }
        cout << "]";
    }
}

// Apufunktio askeleen tulostamiseen
void print_step(const string& operation, const Queue& q, char x = '\0', char y = '\0', 
                bool show_x = false, bool show_y = false) {
    cout << left << setw(30) << operation << " Queue: ";
    q.print_queue();
    if (show_x) cout << "  x = '" << x << "'";
    if (show_y) cout << "  y = '" << y << "'";
    cout << endl;
}

int main() 
{
    cout << "========================================" << endl;
    cout << "  Queue Operations Demonstration" << endl;
    cout << "  Exercise 2: Parts A, B, and C" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // ===================================================================
    // OSA A
    // ===================================================================
    cout << "========================================" << endl;
    cout << "PART A:" << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    {
        Queue q;
        cout << left << setw(30) << "Queue q;" << " Queue: ";
        q.print_queue();
        cout << endl;
        
        q.append('a');
        print_step("q.append('a');", q);
        
        q.serve();
        print_step("q.serve();", q);
        
        q.append('b');
        print_step("q.append('b');", q);
        
        q.serve();
        print_step("q.serve();", q);
        
        q.append('c');
        print_step("q.append('c');", q);
        
        q.append('d');
        print_step("q.append('d');", q);
        
        q.serve();
        print_step("q.serve();", q);
        
        cout << endl;
        cout << "Final result: Queue contains 'd' (front: 'd', size: 1)" << endl;
    }
    
    cout << endl;
    
    // ===================================================================
    // OSA B
    // ===================================================================
    cout << "========================================" << endl;
    cout << "PART B:" << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    {
        Queue q;
        char x = '?';  // Alustetaan näyttämään että se on määrittelemätön
        
        cout << left << setw(30) << "Queue q;" << " Queue: ";
        q.print_queue();
        cout << "  x = '" << x << "'" << endl;
        
        q.append('a');
        print_step("q.append('a');", q, x, '\0', true, false);
        
        q.append('b');
        print_step("q.append('b');", q, x, '\0', true, false);
        
        q.retrieve(x);
        print_step("q.retrieve(x);", q, x, '\0', true, false);
        
        q.serve();
        print_step("q.serve();", q, x, '\0', true, false);
        
        q.append('c');
        print_step("q.append('c');", q, x, '\0', true, false);
        
        q.append(x);
        print_step("q.append(x);", q, x, '\0', true, false);
        
        q.serve();
        print_step("q.serve();", q, x, '\0', true, false);
        
        q.serve();
        print_step("q.serve();", q, x, '\0', true, false);
        
        cout << endl;
        cout << "Final result: Queue contains 'a' (front: 'a', size: 1), x = 'a'" << endl;
    }
    
    cout << endl;
    
    // ===================================================================
    // OSA C
    // ===================================================================
    cout << "========================================" << endl;
    cout << "PART C:" << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    {
        Queue q;
        char x = '?';  // Alustetaan näyttämään että se on määrittelemätön
        char y = '?';  // Alustetaan näyttämään että se on määrittelemätön
        
        cout << left << setw(30) << "Queue q;" << " Queue: ";
        q.print_queue();
        cout << "  x = '" << x << "'  y = '" << y << "'" << endl;
        
        q.append('a');
        print_step("q.append('a');", q, x, y, true, true);
        
        x = 'b';
        print_step("x = 'b';", q, x, y, true, true);
        
        q.append('x');  // Huom: lisää merkkinä 'x', ei muuttujan x arvoa
        print_step("q.append('x');", q, x, y, true, true);
        
        q.retrieve(y);
        print_step("q.retrieve(y);", q, x, y, true, true);
        
        q.serve();
        print_step("q.serve();", q, x, y, true, true);
        
        q.append(x);
        print_step("q.append(x);", q, x, y, true, true);
        
        q.serve();
        print_step("q.serve();", q, x, y, true, true);
        
        q.append(y);
        print_step("q.append(y);", q, x, y, true, true);
        
        cout << endl;
        cout << "Final result: Queue contains ['b', 'a'] (front: 'b', size: 2)" << endl;
        cout << "             x = 'b', y = 'a'" << endl;
    }
    
    cout << endl;
    cout << "========================================" << endl;
    cout << "Demonstration completed!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
