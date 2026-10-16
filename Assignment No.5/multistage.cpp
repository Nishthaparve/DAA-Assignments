#include <iostream>
#include <vector>
using namespace std;

const int INF = 999999;

int main() {
    int n, m;

    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<int>> cost(n, vector<int>(n, INF));

    cout << "Enter edges (from to cost):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        cost[u][v] = w;
    }

    vector<int> dist(n, INF);
    vector<int> next(n, -1);

    // Destination is the last vertex
    dist[n - 1] = 0;

    // Calculate minimum cost from each vertex
    for (int u = n - 2; u >= 0; u--) {
        for (int v = u + 1; v < n; v++) {
            if (cost[u][v] != INF && dist[v] != INF) {
                if (cost[u][v] + dist[v] < dist[u]) {
                    dist[u] = cost[u][v] + dist[v];
                    next[u] = v;
                }
            }
        }
    }

    if (dist[0] == INF) {
        cout << "No path exists!\n";
        return 0;
    }

    cout << "\nMinimum delivery cost: " << dist[0] << endl;

    cout << "Optimal path: ";
    int current = 0;

    while (current != -1) {
        cout << current;
        if (current == n - 1)
            break;

        cout << " -> ";
        current = next[current];
    }

    cout << endl;

    return 0;
}
