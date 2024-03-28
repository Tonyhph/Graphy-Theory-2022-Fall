#include <bits/stdc++.h>
using namespace std;
int n, m;
int main()
{
    cin >> n >> m;
    vector<int> deg(n,0);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        ++deg[u];
        ++deg[v];
    }
    sort(deg.begin(), deg.end());
    cout<<deg[0]<<'\n';
}