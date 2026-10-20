
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Course {
    string name;
    vector<int> students;
    int slot;
};

int main() {
    int n;
    cout << "=== University Exam Timetable Scheduler ===\n";
    cout << "Enter number of courses: ";
    cin >> n;

    vector<Course> courses(n);

    // Enter course names and enrolled students
    for (int i = 0; i < n; i++) {
        cout << "\nEnter course name: ";
        cin >> courses[i].name;

        int count;
        cout << "Enter number of students in "
             << courses[i].name << ": ";
        cin >> count;

        cout << "Enter student IDs: ";
        for (int j = 0; j < count; j++) {
            int id;
            cin >> id;
            courses[i].students.push_back(id);
        }

        courses[i].slot = -1;
    }

    // Build conflict graph
    vector<vector<int>> graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            bool conflict = false;

            for (int a : courses[i].students) {
                for (int b : courses[j].students) {
                    if (a == b) {
                        conflict = true;
                        break;
                    }
                }
                if (conflict) break;
            }

            if (conflict) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    // Greedy graph coloring
    int maxSlot = 0;

    for (int i = 0; i < n; i++) {
        vector<bool> used(n, false);

        for (int neighbor : graph[i]) {
            if (courses[neighbor].slot != -1) {
                used[courses[neighbor].slot] = true;
            }
        }

        int slot = 0;
        while (used[slot]) {
            slot++;
        }

        courses[i].slot = slot;
        maxSlot = max(maxSlot, slot + 1);
    }

    // Display timetable
    cout << "\n===== EXAM TIMETABLE =====\n";

    for (int i = 0; i < n; i++) {
        cout << courses[i].name
             << " -> Exam Slot "
             << courses[i].slot + 1 << endl;
    }

    cout << "\nTotal exam slots required: "
         << maxSlot << endl;

    return 0;
}
