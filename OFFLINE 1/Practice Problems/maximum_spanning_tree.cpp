/*
Learn more about the problem: https://www.geeksforgeeks.org/maximum-spanning-tree-using-prims-algorithm/

*/
#include<bits/stdc++.h>
using namespace std;


vector<pair<int,int>> PrimsAlgorithm(vector<vector<pair<int,int>>>&graph,int &finalweight)
{
    priority_queue<pair<int,int>>pq;
    int v=graph.size();
    vector<int>weight(v,0);
    vector<int>parent(v,-1);
    vector<bool>inMST(v,false);
    pq.push({0,0});
    weight[0]=0;
    vector<pair<int,int>>edges;
    while(!pq.empty())
    {
        int u=pq.top().second;
        pq.pop();
        inMST[u]=true;
        for(auto child:graph[u])
        {
            int child_v=child.first;
            int child_w=child.second;
            if(!inMST[child_v] && child_w>=weight[child_v])
            {
                weight[child_v]=child_w;
                parent[child_v]=u;
                pq.push({child_w,child_v});

            }
        }
    }
    for(int i=1;i<parent.size();i++)
    {
        finalweight+=weight[i];
        edges.push_back({i,parent[i]});
    }
    return edges;
    
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>>graph(n);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }
    int finalWeight=0;
    vector<pair<int,int>>edges=PrimsAlgorithm(graph,finalWeight);
    cout<<finalWeight<<endl;
}
