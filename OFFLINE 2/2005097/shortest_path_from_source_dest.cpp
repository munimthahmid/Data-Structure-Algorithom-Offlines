#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;
const int INF = 1e9 + 10;

vector<vector<pair<int, int>>> graph(N);
vector<int> distPos(N, INF);
vector<int> distNeg(N, INF);

void addEdge(int u, int v, int w)
{
    graph[u].push_back({v, w});
    graph[v].push_back({u, -w});
}

void dijkstra(int source, vector<int> &dist, bool positive)
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

            if (positive && child_w < 0)
                continue;
            if (!positive && child_w > 0)
                continue;

            if ((dist[v] + child_w) < dist[child_v])
            {
                dist[child_v] = dist[v] + child_w;
                s.insert({dist[child_v], child_v});
            }
        }
    }
}

int shortestPath(int source, int destination)
{
    fill(distPos.begin(), distPos.end(), INF);
    fill(distNeg.begin(), distNeg.end(), INF);

    dijkstra(source, distPos, true);
    dijkstra(source, distNeg, false);

    int shortestDistance = INF;

    for (int v = 0; v < N; v++)
    {
        if (distPos[v] != INF && distNeg[v] != INF)
        {
            int distance = distPos[v] + distNeg[v];
            shortestDistance = min(shortestDistance, distance);
        }
    }

    if (shortestDistance == INF)
        return -1;

    return shortestDistance;
}

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    int source, destination;
    cin >> source >> destination;

    int shortestDistance = shortestPath(source, destination);

    cout << "Shortest path with changing weight differences: " << shortestDistance << endl;

    return 0;
}
