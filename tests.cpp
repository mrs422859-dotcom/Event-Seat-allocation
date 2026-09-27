#include <iostream>
#include <cassert>

#include "event_allocator.h"

using namespace std;

// ============================================
// TEST 1: Seat Allocation
// ============================================

void testSeatAllocation()
{

    EventSeatAllocator event(3);

    event.registerAttendee(
        "Alice",
        "10:01");

    event.registerAttendee(
        "Bob",
        "10:02");

    event.registerAttendee(
        "Charlie",
        "10:03");

    // All three should be confirmed
    assert(event.getConfirmedCount() == 3);

    // Nobody should be waiting
    assert(event.getWaitlistCount() == 0);

    cout << "[PASS] Seat allocation test\n";
}

// ============================================
// TEST 2: Waitlist
// ============================================

void testWaitlist()
{

    EventSeatAllocator event(2);

    event.registerAttendee(
        "Alice",
        "10:01");

    event.registerAttendee(
        "Bob",
        "10:02");

    event.registerAttendee(
        "Charlie",
        "10:03");

    event.registerAttendee(
        "David",
        "10:04");

    // Two seats
    assert(event.getConfirmedCount() == 2);

    // Two people should be waiting
    assert(event.getWaitlistCount() == 2);

    cout << "[PASS] Waitlist test\n";
}

// ============================================
// TEST 3: Priority Queue Ordering
// ============================================

void testPriorityQueue()
{

    EventSeatAllocator event(1);

    event.registerAttendee(
        "Alice",
        "10:01");

    event.registerAttendee(
        "Bob",
        "10:02");

    event.registerAttendee(
        "Charlie",
        "10:03");

    // Bob registered before Charlie.
    // Therefore Bob should be at the top.
    assert(event.getNextWaitlistId() == 2);

    cout << "[PASS] Priority queue ordering test\n";
}

// ============================================
// TEST 4: Waitlist Promotion
// ============================================

void testWaitlistPromotion()
{

    EventSeatAllocator event(2);

    event.registerAttendee(
        "Alice",
        "10:01");

    event.registerAttendee(
        "Bob",
        "10:02");

    event.registerAttendee(
        "Charlie",
        "10:03");

    event.registerAttendee(
        "David",
        "10:04");

    // Cancel Alice
    event.cancelRegistration(1);

    // Charlie should be promoted
    assert(event.getConfirmedCount() == 2);

    // David should remain on waitlist
    assert(event.getWaitlistCount() == 1);

    assert(event.getNextWaitlistId() == 4);

    cout << "[PASS] Waitlist promotion test\n";
}

// ============================================
// TEST 5: Cancellation
// ============================================

void testCancellation()
{

    EventSeatAllocator event(2);

    event.registerAttendee(
        "Alice",
        "10:01");

    event.registerAttendee(
        "Bob",
        "10:02");

    // Cancel Alice
    event.cancelRegistration(1);

    // Only Bob should remain
    assert(event.getConfirmedCount() == 1);

    // No waitlist
    assert(event.getWaitlistCount() == 0);

    cout << "[PASS] Cancellation test\n";
}

// ============================================
// TEST RUNNER
// ============================================

int main()
{

    cout << "====================================\n";

    cout << "       EVENT ALLOCATION TESTS\n";

    cout << "====================================\n\n";

    testSeatAllocation();

    testWaitlist();

    testPriorityQueue();

    testWaitlistPromotion();

    testCancellation();

    cout << "\n====================================\n";

    cout << "All tests passed successfully!\n";

    cout << "====================================\n";

    return 0;
}