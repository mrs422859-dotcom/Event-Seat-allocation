#include "event_allocator.h"

#include <fstream>
#include <iomanip>

// ============================================
// Constructor
// ============================================

EventSeatAllocator::EventSeatAllocator(int seats)
{

    totalSeats = seats;

    nextId = 1;
}

// ============================================
// Register Attendee
// ============================================

void EventSeatAllocator::registerAttendee(
    const string &name,
    const string &timestamp)
{

    Attendee attendee;

    attendee.id = nextId++;

    attendee.name = name;

    attendee.timestamp = timestamp;

    // ----------------------------------------
    // If a seat is available
    // ----------------------------------------

    if (confirmed.size() < totalSeats)
    {

        confirmed.push_back(attendee);

        cout << "\nRegistration successful.\n";

        cout << name << " -> CONFIRMED\n";
    }

    // ----------------------------------------
    // Otherwise add to waitlist
    // ----------------------------------------

    else
    {

        waitlist.push(attendee);

        cout << "\nRegistration successful.\n";

        cout << name << " -> WAITLIST\n";
    }
}

// ============================================
// Cancel Registration
// ============================================

void EventSeatAllocator::cancelRegistration(int id)
{

    bool found = false;

    // Search for attendee in confirmed list
    for (
        auto it = confirmed.begin();
        it != confirmed.end();
        ++it)
    {

        if (it->id == id)
        {

            string cancelledName = it->name;

            // Remove attendee
            confirmed.erase(it);

            cout << "\n"
                 << cancelledName
                 << " has been cancelled.\n";

            found = true;

            // --------------------------------
            // Promote from waitlist
            // --------------------------------

            if (!waitlist.empty())
            {

                Attendee promoted = waitlist.top();

                waitlist.pop();

                confirmed.push_back(promoted);

                cout << promoted.name
                     << " has been promoted from WAITLIST to CONFIRMED.\n";
            }

            break;
        }
    }

    // Attendee not found
    if (!found)
    {

        cout << "\nConfirmed attendee with ID "
             << id
             << " not found.\n";
    }
}

// ============================================
// Display Confirmed Attendees
// ============================================

void EventSeatAllocator::displayConfirmed() const
{

    cout << "\n============================================\n";

    cout << "           CONFIRMED ATTENDEES\n";

    cout << "============================================\n";

    if (confirmed.empty())
    {

        cout << "No confirmed attendees.\n";

        return;
    }

    cout << left
         << setw(8) << "ID"
         << setw(20) << "Name"
         << "Timestamp\n";

    cout << "--------------------------------------------\n";

    for (const auto &attendee : confirmed)
    {

        cout << left
             << setw(8) << attendee.id
             << setw(20) << attendee.name
             << attendee.timestamp
             << '\n';
    }
}

// ============================================
// Display Waitlist
// ============================================

void EventSeatAllocator::displayWaitlist() const
{

    cout << "\n============================================\n";

    cout << "                 WAITLIST\n";

    cout << "============================================\n";

    if (waitlist.empty())
    {

        cout << "Waitlist is empty.\n";

        return;
    }

    // Copy priority queue so original remains unchanged
    auto temp = waitlist;

    cout << left
         << setw(8) << "ID"
         << setw(20) << "Name"
         << "Timestamp\n";

    cout << "--------------------------------------------\n";

    while (!temp.empty())
    {

        Attendee attendee = temp.top();

        temp.pop();

        cout << left
             << setw(8) << attendee.id
             << setw(20) << attendee.name
             << attendee.timestamp
             << '\n';
    }
}

// ============================================
// Export Attendee Manifest
// ============================================

void EventSeatAllocator::exportCSV(
    const string &filename) const
{

    ofstream file(filename);

    if (!file.is_open())
    {

        cout << "\nError: Could not create CSV file.\n";

        return;
    }

    // CSV header
    file << "ID,Name,Registration Timestamp,Status\n";

    // ----------------------------------------
    // Export confirmed attendees
    // ----------------------------------------

    for (const auto &attendee : confirmed)
    {

        file << attendee.id << ","
             << attendee.name << ","
             << attendee.timestamp << ","
             << "CONFIRMED\n";
    }

    // ----------------------------------------
    // Export waitlisted attendees
    // ----------------------------------------

    auto temp = waitlist;

    while (!temp.empty())
    {

        Attendee attendee = temp.top();

        temp.pop();

        file << attendee.id << ","
             << attendee.name << ","
             << attendee.timestamp << ","
             << "WAITLIST\n";
    }

    file.close();

    cout << "\nManifest exported successfully to "
         << filename
         << "\n";
}

// ============================================
// Get Confirmed Count
// ============================================

int EventSeatAllocator::getConfirmedCount() const
{

    return static_cast<int>(confirmed.size());
}

// ============================================
// Get Waitlist Count
// ============================================

int EventSeatAllocator::getWaitlistCount() const
{

    return static_cast<int>(waitlist.size());
}

// ============================================
// Get Next Waitlist ID
// ============================================

int EventSeatAllocator::getNextWaitlistId() const
{

    if (waitlist.empty())
    {

        return -1;
    }

    return waitlist.top().id;
}