#include <bits/stdc++.h>
using namespace std;
//TlE
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
// slower way
/*
TreeNode *findLCA(TreeNode *root, TreeNode *n1, TreeNode *n2)
{
    if (root == NULL || root == n1 || root == n2)
        return root;
    if (&root->children == NULL || root->children.size() == 0)
        return NULL;
    int count = 0;
    TreeNode *res = NULL;
    for (TreeNode *child : root->children)
    {
        TreeNode *cur = findLCA(child, n1, n2);
        if (cur != NULL)
        {
            count++;
            res = cur;
        }
    }
    if (count == 2)
        return root;
    return res;
}
*/
// faster way but not enough

TreeNode *faster_findLCA(TreeNode *n1, TreeNode *n2)
{
    TreeNode *larger, *smaller;
    if (n1->depth > n2->depth)
    {
        larger = n1;
        smaller = n2;
    }
    else
    {
        larger = n2;
        smaller = n1;
    }
    while (larger->depth != smaller->depth)
        larger = larger->parent;
    while (larger != smaller)
    {
        larger = larger->parent;
        smaller = smaller->parent;
    }
    return larger;
}
int getDistance(TreeNode *LCA, TreeNode *node){
    return node->depth - LCA->depth;
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
    nodeList[1]->depth = 0; //default depth = 0
    nodeList[1]->parent = NULL; //default
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
        TreeNode *LCA = faster_findLCA(nodeList[u], nodeList[v]);         
        //TreeNode *LCA = findLCA(nodeList[1], nodeList[u], nodeList[v]);
        int root_u_len = getDistance(LCA, nodeList[u]);
        int root_v_len = getDistance(LCA, nodeList[v]);
        cout << root_u_len + root_v_len << '\n';
    }
}