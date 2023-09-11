#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to;
    long flow, capacity;

    Edge(int from, int to, long capacity) : from(from), to(to), flow(0), capacity(capacity) {}

    long remainingCapacity() const {
        return capacity - flow;
    }

    void augment(long bottleNeck) {
        flow += bottleNeck;
    }
};

class FordFulkersonDfsSolverAdjacencyList {
private:
    const long INF = 1e9;
    int n, s, t;
    vector<vector<Edge>> graph;
    vector<bool> visited;
    long maxFlow;

public:
    FordFulkersonDfsSolverAdjacencyList(int n, int s, int t) : n(n), s(s), t(t), graph(n), visited(n), maxFlow(0) {}

    void addEdge(int from, int to, long capacity) {
        Edge forwardEdge(from, to, capacity);
        Edge backwardEdge(to, from, 0);
        graph[from].push_back(forwardEdge);
        graph[to].push_back(backwardEdge);
    }

    void markAllNodesAsUnvisited() {
        fill(visited.begin(), visited.end(), false);
    }

    long dfs(int node, long flow) {
        if (node == t) return flow;

        visited[node] = true;
        for (Edge& edge : graph[node]) {
            if (!visited[edge.to] && edge.remainingCapacity() > 0) {
                long bottleNeck = dfs(edge.to, min(flow, edge.remainingCapacity()));

                if (bottleNeck > 0) {
                    edge.augment(bottleNeck);
                    return bottleNeck;
                }
            }
        }
        return 0;
    }

    void solve() {
        for (long f = dfs(s, INF); f != 0; f = dfs(s, INF)) {
            markAllNodesAsUnvisited();
            maxFlow += f;
        }
    }

    long getMaxFlow() const {
        return maxFlow;
    }
};

int main() {
    int n = 12;
    int s = n - 2;
    int t = n - 1;

    FordFulkersonDfsSolverAdjacencyList solver(n, s, t);

    solver.addEdge(s, 1, 2);
    solver.addEdge(s, 2, 1);
    solver.addEdge(s, 0, 7);

    solver.addEdge(0, 3, 2);
    solver.addEdge(0, 4, 4);

    solver.addEdge(1, 4, 5);
    solver.addEdge(1, 5, 6);

    solver.addEdge(2, 3, 4);
    solver.addEdge(2, 7, 8);

    solver.addEdge(3, 6, 7);
    solver.addEdge(3, 7, 1);

    solver.addEdge(4, 5, 8);
    solver.addEdge(4, 8, 3);

    solver.addEdge(5, 8, 3);

    solver.addEdge(6, t, 1);
    solver.addEdge(7, t, 3);
    solver.addEdge(8, t, 4);

    solver.solve();

    cout << solver.getMaxFlow() << endl;

    return 0;
}
