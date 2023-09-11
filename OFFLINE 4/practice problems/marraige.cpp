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
                if(child==t) {
                    
                    return newflow;}
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
        int n,m;
        cin>>n>>m;
        vector<vector<int>>man;
        vector<vector<int>>women;
        for(int i=0;i<n;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            vector<int>temp;
            temp.push_back(u);
            temp.push_back(v);
            temp.push_back(w);
            man.push_back(temp);

        }
           for(int i=0;i<m;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            vector<int>temp;
            temp.push_back(u);
            temp.push_back(v);
            temp.push_back(w);
            women.push_back(temp);
        }
        int node=n+m+2;
        int s=n+m;
        int t=n+m+1;
        vector<vector<int>>capacity(node,vector<int>(n,0));
        vector<vector<int>>adj(node);
        for(int i=0;i<n;i++)
        {
            int m_height=man[i][0];
            int m_year=man[i][1];
            int m_div=man[i][2];
            for(int j=0;j<m;j++)
            {
                 int wm_height=women[j][0];
                int wm_year=women[j][1];
                int wm_div=women[j][2];
            if(abs(m_height-wm_height)<=12 &&abs(m_year-wm_year)>=5 && m_div==wm_div)
            {
             int a=i;
             int b=n+i;
             capacity[s][a]=1;
             adj[s].push_back(a);
             adj[a].push_back(s);
             adj[a].push_back(b);
             capacity[a][b]=1;
             adj[b].push_back(a);

             adj[b].push_back(t);
             adj[t].push_back(b);
             capacity[b][t]=1;
            }

            }
        }
        int ans=maxFlow(s,t,capacity,adj);
        cout<<ans<<endl;






    }
}