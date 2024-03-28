#include <bits/stdc++.h>
using namespace std;
long long n;
class Graph
{
public:
    long long adj[13][13];
    long long deg[13];

    Graph()
    {
        memset(adj, 0, sizeof(adj));
        memset(deg, 0, sizeof(deg));
    }

    void addEdge(long long x, long long y)
    {
        adj[x][y] = adj[y][x] = 1;
    }
    bool isPlanar()
    {
        if (K5() || K33())
            return 0;
        return 1;
    }
    bool K5()
    {
        long long p[8];
        long long i, k;
        for (p[0] = 0, k = 0; k >= 0;)
        {
            if (++p[k] > n)
            {
                --k;
                continue;
            }
            for (i = 0; i < k; i++)
                if (!adj[p[k]][p[i]])
                    break;
            if (i < k)
            {
                --k;
                continue;
            }
            if (k == 4)
                return 1;
            p[k + 1] = p[k];
            ++k;
        }
        return 0;
    }
    bool K33()
    {
        long long a, b, c, d, e, f;
        for (a = 1; a <= n; ++a)
        {
            for (d = 1; d <= n; ++d)
            {
                if (!adj[a][d])
                    continue;
                for (b = 1; b <= n; ++b)
                {
                    if (!adj[b][d] || a == b)
                        continue;
                    for (e = 1; e <= n; ++e)
                    {
                        if (!adj[a][e] || !adj[b][e] || d == e)
                            continue;
                        for (c = 1; c <= n; ++c)
                        {
                            if (!adj[d][c] || !adj[e][c] || c == a || c == b)
                                continue;
                            for (f = 1; f <= n; ++f)
                            {
                                if (!adj[a][f] || !adj[b][f] || !adj[c][f] || f == d || f == e)
                                    continue;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        return 0;
    }
};

int main()
{
    long long Q;
    cin >> Q;
    long long m;
    long long x, y;
    while (Q--)
    {
        long long i, j = 1, k;
        cin >> n >> m;
        Graph g;
        while (m--)
        {
            cin >> x >> y;
            g.addEdge(x, y);
        }
        if(m > 3*n-6){
            cout<<"No\n";
            continue;
        }
        for (i = 1; i <= n; ++i)
        {
            for (long long j = 1; j <= n; ++j)
                g.deg[i] += g.adj[i][j];
        }

        while (j != 0)
        {
            j = 0;
            for (i = 1; i <= n; ++i)
            {
                if (g.deg[i] == 1)
                {
                    for (g.deg[i] = 0, j = 1; j <= n; ++j)
                        if (g.adj[i][j])
                            break;
                    g.adj[i][j] = g.adj[j][i] = 0;
                    --g.deg[j];
                }
                else if (g.deg[i] == 2)
                {
                    for (g.deg[i] = 0, j = 1; j <= n; ++j)
                        if (g.adj[i][j])
                            break;
                    for (k = j + 1; k <= n; k++)
                        if (g.adj[i][k])
                            break;
                    g.adj[i][j] = g.adj[j][i] = 0;
                    g.adj[i][k] = g.adj[k][i] = 0;
                    g.adj[j][k] = g.adj[k][j] = 1;
                }
            }
        }

        for (i = 1; i <= n; ++i)
        {
            if (g.deg[i] == 0)
                continue;
            for (j = 1, k = 1; j <= n; ++j)
                if (g.deg[j] != 0)
                    g.adj[i][k++] = g.adj[i][j];
        }
        for (i = 1, k = 0; i <= n; ++i)
        {
            if (g.deg[i] == 0)
                continue;
            ++k;
            if (i != k)
                memcpy(g.adj[k], g.adj[i], sizeof(g.adj[0]));
        }
        n = k;
        for (long long i = 1; i <= n; ++i)
            g.adj[i][i] = 0;
        if (g.isPlanar())
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}