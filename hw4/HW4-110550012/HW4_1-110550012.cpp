#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define to_weight pair<ll, ll>
#define maxDistance INT_MAX
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
        adjList.resize(numVertex);
    }
    void addEdge(ll from, ll to, ll weight)
    {
        adjList[from].push_back(make_pair(to, weight));
    }
    void dijkstra(vector<ll>& pqList);
};
void Graph::dijkstra(vector<ll>& pqList)
{
    distance.clear();
    distance.resize(numVertex, maxDistance);
    vector<bool> visited(numVertex, false);
    for(auto i : pqList){
        pq.push(make_pair(0,i));
        distance[i] = 0;
    }
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
    ll n, m, p, q, t, T;
    cin>>n>>m>>p>>q>>t>>T;
    ll a,b,w;
    Graph virus(n);
    Graph anti(n); 
    vector<ll> pList(p);
    vector<ll> qList(q);
    for(int i = 0; i < m; ++i){
        cin>>a>>b>>w;
        virus.addEdge(a-1, b-1, w);
        anti.addEdge(a-1 ,b-1, 1);
    }
    ll v;
    for(int i = 0; i < p; ++i){
        cin>>v;
        --v;
        pList[i] = v;
    }
    virus.dijkstra(pList);

    for(int i = 0; i < q; ++i){
        cin>>v;
        --v;
        qList[i] = v;
    }
    anti.dijkstra(qList);

    ll ans = 0;
    
    for(int i = 0; i < n; ++i){
        if(virus.distance[i] < anti.distance[i] + t && virus.distance[i] <= T)
            ++ans;
    }
    cout<<ans<<'\n';
    return 0;
}
