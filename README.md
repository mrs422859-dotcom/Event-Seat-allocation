# Event Seat Allocation Engine

A C++ implementation of an automated event seat allocation system using
a **Priority Queue (Min-Heap)** for waitlist management.

## Task

**SoarJMI Technical Society --- Task 2.3: Automated Event Seat
Allocation Engine**

The program manages event seat capacity, automatically places excess
registrations into a waitlist, promotes the earliest waitlisted attendee
when a confirmed seat becomes available, and exports the attendee
manifest to CSV.

## Features

-   Set the total number of event seats.
-   Register attendees.
-   Automatically confirm attendees while seats are available.
-   Automatically add additional attendees to a waitlist.
-   Use a `priority_queue` (heap) to maintain waitlist priority.
-   Give priority to attendees who registered earlier.
-   Cancel a confirmed registration.
-   Automatically promote the earliest waitlisted attendee after
    cancellation.
-   Display confirmed attendees.
-   Display the waitlist.
-   Export the final attendee manifest to a CSV file.
-   Includes C++ test cases for the main allocation logic.

## Project Structure

``` text
Soar_Jmi_Task_2.3/
│
├── main.cpp
├── event_allocator.h
├── event_allocator.cpp
├── tests.cpp
├── README.md
└── attendees.csv        # Generated after CSV export
```

## How It Works

### 1. Seat Allocation

When an attendee registers:

``` text
             Registration
                   |
                   v
          Are seats available?
             /           \
           Yes            No
            |              |
            v              v
       CONFIRMED        WAITLIST
                           |
                           v
                    Priority Queue
```

If the event has 5 seats, the first 5 registrations are confirmed.
Further registrations are placed in the waitlist.

### 2. Waitlist Priority

The waitlist is implemented using:

``` cpp
priority_queue<
    Attendee,
    vector<Attendee>,
    CompareAttendee
>
```

The comparator gives higher priority to the attendee with the smaller
registration ID.

Since IDs are assigned in registration order:

``` text
ID 1 → registered first
ID 2 → registered second
ID 3 → registered third
...
```

the earliest registration is always at the top of the heap.

### 3. Cancellation and Promotion

When a confirmed attendee cancels:

``` text
Confirmed seat becomes available
            |
            v
     Is waitlist empty?
        /          \
      Yes           No
       |             |
       v             v
   Keep seat     Remove top
                 of priority queue
                       |
                       v
                  Confirm attendee
```

The earliest person in the waitlist is automatically promoted.

## Data Structures Used

### `vector`

A `vector<Attendee>` stores confirmed attendees.

``` cpp
vector<Attendee> confirmed;
```

### `priority_queue`

A `priority_queue` stores waitlisted attendees.

``` cpp
priority_queue<
    Attendee,
    vector<Attendee>,
    CompareAttendee
> waitlist;
```

This provides heap-based priority management.

## Time Complexity

Let:

-   `C` = number of confirmed attendees
-   `W` = number of waitlisted attendees

  Operation                              Time Complexity
  ----------------------------------- ------------------
  Register when a seat is available     `O(1)` amortized
  Add attendee to waitlist                    `O(log W)`
  Get next waitlisted attendee                    `O(1)`
  Remove next waitlisted attendee             `O(log W)`
  Cancel confirmed attendee                       `O(C)`
  Promote from waitlist                       `O(log W)`
  Display confirmed attendees                     `O(C)`
  Display waitlist                          `O(W log W)`
  Export CSV                            `O(C + W log W)`

### Why is displaying/exporting the waitlist `O(W log W)`?

`priority_queue` does not provide direct iteration in priority order.
The implementation therefore makes a copy of the heap and repeatedly
calls:

``` cpp
top()
pop()
```

Each `pop()` takes `O(log W)`, resulting in `O(W log W)` overall.

## Space Complexity

The main data structures store all attendees:

``` text
Confirmed attendees → O(C)
Waitlist             → O(W)
```

Therefore, the main space complexity is:

``` text
O(C + W)
```

The display/export operations temporarily copy the waitlist, requiring
additional `O(W)` space.

## Compilation

Make sure all source files are in the same directory.

### Compile the main program

``` powershell
g++ main.cpp event_allocator.cpp -o event_allocator.exe
```

Run:

``` powershell
.\event_allocator.exe
```

### Compile the tests

``` powershell
g++ tests.cpp event_allocator.cpp -o tests.exe
```

Run:

``` powershell
.\tests.exe
```

## Example

Suppose the event has:

``` text
Total seats: 3
```

Registrations:

``` text
1. Alice   10:01
2. Bob     10:02
3. Charlie 10:03
4. David   10:04
5. Esha    10:05
```

The allocation becomes:

``` text
CONFIRMED
---------
Alice
Bob
Charlie

WAITLIST
--------
David
Esha
```

If Alice cancels:

``` text
Alice → CANCELLED
David → CONFIRMED
Esha  → WAITLIST
```

The system performs this promotion automatically.

## CSV Output

Selecting **Export Attendee Manifest** creates:

``` text
attendees.csv
```

with the following format:

``` csv
ID,Name,Registration Timestamp,Status
1,Alice,10:01,CONFIRMED
2,Bob,10:02,CONFIRMED
3,Charlie,10:03,CONFIRMED
4,David,10:04,WAITLIST
5,Esha,10:05,WAITLIST
```

## Testing

The test program checks:

1.  Seat allocation.
2.  Waitlist creation.
3.  Priority queue ordering.
4.  Automatic waitlist promotion.
5.  Cancellation when the waitlist is empty.

Successful execution should show:

``` text
[PASS] Seat allocation test
[PASS] Waitlist test
[PASS] Priority queue ordering test
[PASS] Waitlist promotion test
[PASS] Cancellation test

All tests passed successfully!
```

## Technologies

-   **Language:** C++
-   **Compiler:** g++
-   **Data Structure:** `vector`, `priority_queue`
-   **Output Format:** CSV
-   **Testing:** C++ `assert`

## Author

Mohd Saif

SoarJMI Technical Society --- Task 2.3
