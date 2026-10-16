
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of courses: ";
    cin >> n;

    cout << "Enter number of conflicts: ";
    cin >> m;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Enter conflicting course pairs (0-based):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    vector<int> color(n, -1);
    color[0] = 0;

    vector<bool> available(n, true);

    // Greedy graph coloring
    for (int u = 1; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (graph[u][v] == 1 && color[v] != -1) {
                available[color[v]] = false;
            }
        }

        int c;
        for (c = 0; c < n; c++) {
            if (available[c])
                break;
        }

        color[u] = c;

        // Reset available colors
        for (int i = 0; i < n; i++) {
            available[i] = true;
        }
    }

    int slots = 0;

    cout << "\nExam Timetable:\n";
    for (int i = 0; i < n; i++) {
        cout << "Course " << i
             << " -> Slot " << color[i] + 1 << endl;

        if (color[i] + 1 > slots)
            slots = color[i] + 1;
    }

    cout << "\nTotal exam slots required: "
         << slots << endl;

    return 0;
}
