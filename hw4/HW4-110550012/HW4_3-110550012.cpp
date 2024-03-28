#include <bits/stdc++.h>
using namespace std;
#define MAX 10000
class Graph
{
private:
    vector<int> G[MAX];
    struct Edge
    {
        int from, to, c, f;
    };
    vector<Edge> E;
    int distance[MAX];
    bool visited[MAX];
    queue<int> q;

public:
    int S, T;
    void addEdge(int from, int to, int cap)
    {
        E.push_back((Edge){from, to, cap, 0});
        E.push_back((Edge){to, from, 0, 0});
        G[from].push_back(E.size() - 2);
        G[to].push_back(E.size() - 1);
    }
    bool BFS()
    {
        memset(visited, false, sizeof(visited));
        while (!q.empty())
            q.pop();
        q.push(S);
        distance[S] = 0;
        visited[S] = true;
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < G[cur].size(); ++i)
            {
                Edge &temp = E[G[cur][i]];
                int next = temp.to;
                if (!visited[next] && temp.c > temp.f)
                {
                    distance[next] = distance[cur] + 1;
                    q.push(next);
                    visited[next] = true;
                }
            }
        }
        return visited[T];
    }
    int DFS(int cur, int flow)
    {
        if (cur == T || flow == 0)
            return flow;
        int rest = flow;
        int test;
        for (int i = 0; rest > 0 && i < G[cur].size(); ++i)
        {
            Edge &temp = E[G[cur][i]];
            int next = temp.to;
            if (temp.c > temp.f && distance[next] == distance[cur] + 1)
            {
                test = DFS(next, min(rest, temp.c - temp.f));
                if (!test)
                    distance[next] = 0;
                temp.f += test;
                E[G[cur][i] ^ 1].f -= test;
                rest -= test;
            }
        }
        return flow - rest;
    }

    int maxFlow()
    {
        int res = 0;
        int flow = 0;
        while (BFS())
        {
            while (flow = DFS(S, INT_MAX))
                res += flow;
        }
        return res;
    }
};
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m, k; // hero, monster, potion
    cin >> n >> m >> k;
    Graph g;
    g.S = 0;
    g.T = n + m + 2;
    g.addEdge(g.S, n + m + 1, k);
    int t;
    for (int i = 1; i <= n; ++i)
    { // index of hero
        g.addEdge(g.S, i, 1);
        g.addEdge(n + m + 1, i, 1);
        cin >> t; // size of Mi
        for (int j = 1, m; j <= t; ++j)
        {
            cin >> m;
            g.addEdge(i, n + m, 1);
        }
    }
    for (int i = 1; i <= m; ++i)
        g.addEdge(n + i, g.T, 1);
    cout << g.maxFlow() << '\n';
    return 0;
}
