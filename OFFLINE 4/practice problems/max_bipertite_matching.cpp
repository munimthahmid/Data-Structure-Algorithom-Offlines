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
    vector<int>path;
    while(newflow=bfs(s,t,parent,capacity,adj))
    {
        flow+=newflow;
        int cur=t;
        while(cur!=s)
        {
            path.push_back(cur);
            int prev=parent[cur];
            capacity[prev][cur]-=newflow;
            capacity[cur][prev]+=newflow;
            cur=prev;
        }
        path.push_back(s);
    reverse(path.begin(),path.end());
    for(int i=0;i<path.size();i++)
    {
        cout<<path[i]<<" ";
    }
    cout<<endl;
    path.clear();
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
    int applicant,job;
    cin>>applicant>>job;
    int node=applicant+job+2;
    int s=job;
    int t=job+1;
    vector<vector<int>>capacity(node,vector<int>(node,0));
    vector<vector<int>>adj(node);
    int from=job+2;

    for(int i=0;i<applicant;i++)
    {
        int x;
        cin>>x;
        for(int i=0;i<x;i++)
        {
        int u;
        cin>>u;
        adj[from].push_back(u-1);
        adj[u-1].push_back(from);
        capacity[from][u-1]=1;
        adj[s].push_back(from);
        adj[from].push_back(s);
        capacity[s][from]=1;
        }
        from++;
    }

    for(int i=0;i<job;i++)
    {
        adj[i].push_back(t);
        adj[t].push_back(i);
        capacity[i][t]=1;
    }
    int ans=maxFlow(s,t,capacity,adj);
    cout<<ans<<endl;
}