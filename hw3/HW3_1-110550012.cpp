#include <bits/stdc++.h>
using namespace std;
#define edge pair<long long, long long>
class Graph
{
private:
    vector<pair<long long, edge> > G;
    vector<long long> parent;

public:
    Graph(long long n)
    {
        parent.resize(n+1);
        for (long long i = 1; i <= n; ++i)
            parent[i] = i;
        G.clear();
    }
    void AddEdge(long long u, long long v, long long w)
    {
        G.push_back(make_pair(w, edge(u, v)));
    }
    long long findSet(long long i)
    {
        return i == parent[i] ? i : (parent[i] = findSet(parent[i]));
    }
    void unionSet(long long u, long long v)
    {
        parent[u] = parent[v];
    }
    void kruskal()
    {
        long long uSet, vSet, res = 0;
        sort(G.begin(), G.end());
        for (long long i = 0; i < G.size(); ++i)
        {
            uSet = findSet(G[i].second.first);
            vSet = findSet(G[i].second.second);
            if (uSet != vSet)
            {
                res += G[i].first;
                unionSet(uSet, vSet);
            }
        }
        cout << res << '\n';
    }
};

int main()
{
    // city 1 to n
    // kruskal
    ios_base::sync_with_stdio(0), cin.tie(0);
    long long Q;
    cin >> Q;
    long long n, m;
    long long x, y, w;
    while (Q--)
    {
        cin >> n >> m; // n: # of cities m: # of special offers
        Graph Graph(n);
        vector<long long> a(n + 1);
        long long MIN = INT_MAX;
        long long source;
        for (long long i = 1; i <= n; ++i)
        {
            cin >> a[i];
            if (a[i] < MIN)
            {
                MIN = a[i];
                source = i;
            }
        }
        for(int i = 1; i < source; ++i){
            Graph.AddEdge(source, i, MIN+a[i]);
        }
        for(int i = source+1;i <= n; ++i){
            Graph.AddEdge(source, i, MIN+a[i]);
        }

        for (long long i = 0; i < m; ++i)
        {
            cin >> x >> y >> w;
            if(a[x]+ a[y] > w)
                Graph.AddEdge(x, y, w);
        }
        Graph.kruskal();
    }
}