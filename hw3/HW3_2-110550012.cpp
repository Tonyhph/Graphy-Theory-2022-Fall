#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define to_weight pair<ll, ll>
#define maxDistance LLONG_MAX
//  0 to n-1
class Graph
{
private:
    ll numVertex;
    vector<vector<to_weight> > adjList;
    priority_queue<to_weight, vector<to_weight>, greater<to_weight> > pq;
public:
    vector<ll> distance;
    Graph() : numVertex(0){};
    Graph(ll n) : numVertex(n)
    {
        adjList.resize(numVertex + 1);
    }
    void addEdge(ll from, ll to, ll weight)
    {
        adjList[from].push_back(make_pair(to, weight));
    }
    void dijkstra(ll start);
};
void Graph::dijkstra(ll start)
{
    distance.clear();
    distance.resize(numVertex + 1, maxDistance);
    vector<bool> visited(numVertex + 1, false);
    pq.push(make_pair(0, start));
    distance[start] = 0;
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
            if (distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                pq.push(make_pair(distance[v], v));
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    ll T, sub;
    ll n, m, k;
    // k == 2 ->  goto 1 and n,  k == 1 -> goto 1
    ll u, v, w; // u->v, weight
    cin >> T >> sub;
    while (T--)
    {
        cin >> n >> m >> k;
        Graph g(n);
        for (ll i = 0; i < m; ++i)
        {
            cin >> u >> v >> w;
            // many points to one point, so swap
            swap(u, v);
            --u;
            --v;
            g.addEdge(u, v, w);
        }
        if (k == 1)
        { // min len from restaurant i-1 to restaurant 0
            g.dijkstra(0);
            for (int i = 0; i < n; ++i)
            {
                if (g.distance[i] == maxDistance)
                    cout << -1 << ' ';
                else
                    cout << g.distance[i] << ' ';
            }
            cout << '\n';
        }
        else if (k == 2)
        {
            // to 0 dis
            // to n-1 dis
            vector<ll> weight(n+1, 0);
            g.dijkstra(0);
            for (int i = 0; i < g.distance.size(); ++i)
            {
                weight[i] += g.distance[i];
            }
            g.dijkstra(n - 1);
            for (int i = 0; i < g.distance.size(); ++i)
            {
                if (g.distance[i] != maxDistance && weight[i] != maxDistance) //warning
                    weight[i] += g.distance[i];
                else weight[i] = maxDistance;
            }
            for (int i = 0; i <= n; ++i)
            {
                if (weight[i] != maxDistance)
                    g.addEdge(n, i, weight[i]);
            }
            g.dijkstra(n);
            for (int i = 0; i < n; ++i)
            {
                if (g.distance[i] == maxDistance)
                    cout << -1 << ' ';
                else
                    cout << g.distance[i] << ' ';
            }
            cout<<'\n';
        }
    }
}
