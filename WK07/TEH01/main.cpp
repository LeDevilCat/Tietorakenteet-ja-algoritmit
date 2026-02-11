#include <iostream>
using namespace std;

// Virheenkäsittelykoodit
enum Error_code { success, fail, overflow, underflow };

// Jonon alkiotyyppi (merkki kuten ohjetekstissä)
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

protected:
    int count;
    int front, rear;
    Queue_entry entry[maxqueue];
};

// Laajennettu jonorakenne lisätoiminnoilla
class Extended_queue : public Queue {
public:
    bool full() const;
    int size() const;
    void clear();
    Error_code serve_and_retrieve(Queue_entry &item);
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

// Extended_queue-luokan toteutus
bool Extended_queue::full() const {
    return count == maxqueue;
}

int Extended_queue::size() const {
    return count;
}

void Extended_queue::clear() {
    count = 0;
    rear = maxqueue - 1;
    front = 0;
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &item) {
    if (count <= 0) 
        return underflow;
    item = entry[front];
    count--;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);
    return success;
}

// Funktioiden esittelyt
void introduction();
char get_command();
bool do_command(char c, Extended_queue &test_queue);
void help();

// Pääohjelma
int main() 
/* Jälkiehto: Vastaanottaa käyttäjän komentoja valikkopohjaisena
              demonstraatio-ohjelmana Extended_queue-luokalle.
   Käyttää: Extended_queue-luokkaa; funktioita introduction, get_command
            ja do_command. */
{
    Extended_queue test_queue;
    introduction();
    while (do_command(get_command(), test_queue));
    return 0;
}

void introduction() 
/* Jälkiehto: Tulostaa ohjelman esittelyn ja käyttöohjeet. */
{
    cout << "=======================================" << endl;
    cout << "  Extended Queue Demonstration Program" << endl;
    cout << "=======================================" << endl;
    cout << endl;
    cout << "This program demonstrates the Extended_queue data structure." << endl;
    cout << "You can perform various operations on the queue." << endl;
    cout << "Type 'H' for help on available commands." << endl;
    cout << endl;
}

char get_command() 
/* Jälkiehto: Lukee käyttäjältä kelvollisen komennon ja palauttaa sen
              muunnettuna pieniksi kirjaimiksi tarvittaessa. */
{
    char command;
    cout << "Enter command (H for help): ";
    cin >> command;
    
    // Muunna pieniksi kirjaimiksi
    if (command >= 'A' && command <= 'Z')
        command = command - 'A' + 'a';
    
    return command;
}

void help() 
/* Jälkiehto: Tulostaa ohjelman ohjenäytön, joka kertoo jokaisen
              käytettävissä olevan komennon merkityksen. */
{
    cout << endl
         << "This program allows the user to enter one command" << endl
         << "(but only one) on each input line." << endl
         << "For example, if the command S is entered, then" << endl
         << "the program will serve the front of the queue." << endl
         << endl
         << "  The valid commands are:" << endl
         << "A - Append the next input character to the extended queue" << endl
         << "S - Serve the front of the extended queue" << endl
         << "R - Retrieve and print the front entry." << endl
         << "# - The current size of the extended queue" << endl
         << "C - Clear the extended queue (same as delete)" << endl
         << "P - Print the extended queue" << endl
         << "H - This help screen" << endl
         << "Q - Quit" << endl
         << "Press <Enter> to continue." << flush;
    
    char c;
    do {
        cin.get(c);
    } while (c != '\n');
}

bool do_command(char c, Extended_queue &test_queue) 
/* Esiehto:  c on kelvollinen komento.
   Jälkiehto: Suorittaa annetun komennon c Extended_queue-rakenteelle test_queue.
              Palauttaa false jos c == 'q', muuten true.
   Käyttää: Extended_queue-luokkaa. */
{
    bool continue_input = true;
    Queue_entry x;
    
    switch (c) {
        case 'a': {
            cout << "Enter a character to append: ";
            cin >> x;
            if (test_queue.append(x) == overflow)
                cout << "Queue is full. Cannot append." << endl;
            else
                cout << "'" << x << "' has been appended to the queue." << endl;
            break;
        }
        
        case 's': {
            if (test_queue.serve() == underflow)
                cout << "Queue is empty. Cannot serve." << endl;
            else
                cout << "The front entry has been served (removed)." << endl;
            break;
        }
        
        case 'r': {
            if (test_queue.retrieve(x) == underflow)
                cout << "Queue is empty." << endl;
            else
                cout << endl << "The first entry is: " << x << endl;
            break;
        }
        
        case '#': {
            cout << "The queue size is: " << test_queue.size() << endl;
            break;
        }
        
        case 'c': {
            test_queue.clear();
            cout << "The queue has been cleared." << endl;
            break;
        }
        
        case 'p': {
            if (test_queue.empty()) {
                cout << "Queue is empty." << endl;
            } else {
                cout << "Queue contents (front to rear): ";
                // Luodaan väliaikainen jono tulostamista varten alkuperäistä tuhoamatta
                Extended_queue temp_queue;
                Queue_entry item;
                int queue_size = test_queue.size();
                
                // Kopioidaan kaikki alkiot ja tulostetaan ne
                Extended_queue copy_queue = test_queue; // Tehdään kopio
                for (int i = 0; i < queue_size; i++) {
                    if (copy_queue.serve_and_retrieve(item) == success) {
                        cout << item;
                        if (i < queue_size - 1) cout << " ";
                    }
                }
                cout << endl;
            }
            break;
        }
        
        case 'h': {
            help();
            break;
        }
        
        case 'q': {
            cout << "Extended queue demonstration finished." << endl;
            continue_input = false;
            break;
        }
        
        default: {
            cout << "Invalid command. Type 'H' for help." << endl;
            break;
        }
    }
    
    return continue_input;
}
