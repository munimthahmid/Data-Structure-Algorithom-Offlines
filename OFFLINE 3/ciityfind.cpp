#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    const int INF=1e9+10;
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
            int n, m;
    n=numCourses;
    m=prerequisites.size();
    vector<vector<int>> distance(n, vector<int>(n , INF));
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        u=prerequisites[i][0];
        v=prerequisites[i][1];
        w=1;
        distance[u][v] = w;
        distance[u][u] = 0;
        distance[v][v] = 0;
    }

    for (int k =0; k < n; k++)
    {
        for (int i =0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {

                int cur_dist = distance[i][k] + distance[k][j];
                if(distance[i][k]!=INF && distance[k][j]!=INF)
                distance[i][j] = min(cur_dist, distance[i][j]);
            }
        }
    }
    vector<bool>ans;
    for(int i=0;i<queries.size();i++)
    {
        int u=queries[i][0];
        int v=queries[i][1];
        if(distance[u][v]!=INF) ans.push_back(true);
        else ans.push_back(false);
    }
    return ans;

        
    }
};