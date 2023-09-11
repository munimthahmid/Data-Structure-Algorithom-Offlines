#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to;
    long long capacity, flow;
};

class FordFulkersonDfsSolverAdjacencyList {
private:
    int n, s, t;
    vector<vector<Edge>> graph;
    vector<bool> visited;
    long long maxFlow;
    const long long INF = 1e18;

public:
    FordFulkersonDfsSolverAdjacencyList(int n, int s, int t) : n(n), s(s), t(t), graph(n), visited(n), maxFlow(0) {}

    void addEdge(int from, int to, long long capacity) {
        graph[from].push_back({from, to, capacity, 0});
        graph[to].push_back({to, from, 0, 0});
    }

    bool dfs(int node, long long flow) {
        if (node == t) return flow;

        visited[node] = true;

        for (Edge& edge : graph[node]) {
            if (!visited[edge.to] && edge.capacity > edge.flow) {
                long long bottleNeck = dfs(edge.to, min(flow, edge.capacity - edge.flow));

                if (bottleNeck > 0) {
                    edge.flow += bottleNeck;
                    graph[edge.to][edge.from].flow -= bottleNeck;
                    return bottleNeck;
                }
            }
        }
        return 0;
    }

    void markAllNodesAsUnvisited() {
        fill(visited.begin(), visited.end(), false);
    }

    void solve() {
        for (long long f = dfs(s, INF); f != 0; f = dfs(s, INF)) {
            markAllNodesAsUnvisited();
            maxFlow += f;
        }
    }

    long long getMaxFlow() const {
        return maxFlow;
    }
};

/* Example */

int main() {
    // Example graph from the slides
    int n = 6;
    int s = 0;
    int t = 5;

    FordFulkersonDfsSolverAdjacencyList solver(n, s, t);

    solver.addEdge(s, 1, 10);
    solver.addEdge(1, 3, 10);
    solver.addEdge(1, 3, 2);
    solver.addEdge(1, 2, 4);
    solver.addEdge(1, 4, 8);

    solver.addEdge(4, 2, 6);
    solver.addEdge(2, 5, 10);
    solver.addEdge(4, 5, 10);
    solver.addEdge(2, 5, 10);

    solver.solve();
    cout << "Max Flow: " << solver.getMaxFlow() << endl;

    return 0;
}
