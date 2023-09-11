#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9; // Use a double for edge weights

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
        cout<<graph[u][v]<<endl;
        mstGraph[u][v]=graph[u][v];
        mstGraph[v][u]=graph[v][u];
    }

    return mstGraph;
}
void dfs(int current, vector<bool>& visited,vector<int>&vertices,vector<vector<int>>&graph)
{
    
    cout << current << " ";
    vertices.push_back(current);
 
    // Set current node as visited
    visited[current] = true;
 
    // For every node of the graph
    for (int i = 0; i < graph[current].size(); i++) {
 
        // If some node is adjacent to the current node
        // and it has not already been visited
        if (graph[current][i] != INF && (!visited[i])) {
            dfs(i, visited,vertices,graph);
        }
    }
}
void backdfs(int current,int final, vector<bool>& visited,vector<int>&backvertices,vector<vector<int>>&graph)
{
    
    backvertices.push_back(current);
 
    // Set current node as visited
    visited[current] = true;
 
    // For every node of the graph
    for (int i = 0; i < graph[current].size(); i++) {
 
        // If some node is adjacent to the current node
        // and it has not already been visited
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
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n, vector<int>(n, INF)); // Initialize as a double matrix

    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w;
    }

    vector<vector<int>>mstgraph= PrimsAlgo(graph);
    vector<int>vertices;
    vector<bool>visited(100,false);
    dfs(0,visited,vertices,graph);
    vector<int>backvertices;
    for(int i=0;i<visited.size();i++)
    {
        visited[i]=false;
    }
    cout<<endl;

    backdfs(vertices.back(),0,visited,backvertices,graph);
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
    for(int i=0;i<vertices.size();i++){
        cout<<vertices[i]<<" ";
    }
    cout<<endl;
    vertices=deleteDuplicate(vertices);
    for(int i=0;i<vertices.size();i++)
    {
        cout<<vertices[i]<<" ";
    }
    cout<<endl;


}
