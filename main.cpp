#include <iostream>
#include <string>

#include "event_allocator.h"

using namespace std;

int main()
{

    int seats;

    // ========================================
    // Program Header
    // ========================================

    cout << "========================================\n";

    cout << "     EVENT SEAT ALLOCATION ENGINE\n";

    cout << "========================================\n\n";

    // ========================================
    // Get Event Seat Capacity
    // ========================================

    cout << "Enter total number of seats: ";

    cin >> seats;

    if (seats <= 0)
    {

        cout << "Number of seats must be greater than 0.\n";

        return 0;
    }

    // Create event
    EventSeatAllocator event(seats);

    int choice;

    // ========================================
    // Main Menu
    // ========================================

    do
    {

        cout << "\n========== MENU ==========\n";

        cout << "1. Register Attendee\n";

        cout << "2. Cancel Registration\n";

        cout << "3. View Confirmed Attendees\n";

        cout << "4. View Waitlist\n";

        cout << "5. Export Attendee Manifest\n";

        cout << "6. Exit\n";

        cout << "===========================\n";

        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {

            // =================================
            // Register Attendee
            // =================================

        case 1:
        {

            string name;

            string timestamp;

            cin.ignore();

            cout << "Enter attendee name: ";

            getline(cin, name);

            cout << "Enter registration timestamp: ";

            getline(cin, timestamp);

            event.registerAttendee(
                name,
                timestamp);

            break;
        }

            // =================================
            // Cancel Registration
            // =================================

        case 2:
        {

            int id;

            cout << "Enter attendee ID to cancel: ";

            cin >> id;

            event.cancelRegistration(id);

            break;
        }

            // =================================
            // Display Confirmed
            // =================================

        case 3:

            event.displayConfirmed();

            break;

            // =================================
            // Display Waitlist
            // =================================

        case 4:

            event.displayWaitlist();

            break;

            // =================================
            // Export CSV
            // =================================

        case 5:

            event.exportCSV("attendees.csv");

            break;

            // =================================
            // Exit
            // =================================

        case 6:

            cout << "\nExiting program...\n";

            break;

            // =================================
            // Invalid Choice
            // =================================

        default:

            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}