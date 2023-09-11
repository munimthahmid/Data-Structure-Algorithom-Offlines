#include<bits/stdc++.h>
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
    int t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
          map<int,string>m;
    vector<pair<int,int>>rc;
    int n,g;
    cin>>n>>g;
    for(int i=0;i<n;i++)
    {
        int s,r,c;
        cin>>s>>r>>c;
        m[r]=s;
        rc.push_back({r,c});
        
    }


    }
  
    

}