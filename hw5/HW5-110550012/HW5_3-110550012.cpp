#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define to_weight pair<ll, ll>
//  1 to n
ll n, m;
vector<ll> u;
vector<ll> v;
vector<ll> w;
vector<ll> dfn;
vector<ll> low;
vector<ll> bridge;
ll tot = 0;
vector<to_weight> r;
class Graph
{
private:
    ll numVertex;
    vector<vector<to_weight> > adjList;
    priority_queue<to_weight, vector<to_weight>, greater<to_weight> > pq;

public:
    Graph() : numVertex(0){};
    Graph(ll n) : numVertex(n)
    {
        adjList.resize(numVertex + 1);
    }
    void addEdge(ll from, ll to, ll weight)
    {
        adjList[from].push_back(make_pair(to, weight));
    }
    void dijkstra(vector<ll> &d, ll start);
    void tarjan(ll x, pair<ll, ll> in);
};
void Graph::dijkstra(vector<ll> &d, ll start)
{
    vector<bool> visited(numVertex + 1, false);
    pq.push(make_pair(0, start));
    d[start] = 0;
    while (!pq.empty())
    {
        ll u = pq.top().second;
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = true;

        for (auto i : adjList[u])
        {
            ll v = i.first;
            ll w = i.second;
            if (d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                pq.push(make_pair(d[v], v));
            }
        }
    }
}

void Graph::tarjan(ll x, pair<ll, ll> in)
{
    dfn[x] = low[x] = ++tot;
    r[x] = in;
    for(auto i : adjList[x]){
        ll y = i.first;
        if(!dfn[y]){
            tarjan(y, make_pair(x, i.second));
            low[x] = min(low[x], low[y]);
        }
        else if(y!=in.first) low[x] = min(low[x], dfn[y]);
    }
    

}

int main()
{

    cin >> n >> m;
    ll original;
    vector<ll> d1(n + 1, 0x3f3f3f3f);
    vector<ll> d2(n + 1, 0x3f3f3f3f);
    u.resize(m+1, 0);
    v.resize(m+1, 0);
    w.resize(m+1, 0);
    dfn.resize(n+1, 0);
    low.resize(n+1, 0);
    bridge.resize(n+1,0);
    r.resize(n+1);
    for (ll i = 1; i <= m; ++i)
        cin >> u[i] >> v[i] >> w[i];
    Graph g1(n);
    for (ll i = 1; i <= m; ++i)
        g1.addEdge(u[i], v[i], w[i]);
    g1.dijkstra(d1, 1);
    Graph g2(n);
    for (ll i = 0; i <= m; ++i)
        g2.addEdge(v[i], u[i], w[i]);
    g2.dijkstra(d2, 2);
    original = d1[2];
    vector<ll> ans(m+1, 0);
    for(int i = 1; i <= m; ++i)
        if (original > d1[v[i]] + d2[u[i]] + w[i])
            ans[i] = 1;
    Graph g3(n);
    for (ll i = 1; i <= m; ++i)
        if (original == d1[u[i]] + d2[v[i]] + w[i])
        {
            g3.addEdge(u[i], v[i], i);
            g3.addEdge(v[i], u[i], i);
        }
    
    g3.tarjan(1, make_pair(1,1));
    for(ll v= 2; v <= n; ++v){
        ll u = r[v].first;
        ll i = r[v].second;
        if(low[v] > dfn[u]) ans[i] = 2;
    }

    for (ll i = 1; i <= m; ++i)
    {
        if(ans[i] == 1)
            cout << "HAPPY\n";
        else if (ans[i] == 2)
            cout << "SAD\n";
        else
            cout << "SOSO\n";
    }
    return 0;
}