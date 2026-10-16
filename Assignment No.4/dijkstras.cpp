
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int INF = INT_MAX;

void dijkstra(int source, int n,
              vector<vector<pair<int, int>>>& graph) {
    vector<int> dist(n, INF);
    vector<int> parent(n, -1);

    priority_queue<pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nShortest travel time from S:\n";

    for (int i = 0; i < n; i++) {
        cout << "Node " << i << " : ";

        if (dist[i] == INF)
            cout << "Not reachable\n";
        else
            cout << dist[i] << " minutes\n";
    }

    int hospital;
    cout << "\nEnter hospital destination node: ";
    cin >> hospital;

    if (hospital < 0 || hospital >= n ||
        dist[hospital] == INF) {
        cout << "Hospital is not reachable!\n";
        return;
    }

    vector<int> path;
    for (int v = hospital; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    cout << "Shortest path: ";
    for (int node : path)
        cout << node << " ";

    cout << "\nTotal travel time: "
         << dist[hospital] << " minutes\n";
}

int main() {
    int n, m;

    cout << "Enter number of intersections: ";
    cin >> n;

    vector<vector<pair<int, int>>> graph(n);

    cout << "Enter number of roads: ";
    cin >> m;

    cout << "Enter roads as: from to travel_time\n";

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int choice;
    cout << "\n1. Find shortest path\n";
    cout << "2. Update traffic and find path again\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 2) {
        int u, v, newTime;
        cout << "Enter road (u v) and new travel time: ";
        cin >> u >> v >> newTime;

        // Update road in both directions
        for (auto &edge : graph[u])
            if (edge.first == v)
                edge.second = newTime;

        for (auto &edge : graph[v])
            if (edge.first == u)
                edge.second = newTime;
    }

    dijkstra(0, n, graph);

    return 0;
}
