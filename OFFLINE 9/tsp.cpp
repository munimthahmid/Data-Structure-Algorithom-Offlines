#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int N=1e5;
vector<int>parent(N);
vector<int>Size(N);
multiset<int>sizes;
class Graph {
public:
    int V; 
    vector<vector<int>> graph;

    Graph(int vertices) {
        V = vertices;
        graph.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        graph[u][v] = weight;
        graph[v][u] = weight; 
    }
};

double Calculate_Tour_Length(const vector<int>& tour, const vector<vector<int>>& graph) {
    double length = 0.0;
    int n = tour.size();

    for (int i = 0; i < n - 1; i++) {
        int u = tour[i];
        int v = tour[i + 1];
        length += graph[u][v];
    }

    int first = tour[0];
    int last = tour[n - 1];
    length += graph[first][last];

    return length;
}
int randomWeight()
{

    return rand()%151+50;
}
Graph Create_Random_Graph(int V) {
    Graph graph(V);

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            int weight = randomWeight();
            if(weight==0)
            {
            }
            graph.addEdge(i, j, weight);
        }
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            for (int k = 0; k < V; k++) {
                if (i != j && j != k && i != k) {
                    int dist_ij = graph.graph[i][j];
                    int dist_ik = graph.graph[i][k];
                    int dist_kj = graph.graph[k][j];

                    if (dist_ij > dist_ik + dist_kj) {
                        graph.graph[i][j] = dist_ik + dist_kj;
                        graph.graph[j][i] = dist_ik + dist_kj; 
                    }
                }
            }
        }
    }

    return graph;
}

vector<vector<int>> PrimsAlgo(vector<vector<int>>& graph) {
    int v = graph.size();
    vector<double> weight(v, INF); 
    vector<int> parent(v, -1);
    vector<bool> inMST(v, false);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    pq.push({0.0, 0});
    weight[0] = 0.0;
    vector<pair<int, int>> edges;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;

        for (int child_v = 0; child_v < v; child_v++) {
            double child_w = graph[u][child_v];

            if (!inMST[child_v] && child_w < weight[child_v]) {
                weight[child_v] = child_w;
                parent[child_v] = u;
                pq.push({child_w, child_v});
            }
        }
    }

    for (int i = 1; i < parent.size(); i++) {
        edges.push_back({parent[i], i});
    }
    vector<vector<int>>mstGraph(graph.size(),vector<int>(graph.size(),0));
    for(int i=0;i<edges.size();i++)
    {
        int u=edges[i].first;
        int v=edges[i].second;
        mstGraph[u][v]=graph[u][v];
        mstGraph[v][u]=graph[v][u];
    }

    return mstGraph;
}
int DFSCount(int v, vector<bool>& visited, const vector<vector<int>>& graph) {
    visited[v] = true;
    int count = 1;
    int n = graph.size();

    for (int i = 0; i < n; i++) {
        if (graph[v][i] > 0 && !visited[i])
            count += DFSCount(i, visited, graph);
    }

    return count;
}

// Function to check if edge u-v can be considered as the next edge in Eulerian Path
bool isValidNextEdge(int u, int v,  vector<vector<int>>& graph) {
    int n = graph.size();
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (graph[u][i] > 0)
            count++;
    }

    if (count == 1)
        return true;

    // If there are multiple edges, do a DFS to check if removing u-v makes a bridge
    vector<bool> tempVisited(n, false);
    int count1 = DFSCount(u, tempVisited, graph);
    graph[u][v] = 0; // Temporarily remove the edge
    tempVisited.assign(n, false);
    int count2 = DFSCount(u, tempVisited, graph);
    graph[u][v] = 1; // Restore the edge

    return (count1 <= count2);
}

vector<int> deleteDuplicate(vector<int>vertices)
{
    vector<bool>visited(vertices.size(),false);
    vector<int>finalVertices;
    for(int i=0;i<vertices.size();i++)
    {
        if(!visited[vertices[i]])
        {
            visited[vertices[i]]=true;
            finalVertices.push_back(vertices[i]);
        }
    }
    finalVertices.push_back(vertices.back());
    return finalVertices;

}
void dfs(int current, vector<bool>& visited,vector<int>&vertices,vector<vector<int>>&graph)
{
    
    vertices.push_back(current);
 
    visited[current] = true;
 
    for (int i = 0; i < graph[current].size(); i++) {
 

        if (graph[current][i] > 0 && (!visited[i])) {
            dfs(i, visited,vertices,graph);
        }
    }
}
void backdfs(int current,int final, vector<bool>& visited,vector<int>&backvertices,vector<vector<int>>&graph)
{
    
    backvertices.push_back(current);
 
    visited[current] = true;
 
    for (int i = 0; i < graph[current].size(); i++) {
 
      
        if (graph[current][i] != INF && (!visited[i])) {
            if(i==final)
            {
                backvertices.push_back(i);
                break;
            }
            backdfs(i,final, visited,backvertices,graph);
        }
    }
}
vector<int> Metric_Approximation_TSP(vector<vector<int>> graph) {
    int n = graph.size();

    // Step 1: Find an MST (Minimum Spanning Tree)
    vector<vector<int>> mst = PrimsAlgo(graph);
    vector<int>vertices;
    vector<bool>visited(mst.size(),false);
    dfs(0,visited,vertices,mst);
    vector<int>backvertices;
    
    backdfs(vertices.back(),0,visited,backvertices,mst);
    for(int i=1;i<backvertices.size();i++)
    {
        if(backvertices[i]!=0)
        {
            vertices.push_back(backvertices[i]);
        }
        else 
        {
             vertices.push_back(backvertices[i]);
             break;
        }
    }
    vertices=deleteDuplicate(vertices); 

    
    return vertices;
}



int Exact_TSP(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));

    dp[1][0] = 0; 

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
    if (mask & (1 << u)) {
        for (int v = 0; v < n; v++) {
            if (mask & (1 << v) && u != v) {
                dp[mask][u] = min(dp[mask][u], dp[mask ^ (1 << u)][v] + graph[v][u]);
            }
        }
    }
}

    }

    int minCost = INF;

    for (int u = 0; u < n; u++) {
    if (u != 0) { 
        minCost = min(minCost, dp[(1 << n) - 1][u] + graph[u][0]);
    }
}
    if(minCost!=INF)
    return minCost;
    else return 0;
}

int main() {
    int t;
    cin >> t;
    srand(time(0));
    for(int i=0;i<t;i++)
    {
        Graph g=Create_Random_Graph(20);
        vector<vector<int>>graph=g.graph;
        int minTSPCost = Exact_TSP(graph);
        vector<int> approximateTour = Metric_Approximation_TSP(graph);

        double approximateCost = Calculate_Tour_Length(approximateTour, graph);

        double ratio = approximateCost / minTSPCost;

        cout << ratio << endl;


    }
    
}
