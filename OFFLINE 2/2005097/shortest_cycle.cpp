#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;
const int INF = 1e9 + 10;
vector<vector<pair<int, int>>> graph(N);
vector<int> dist(N, INF);
vector<int> parent(N, -1);
int shortestCycle = INF; // Variable to track the shortest cycle length

void dijkstra(int source)
{
    vector<bool> visited(N, false);
    set<pair<int, int>> s;
    s.insert({0, source});
    dist[source] = 0;
    while (!s.empty())
    {
        auto node = *s.begin();
        int wt = node.first;
        int v = node.second;
        s.erase(s.begin());
        if (visited[v])
            continue;
        visited[v] = true;
        for (auto child : graph[v])
        {
            long long int child_v = child.first;
            long long int child_w = child.second;
            if ((dist[v] + child_w) < dist[child_v])
            {
                dist[child_v] = dist[v] + child_w;
                s.insert({dist[child_v], child_v});
                parent[child_v] = v;
            }
            // Check for a cycle
            if (visited[child_v] && parent[v] != child_v)
            {
                int cycleLength = dist[v] + child_w + dist[child_v];
                shortestCycle = min(shortestCycle, cycleLength);
            }
        }
    }
}

int findShortestCycle(int n)
{
    shortestCycle = INF;
    for (int i = 0; i < n; i++)
    {
        fill(dist.begin(), dist.end(), INF);
        fill(parent.begin(), parent.end(), -1);
        dijkstra(i);
    }
    return (shortestCycle == INF) ? -1 : shortestCycle;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // Undirected graph
    }

    int shortestCycleLength = findShortestCycle(n);
    cout << "Shortest cycle length: " << shortestCycleLength << endl;

    return 0;
}
