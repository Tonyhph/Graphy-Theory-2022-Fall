#include <bits/stdc++.h>
using namespace std;
//TLE
class TreeNode
{
public:
    int index;
    vector<TreeNode *> children;
    TreeNode *parent;
    int depth;
    TreeNode() {}
    TreeNode(int _index)
    {
        index = _index;
    }
};

int findDist(TreeNode *src, TreeNode *dst)
{
    map<TreeNode *, int> parents;
    TreeNode *current = src;
    int dist = 0;
    while (current != NULL)
    {
        parents[current] = dist + 1;
        ++dist;
        current = current->parent;
    }
    current = dst;
    dist = 0;
    while (!parents[current])
    {
        current = current->parent;
        dist++;
    }
    return parents[current] + dist;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n; // a tree with n vertices and n-1 edges
    cin >> n;
    vector<TreeNode *> nodeList(n + 1);
    for (int i = 1; i <= n; ++i)
        nodeList[i] = new TreeNode(i);
    int x, y;
    // nodeList[1]->depth = 0; //default depth = 0
    // nodeList[1]->parent = NULL; //default
    for (int i = 0; i < n - 1; ++i)
    {
        cin >> x >> y; // indicate the unique edge connect vetice x and y with length 1
        nodeList[x]->children.push_back(nodeList[y]);
        nodeList[y]->depth = nodeList[x]->depth + 1;
        nodeList[y]->parent = nodeList[x];
    }
    int Q; // num of queries
    cin >> Q;
    int u, v;
    for (int i = 0; i < Q; ++i)
    {
        cin >> u >> v; // mean asked to find out length from u to v
        cout << findDist(nodeList[u],nodeList[v])-1 << '\n';
        // TreeNode *LCA = findLCA(nodeList[1], nodeList[u], nodeList[v]);
    }
}
