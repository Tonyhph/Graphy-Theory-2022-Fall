#include <bits/stdc++.h>
using namespace std;
class TreeNode
{
public:
    int index;
    TreeNode *parent;
    bool isLeaf;
    int depth;
    TreeNode() {}
    TreeNode(int _index)
    {
        index = _index;
        isLeaf = true;
    }
};
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<TreeNode *> nodeList(n + 1);
    int u, v;
    if (n == 1)
    {
        cout << 0 << ' ' << -1 << '\n';
        return 0;
    }

    cin >> u >> v;
    nodeList[u] = new TreeNode(u);
    nodeList[v] = new TreeNode(v);
    nodeList[u]->depth = 1;
    nodeList[v]->depth = 0;
    nodeList[u]->parent = new TreeNode(-1);
    nodeList[u]->parent->depth = INT_MAX;
    nodeList[v]->parent = nodeList[u];
    nodeList[u]->isLeaf = false;
    for (int i = 2; i < n; ++i)
    {
        cin >> u >> v;
        if (nodeList[u])
        {
            nodeList[v] = new TreeNode(v);
            nodeList[v]->parent = nodeList[u];
            nodeList[u]->isLeaf = false;
            nodeList[v]->depth = 0;
        }
        else if (nodeList[v])
        {
            nodeList[u] = new TreeNode(u);
            nodeList[u]->parent = nodeList[v];
            nodeList[v]->isLeaf = false;
            nodeList[u]->depth = 0;
        }
    }

    for (int i = n; i >= 1; --i)
    {
        if (nodeList[i]->isLeaf)
        {
            TreeNode *temp = nodeList[i];
            while (temp->parent->depth < temp->depth + 1)
            {
                temp->parent->depth = temp->depth + 1;
                temp = temp->parent;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << nodeList[i]->depth << ' ' << nodeList[i]->parent->index << '\n';
    }
}