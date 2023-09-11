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
vector<int> findMinCut(int s, vector<vector<int>>& capacity, vector<vector<int>>& adj,vector<vector<int>>&org,int size) {
    int n = adj.size();
    vector<bool> visited(n, false);
    // Perform DFS from the source node to mark reachable nodes in the residual graph
    dfs(s, capacity, adj, visited);
    // Print the minimum cut edges and nodes
    vector<int>vertices;

    for(int i=0;i<size;i++)
    {
        if(visited[i]==true)
        {
             vertices.push_back(i);
        }
    }
    return vertices;
}
int findTotalMatch(vector<int>&vertics,vector<vector<int>>&matches,int n)
{
    sort(vertics.begin(),vertics.end());
    int total=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(binary_search(vertics.begin(),vertics.end(),i)==true && binary_search(vertics.begin(),vertics.end(),j)==true)
            {
                  total+=matches[i][j];
            }
          

        }
    }
    total=total/2;
    return total;

}
int main()
{
    map<int,string>m;
    int count=0;
    int n;
    cin>>n;
    vector<int>win(n,0);
    vector<int>lose(n,0);
    vector<int>remain(n,0);
    vector<vector<int>>matches(n,vector<int>(n,0));
    for(int i=0;i<n;i++)
    {
        string s;
        int w,l,r;
        cin>>s>>w>>l>>r;
        m[i]=s;
        win[i]=w;
        lose[i]=l;
        remain[i]=r;
        for(int j=0;j<n;j++)
        {
            int x;
            cin>>x;
            matches[i][j]=x;
        }

    }
    for(int x=0;x<n;x++)
    {
        bool impossible=false;
        int impossibleIndex=-1;
        int k=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                
                if(i==x || j==x) continue;
                if(matches[i][j]==0) continue;
                k++;
            }
        }
        int num=k/2;
        int node=num+2+n;

        int s=n;
        int t=n+1;
        vector<vector<int>>capacity(node,vector<int>(node,0));
        vector<vector<int>>adj(node);
        int to=n+2;
        int from=n;
         for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                
                if(i==x || j==x) continue;
                if(matches[i][j]==0) continue;
                if(i>j) continue;
                capacity[from][to]=matches[i][j];
                capacity[to][i]=INF;
                capacity[to][j]=INF;
                adj[to].push_back(i);
                adj[i].push_back(to);
                adj[to].push_back(j);
                adj[j].push_back(to);
                adj[from].push_back(to);
                adj[to].push_back(from);
                to++;
                k++;
            }
        }
        for(int l=0;l<n;l++)
        {
            if(l==x) continue;
            int cap=win[x]+remain[x]-win[l];
            if(cap<0)
            {
                impossible=true;
                impossibleIndex=l;

            }
            cap=max(cap,0);
            capacity[l][t]=cap;
            adj[l].push_back(t);
            adj[t].push_back(l);

        }

        //  for(int i=0;i<capacity.size();i++)
        // {
        //     for(int j=0;j<capacity[i].size();j++)
        //     {
        //         cout<<capacity[i][j]<<" ";

        //     }
        //     cout<<endl;
        // }
        vector<vector<int>>org=capacity;
        int flow=maxFlow(s,t,capacity,adj);
        // for(int i=0;i<capacity.size();i++)
        // {
        //     for(int j=0;j<capacity[i].size();j++)
        //     {
        //         cout<<capacity[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
        bool eliminated=false;
        for(int child:capacity[s])
        {
            if(child!=0)
            {
                eliminated=true;
                break;
            }
        }
        if(impossible==true) eliminated=true;
        if(eliminated)
        {
            string team=m[x];
            cout<<team<<" is "<<"eliminated."<<endl;
            int total=win[x]+remain[x];
          vector<int>vertices;
          if(!impossible) vertices=  findMinCut(s,capacity,adj,org,n);
          else vertices.push_back(impossibleIndex);
          int totalMatch=findTotalMatch(vertices,matches,n);
          int totalWon=0;

          for(int i=0;i<vertices.size();i++)
          {
            totalWon+=win[vertices[i]];
          }
            cout<<"They can win at most "<<win[x]<<" + "<<remain[x]<<" = "<<total<<" games."<<endl;
            for(int i=0;i<vertices.size()-1;i++)
            {
              if(i!=vertices.size()-2)  cout<<m[vertices[i]]<<" ,";
              else cout<<m[vertices[i]]<<"";
            }
            if(vertices.size()>1) cout<<" and ";
            if(vertices.size()>1) cout<<m[vertices[vertices.size()-1]]<<" have won a total of "<<totalWon<<" games."<<endl;
            else cout<<m[vertices[vertices.size()-1]]<<" has won a total of "<<totalWon<<" games."<<endl;
            cout<<"They play each other "<<totalMatch<<" times."<<endl;
            cout<<"So on average, each of the teams in this group wins ";
            int match=totalWon+totalMatch;
            int n=vertices.size();
            double ans=(double)match/n;
            cout<<match<<"/"<<n<<" = "<<ans<<" games."<<endl;
            cout<<endl;
            
            }
            

       


    }





}