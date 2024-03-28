#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
vector<vector<int> > adj;
vector<vector<int> > resVec;
// head and tail has 2 len respectively, so totally 2^2 * 2(from head or tail) = at most 8 keys
void addEdge(vector<vector<int> > &adj, int a, int b)
{
    adj[a].push_back(b);
    adj[b].push_back(a);
}
bool BFS(int i, vector<bool> visited)
{
    queue<int> q;
    q.push(i);
    int cur;
    while (!q.empty())
    {
        cur = q.front();
        visited[cur] = true;
        q.pop();
        if (adj[cur].size() == 3)
            return true;
        if (adj[cur].size() == 1)
            return false;
        for (int k : adj[cur])
            if (!visited[k])
                q.push(k);
    }
    return false;
}
void Traverse(int i, int &len, vector<bool> visited)
{
    while (adj[i].size() == 2)
    {
        visited[i] = true;
        for (int dir = 0; dir < 2; ++dir)
        {
            if (!visited[adj[i][dir]])
            {
                i = adj[i][dir];
                ++len;
                break;
            }
        }
    }
    if (adj[i].size() == 3)
        len = -1;
}
void makeJointList(vector<int> &jointList, vector<bool> visited, int head)
{
    queue<int> q;
    q.push(head);
    int cur;
    while (!q.empty())
    {
        cur = q.front();
        visited[cur] = true;
        if (adj[cur].size() == 3)
            jointList.push_back(cur);
        q.pop();
        for (int i : adj[cur])
        {
            if (!visited[i])
            {
                q.push(i);
            }
        }
    }
}
void makeResVec(int head, int n)
{
    vector<int> jointList;
    vector<bool> visited(n, false);
    makeJointList(jointList, visited, head);
    for (int k = 0; k < jointList.size(); ++k)
    {
        vector<int> lenVec; // head and tail -> size = 2, others -> size = 1
        int len;
        vector<bool> visited(n,false);
        visited[jointList[k]] = true;
        for (int dir = 0; dir < 3; ++dir)
        {
            len = 1;
            Traverse(adj[jointList[k]][dir], len, visited);
            if (len != -1)
            {
                lenVec.push_back(len);
                if (k != 0 && k != jointList.size() - 1)
                    break;
            }
        }
        resVec.push_back(lenVec);
    }
}
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    adj.resize(n);
    int a, b;
    for (int i = 0; i < n - 1; ++i)
    {
        cin >> a >> b;
        addEdge(adj, a, b);
    }
    for (int i = 0; i < n; ++i)
    {
        if (adj[i].size() < 3)
            continue;
        vector<bool> visited(n, false);
        visited[i] = true;
        int adj0 = adj[i][0];
        int adj1 = adj[i][1];
        int adj2 = adj[i][2];
        bool A = BFS(adj0, visited);
        bool B = BFS(adj1, visited);
        bool C = BFS(adj2, visited);
        if (A & B || A & C || B & C)
            continue;
        else if (A || B || C)
        {
            makeResVec(i, n); 
            break;
        }
    }
    int m;
    cin >> m;
    if (resVec.size() != m)
    {
        cout << "NO\n";
        return 0;
    }
    vector<int> res(m);
    for (int i = 0; i < m; ++i)
        cin >> res[i];
    vector<int> rev = res;
    reverse(rev.begin(), rev.end());
    bool YES = true;
    for (int i = 0; i < m; ++i)
    {
        if (i == 0 || i == m - 1)
        {
            for (int j : resVec[i])
            {
                if (j == res[i])
                {
                    YES = true;
                    break;
                }
                else
                    YES = false;
            }
            if (YES == false)
                break;
        }
        else
        {
            if (resVec[i][0] == res[i])
                YES = true;
            else
            {
                YES = false;
                break;
            }
        }
    }
    if (!YES)
    {
        for (int i = 0; i < m; ++i)
        {
            if (i == 0 || i == m - 1)
            {
                for (int j : resVec[i])
                {
                    if (j == rev[i])
                    {
                        YES = true;
                        break;
                    }
                    else
                        YES = false;
                }
                if (YES == false)
                    break;
            }
            else
            {
                if (resVec[i][0] == rev[i])
                    YES = true;
                else
                {
                    YES = false;
                    break;
                }
            }
        }
    }
    if (YES)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}
