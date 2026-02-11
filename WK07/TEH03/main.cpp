#include <iostream>
#include <iomanip>
using namespace std;

// Virheenkäsittelykoodit
enum Error_code { success, fail, overflow, underflow };

const int maxsize = 1000; // Pinon/jonon maksimikoko

// ===================================================================
// JONO-LUOKKA (FIFO-kirjanpitoa varten)
// ===================================================================
class Queue {
public:
    Queue();
    bool empty() const;
    bool full() const;
    Error_code append(int item);
    Error_code serve();
    Error_code retrieve(int &item) const;
    int size() const;

private:
    int count;
    int front, rear;
    int entry[maxsize];
};

Queue::Queue() {
    count = 0;
    rear = maxsize - 1;
    front = 0;
}

bool Queue::empty() const {
    return count == 0;
}

bool Queue::full() const {
    return count >= maxsize;
}

Error_code Queue::append(int item) {
    if (full()) 
        return overflow;
    count++;
    rear = ((rear + 1) == maxsize) ? 0 : (rear + 1);
    entry[rear] = item;
    return success;
}

Error_code Queue::serve() {
    if (empty()) 
        return underflow;
    count--;
    front = ((front + 1) == maxsize) ? 0 : (front + 1);
    return success;
}

Error_code Queue::retrieve(int &item) const {
    if (empty()) 
        return underflow;
    item = entry[front];
    return success;
}

int Queue::size() const {
    return count;
}

// ===================================================================
// PINO-LUOKKA (LIFO-kirjanpitoa varten)
// ===================================================================
class Stack {
public:
    Stack();
    bool empty() const;
    bool full() const;
    Error_code push(int item);
    Error_code pop();
    Error_code top(int &item) const;
    int size() const;

private:
    int count;
    int entry[maxsize];
};

Stack::Stack() {
    count = 0;
}

bool Stack::empty() const {
    return count == 0;
}

bool Stack::full() const {
    return count >= maxsize;
}

Error_code Stack::push(int item) {
    if (full())
        return overflow;
    entry[count] = item;
    count++;
    return success;
}

Error_code Stack::pop() {
    if (empty())
        return underflow;
    count--;
    return success;
}

Error_code Stack::top(int &item) const {
    if (empty())
        return underflow;
    item = entry[count - 1];
    return success;
}

int Stack::size() const {
    return count;
}

// ===================================================================
// TRANSAKTIO-FUNKTIOT
// ===================================================================

void buy_shares_queue(Queue &q, int shares, int price_per_share, const string& month) {
    cout << month << ": Buying " << shares << " shares at $" << price_per_share 
         << "/share (Total: $" << (shares * price_per_share) << ")" << endl;
    
    for (int i = 0; i < shares; i++) {
        q.append(price_per_share);
    }
    cout << "   Queue now has " << q.size() << " shares." << endl;
}

int sell_shares_queue(Queue &q, int shares, int price_per_share, const string& month) {
    cout << month << ": Selling " << shares << " shares at $" << price_per_share << "/share" << endl;
    
    int total_gain = 0;
    int purchase_price;
    
    for (int i = 0; i < shares; i++) {
        if (q.retrieve(purchase_price) == success) {
            q.serve();
            int gain = price_per_share - purchase_price;
            total_gain += gain;
        }
    }
    
    cout << "   Gain/Loss from this sale: $" << total_gain << endl;
    cout << "   Queue now has " << q.size() << " shares." << endl;
    return total_gain;
}

void buy_shares_stack(Stack &s, int shares, int price_per_share, const string& month) {
    cout << month << ": Buying " << shares << " shares at $" << price_per_share 
         << "/share (Total: $" << (shares * price_per_share) << ")" << endl;
    
    for (int i = 0; i < shares; i++) {
        s.push(price_per_share);
    }
    cout << "   Stack now has " << s.size() << " shares." << endl;
}

