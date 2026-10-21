
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Structure to store course details
struct Course {
    string name;           // Name of the course
    vector<int> students;  // Enrolled student IDs
    int slot;              // Assigned exam slot
};

// Check whether a slot can be assigned to a course
bool isSafe(int course, int slot,
            vector<vector<int>>& graph,
            vector<Course>& courses) {

    // Check all neighboring courses
    for (int neighbor : graph[course]) {

        // If a neighboring course has the same slot,
        // assigning this slot would create a conflict
        if (courses[neighbor].slot == slot) {
            return false;
        }
    }

    // No conflict found
    return true;
}

// Solve the timetable using backtracking
bool graphColoring(int course, int n, int maxSlots,
                   vector<vector<int>>& graph,
                   vector<Course>& courses) {

    // Base case: all courses have been assigned slots
    if (course == n) {
        return true;
    }

    // Try each available exam slot
    for (int slot = 0; slot < maxSlots; slot++) {

        // Assign the slot only if it is safe
        if (isSafe(course, slot, graph, courses)) {

            courses[course].slot = slot;

            // Recursively assign slots to remaining courses
            if (graphColoring(course + 1, n, maxSlots,
                              graph, courses)) {
                return true;
            }

            // Backtrack: undo the assignment if it fails
            courses[course].slot = -1;
        }
    }

    // No valid slot could be assigned
    return false;
}

int main() {
    int n;

    cout << "=== University Exam Timetable Scheduler ===\n";
    cout << "Enter number of courses: ";
    cin >> n;

    // Create the list of courses
    vector<Course> courses(n);

    // Input course names and enrolled students
    for (int i = 0; i < n; i++) {
        cout << "\nEnter course name: ";
        cin >> courses[i].name;

        int count;
        cout << "Enter number of students in "
             << courses[i].name << ": ";
        cin >> count;

        cout << "Enter student IDs: ";

        // Store student IDs for this course
        for (int j = 0; j < count; j++) {
            int id;
            cin >> id;
            courses[i].students.push_back(id);
        }

        // Initially, no exam slot is assigned
        courses[i].slot = -1;
    }

    // Build the conflict graph
    // An edge connects courses sharing at least one student
    vector<vector<int>> graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            bool conflict = false;

            // Check whether the courses share a student
            for (int a : courses[i].students) {
                for (int b : courses[j].students) {
                    if (a == b) {
                        conflict = true;
                        break;
                    }
                }

                if (conflict) {
                    break;
                }
            }

            // Add an edge if the courses conflict
            if (conflict) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    // Try increasing numbers of exam slots
    // The first successful solution uses the minimum slots
    int minSlots = 0;
    bool success = false;

    for (int slots = 1; slots <= n; slots++) {

        // Reset assignments before each attempt
        for (int i = 0; i < n; i++) {
            courses[i].slot = -1;
        }

        // Check whether all courses can fit into these slots
        if (graphColoring(0, n, slots, graph, courses)) {
            minSlots = slots;
            success = true;
            break;
        }
    }

    // Display the timetable
    if (success) {
        cout << "\n===== EXAM TIMETABLE =====\n";

        for (int i = 0; i < n; i++) {
            cout << courses[i].name
                 << " -> Exam Slot "
                 << courses[i].slot + 1 << endl;
        }

        cout << "\nMinimum exam slots required: "
             << minSlots << endl;
    } else {
        cout << "No valid timetable exists.\n";
    }

    return 0;
}
