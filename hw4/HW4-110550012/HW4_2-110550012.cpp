#include <bits/stdc++.h>
using namespace std;
set<int> ans;
void DFS(vector<vector<int> > &adj, int u, vector<bool> &visited, vector<int> &disc, vector<int> &low, int &time, int parent)
{
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;
    for (auto v : adj[u])
    {
        if (!visited[v])
        {
            ++children;
            DFS(adj, v, visited, disc, low, time, u);
            low[u] = min(low[u], low[v]);
            if (parent != -1 && low[v] >= disc[u])
                ans.insert(u);
        }
        else if (v != parent)
            low[u] = min(low[u], disc[v]);
    }
    if (parent == -1 && children > 1) //root && children>=2
        ans.insert(u);
}

int main()
{
    int V, E;
    cin >> V >> E;
    vector<vector<int> > adj(V);
    int a, b;
    for (int i = 0; i < E; ++i)
    {
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }

    vector<int> disc(V, 0); // discovery times
    vector<int> low(V);
    vector<bool> visited(V, false);
    int time = 0, parent = -1;
    DFS(adj, 0, visited, disc, low, time, parent);

    cout<<ans.size()<<'\n';
    for(auto i:ans)
        cout<<i + 1<<' ';
    cout<<'\n';
    return 0;
}
