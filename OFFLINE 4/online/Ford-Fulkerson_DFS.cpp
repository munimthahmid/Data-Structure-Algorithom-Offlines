#include <bits/stdc++.h>
using namespace std;
const int INF=1e9+10;
int bfs(int s,int t ,vector<int>&parent,vector<vector<int>>&capacity,vector<vector<int>>&adj)
{
    int n=adj.size();
    fill(parent.begin(),parent.end(),-1);
    parent[s]=-2;
    queue<pair<int,int>>q;
    q.push({s,INF});
    

    while(!q.empty())
    {
        int cur=q.front().first;
        int flow=q.front().second;
        q.pop();
        for(int child:adj[cur])
        {
            if(parent[child]==-1 && capacity[cur][child] )
            {
                int newflow=min(flow,capacity[cur][child]);
                parent[child]=cur;
                if(child==t) return newflow;
                q.push({child,newflow});
            }

        }
    }
    return 0;
}
int maxFlow(int s,int t ,vector<vector<int>>&capacity,vector<vector<int>>&adj)
{
    int flow=0;
    int n=adj.size();
    vector<int>parent(n);

    int newflow;
    while(newflow=bfs(s,t,parent,capacity,adj))
    {
        flow+=newflow;
        int cur=t;
        while(cur!=s)
        {
            int prev=parent[cur];
            capacity[prev][cur]-=newflow;
            capacity[cur][prev]+=newflow;
            cur=prev;
        }
    }
    return flow;
}
void dfs(int node, vector<vector<int>>& capacity, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    for (int next : adj[node]) {
        if (!visited[next] && capacity[node][next] > 0) {
            dfs(next, capacity, adj, visited);
        }
    }
}

void findMinCut(int s, vector<vector<int>>& capacity, vector<vector<int>>& adj,vector<vector<int>>&org) {
    int n = adj.size();
    vector<bool> visited(n, false);
    dfs(s, capacity, adj, visited);
    for(int i=0;i<n;i++)
    {
        if(visited[i]) cout<<"visited: "<<i<<endl;
    }

    cout << "Minimum Cut Edges:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j=0;j<n;j++) {
            if (visited[i] && !visited[j] && org[i][j]>0) {
                cout << i << " -> " << j << endl;
            }
        }
    }
}

int main()
{
    int n,m;
    int s,t;
    cin>>n>>m;
    cin>>s>>t;
    vector<vector<int>>capacity(n,vector<int>(n,0));
    vector<vector<int>>adj(n);

    for(int i=0;i<m;i++)
    {
        int from,to,cap;
        cin>>from>>to>>cap;
        capacity[from][to]=cap;
        adj[from].push_back(to);
        adj[to].push_back(from);

    }
    vector<vector<int>> orgcap= capacity;

     int max_flow = maxFlow(s, t, capacity, adj);
    cout << "Maximum Flow: " << max_flow << endl;
    for(int i=0;i<capacity.size();i++)
    {
        for(int j=0;j<capacity[i].size();j++)
        {
            cout<<i<<" "<<j<<" "<<capacity[i][j]<<endl;
        }
    }

        findMinCut(s, capacity, adj,orgcap);


    return 0;
}