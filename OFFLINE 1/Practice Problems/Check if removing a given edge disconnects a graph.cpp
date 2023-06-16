/*
https://www.geeksforgeeks.org/check-removing-given-edge-disconnects-given-graph/
*/
#include<bits/stdc++.h>
using namespace std;
void dfs(int vertex,vector<bool>&visited,vector<int> &graph)
{
    visited[vertex]=true;
    for(int child:graph)
    {
        dfs(child,visited,graph);
    }
}
bool isConnected(vector<int>graph)
{
    int n=graph.size();
    vector<bool>visited(n+1,false);
    dfs(graph.front(),visited,graph);
    bool check=true;
    for(int i=0;i<n;i++)
    {
        if(visited[i]==true) continue;
        else
        {
            check=false;
            break;
        }
    }
    return check;
}
