#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

// Function to find an augmenting path using BFS
int bfs(int s, int t, vector<int>& parent, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    int n = adj.size();
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

// Function to calculate the maximum flow from source to sink
int maxflow(int s, int t, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    int n = adj.size();
    int flow = 0;
    vector<int> parent(n);

    int new_flow;
    while (new_flow = bfs(s, t, parent, capacity, adj)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    int n;
    cin >> n;

    // Initializing the capacity and adj matrices
    vector<vector<int>> capacity(n, vector<int>(n, 0));
    vector<vector<int>> adj(n);

    int m; // Number of edges
    cin >> m;
      int source, sink; // Assuming you have defined the source and sink nodes.
    cin >> source;

    cin >> sink;
    for (int i = 0; i < m; i++) {
        int from, to, cap;
        cin >> from >> to >> cap;
        capacity[from][to] = cap;
        adj[from].push_back(to);
        adj[to].push_back(from); 

  

    int max_flow = maxflow(source, sink, capacity, adj);

    cout << "Maximum Flow: " << max_flow << endl;

    return 0;
}