int sell_shares_stack(Stack &s, int shares, int price_per_share, const string& month) {
    cout << month << ": Selling " << shares << " shares at $" << price_per_share << "/share" << endl;
    
    int total_gain = 0;
    int purchase_price;
    
    for (int i = 0; i < shares; i++) {
        if (s.top(purchase_price) == success) {
            s.pop();
            int gain = price_per_share - purchase_price;
            total_gain += gain;
        }
    }
    
    cout << "   Gain/Loss from this sale: $" << total_gain << endl;
    cout << "   Stack now has " << s.size() << " shares." << endl;
    return total_gain;
}

// ===================================================================
// PÄÄOHJELMA
// ===================================================================
int main() 
{
    cout << "========================================================================" << endl;
    cout << "  Stock Trading Simulation: FIFO vs LIFO Accounting" << endl;
    cout << "  Exercise 3: Capital Gain/Loss Calculation" << endl;
    cout << "========================================================================" << endl;
    cout << endl;
    
    cout << "Transaction Schedule:" << endl;
    cout << "  January:   Buy 100 shares at $10/share" << endl;
    cout << "  April:     Buy 100 shares at $30/share" << endl;
    cout << "  June:      Sell 100 shares at $20/share" << endl;
    cout << "  September: Buy 100 shares at $50/share" << endl;
    cout << "  November:  Sell 100 shares at $30/share" << endl;
    cout << endl;
    cout << "========================================================================" << endl;
    cout << endl;

    // ===================================================================
    // OSA A: FIFO (First-In, First-Out) - Jonon käyttö
    // ===================================================================
    cout << "========================================================================" << endl;
    cout << "PART A: FIFO (First-In, First-Out) Accounting - Using QUEUE" << endl;
    cout << "========================================================================" << endl;
    cout << "In FIFO, shares bought first are sold first (like a queue)." << endl;
    cout << endl;
    
    {
        Queue fifo_queue;
        int total_capital_gain = 0;
        
        // Tammikuu: Ostetaan 100 osaketta hintaan $10
        buy_shares_queue(fifo_queue, 100, 10, "January");
        cout << endl;
        
        // Huhtikuu: Ostetaan 100 osaketta hintaan $30
        buy_shares_queue(fifo_queue, 100, 30, "April");
        cout << endl;
        
        // Kesäkuu: Myydään 100 osaketta hintaan $20
        // FIFO:ssa myydään tammikuun osakkeet (ostettu $10)
        cout << "--- FIRST SALE ---" << endl;
        int gain_june = sell_shares_queue(fifo_queue, 100, 20, "June");
        total_capital_gain += gain_june;
        cout << "   (Sold January shares: bought at $10, sold at $20, gain = $10/share)" << endl;
        cout << "   Running total gain: $" << total_capital_gain << endl;
        cout << endl;
        
        // Syyskuu: Ostetaan 100 osaketta hintaan $50
        buy_shares_stack(fifo_queue, 100, 50, "September");
        cout << endl;
        
        // Marraskuu: Myydään 100 osaketta hintaan $30
        // FIFO:ssa myydään huhtikuun osakkeet (ostettu $30)
        cout << "--- SECOND SALE ---" << endl;
        int gain_nov = sell_shares_queue(fifo_queue, 100, 30, "November");
        total_capital_gain += gain_nov;
        cout << "   (Sold April shares: bought at $30, sold at $30, gain = $0/share)" << endl;
        cout << "   Running total gain: $" << total_capital_gain << endl;
        cout << endl;
        
        cout << "--- END OF YEAR SUMMARY (FIFO) ---" << endl;
        cout << "Shares still owned: " << fifo_queue.size() << " (September shares at $50/share)" << endl;
        cout << "These shares are not included in gain/loss calculation." << endl;
        cout << endl;
        cout << "*** TOTAL CAPITAL GAIN (FIFO): $" << total_capital_gain << " ***" << endl;
        cout << endl;
    }
    
    cout << "========================================================================" << endl;
    cout << endl;

    // ===================================================================
    // OSA B: LIFO (Last-In, First-Out) - Pinon käyttö
    // ===================================================================
    cout << "========================================================================" << endl;
    cout << "PART B: LIFO (Last-In, First-Out) Accounting - Using STACK" << endl;
    cout << "========================================================================" << endl;
    cout << "In LIFO, shares bought last are sold first (like a stack)." << endl;
    cout << endl;
    
    {
        Stack lifo_stack;
        int total_capital_gain = 0;
        
        // Tammikuu: Ostetaan 100 osaketta hintaan $10
        buy_shares_stack(lifo_stack, 100, 10, "January");
        cout << endl;
        
        // Huhtikuu: Ostetaan 100 osaketta hintaan $30
        buy_shares_stack(lifo_stack, 100, 30, "April");
        cout << endl;
        
        // Kesäkuu: Myydään 100 osaketta hintaan $20
        // LIFO:ssa myydään huhtikuun osakkeet (ostettu $30) - viimeisin ostos
        cout << "--- FIRST SALE ---" << endl;
        int gain_june = sell_shares_stack(lifo_stack, 100, 20, "June");
        total_capital_gain += gain_june;
        cout << "   (Sold April shares: bought at $30, sold at $20, loss = -$10/share)" << endl;
        cout << "   Running total gain: $" << total_capital_gain << endl;
        cout << endl;
        
        // Syyskuu: Ostetaan 100 osaketta hintaan $50
        buy_shares_stack(lifo_stack, 100, 50, "September");
        cout << endl;
        
        // Marraskuu: Myydään 100 osaketta hintaan $30
        // LIFO:ssa myydään syyskuun osakkeet (ostettu $50) - viimeisin ostos
        cout << "--- SECOND SALE ---" << endl;
        int gain_nov = sell_shares_stack(lifo_stack, 100, 30, "November");
        total_capital_gain += gain_nov;
        cout << "   (Sold September shares: bought at $50, sold at $30, loss = -$20/share)" << endl;
        cout << "   Running total gain: $" << total_capital_gain << endl;
        cout << endl;
        
        cout << "--- END OF YEAR SUMMARY (LIFO) ---" << endl;
        cout << "Shares still owned: " << lifo_stack.size() << " (January shares at $10/share)" << endl;
        cout << "These shares are not included in gain/loss calculation." << endl;
        cout << endl;
        cout << "*** TOTAL CAPITAL GAIN (LIFO): $" << total_capital_gain << " ***" << endl;
        cout << endl;
    }
    
    cout << "========================================================================" << endl;
    cout << endl;

    // ===================================================================
    // VERTAILU
    // ===================================================================
    cout << "========================================================================" << endl;
    cout << "COMPARISON OF FIFO vs LIFO" << endl;
    cout << "========================================================================" << endl;
    cout << endl;
    cout << "FIFO (Queue) Result: +$1,000 capital gain" << endl;
    cout << "  - June: Sold January shares (bought $10, sold $20) = +$1,000" << endl;
    cout << "  - November: Sold April shares (bought $30, sold $30) = $0" << endl;
    cout << "  - Still own: September shares (100 @ $50)" << endl;
    cout << endl;
    cout << "LIFO (Stack) Result: -$3,000 capital loss" << endl;
    cout << "  - June: Sold April shares (bought $30, sold $20) = -$1,000" << endl;
    cout << "  - November: Sold September shares (bought $50, sold $30) = -$2,000" << endl;
    cout << "  - Still own: January shares (100 @ $10)" << endl;
    cout << endl;
    cout << "Difference: $4,000" << endl;
    cout << "This demonstrates how the accounting method (FIFO vs LIFO) can" << endl;
    cout << "significantly impact reported gains/losses for tax purposes!" << endl;
    cout << endl;
    cout << "========================================================================" << endl;
    
    return 0;
}
