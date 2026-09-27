#ifndef EVENT_ALLOCATOR_H
#define EVENT_ALLOCATOR_H

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

// Represents one attendee
struct Attendee
{

    int id;
    string name;
    string timestamp;
};

// Priority Queue Comparator
// Smaller ID means earlier registration.
// Therefore, earlier registrations get higher priority.
struct CompareAttendee
{

    bool operator()(const Attendee &a, const Attendee &b) const
    {

        return a.id > b.id;
    }
};

class EventSeatAllocator
{

private:
    int totalSeats;
    int nextId;

    // Stores confirmed attendees
    vector<Attendee> confirmed;

    // Min-heap based waitlist
    priority_queue<
        Attendee,
        vector<Attendee>,
        CompareAttendee>
        waitlist;

public:
    // Constructor
    EventSeatAllocator(int seats);

    // Register a new attendee
    void registerAttendee(
        const string &name,
        const string &timestamp);

    // Cancel a confirmed registration
    void cancelRegistration(int id);

    // Display confirmed attendees
    void displayConfirmed() const;

    // Display waitlist
    void displayWaitlist() const;

    // Export attendee manifest to CSV
    void exportCSV(const string &filename) const;

    // Functions used by tests
    int getConfirmedCount() const;

    int getWaitlistCount() const;

    int getNextWaitlistId() const;
};

#endif