#include "RANDOM.H"
#include <iostream>
#include <stack>

// Forward declarations for project entry functions.
void P1();
void P2();
void P3();
void P4();
void P5();


using namespace std;


int main() {
    while (true) {
        cout << "1. Run P1 version of Airport simulator" << endl;
        cout << "2. Run P2 version of Airport simulator" << endl;
        cout << "3. Run P3 version of Airport simulator" << endl;
        cout << "4. Run P4 version of Airport simulator" << endl;
        cout << "5. Run P5 version of Airport simulator" << endl;
        cout << "6. Quit the program" << endl;
        cout << "Your choice: " << flush;

        int choice;
        cin >> choice;

        if (!cin) {
            cout << "Invalid input. Exiting program." << endl;
            break;
        }

        switch (choice) {
        case 1:
            P1();
            break;
        case 2:
            P2();
            break;
        case 3:
            P3();
            break;
        case 4:
            P4();
            break;
        case 5:
            P5();
            break;
        case 6:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please select a number between 1 and 6." << endl;
            break;
        }

        cout << endl;
    }

    return 0;
}