/*
 * AVL Balenced Binary Search Tree
 * Refer to DS Book(Chen Yue)
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct AVLTree
{
    int val;
    AVLTree *left;
    AVLTree *right;
    int height;
    AVLTree(int val):val(val), left(NULL), right(NULL), height(0){}
};
int Height(AVLTree *root)
{
    if (root == NULL)
        return -1;
    return root->height;
}
/*
 *  Single Rotate With Left
 *     R          K
 *   K  C  -->  A+ R
 * A+ B           B C
 *
 */
AVLTree *SingleRotateWithLeft(AVLTree *root)
{
    AVLTree *K = root->left;

    root->left = K->right;
    K->right = root;

    root->height = max(Height(root->left), Height(root->right)) + 1;
    K->height = max(Height(K->left), Height(K->right)) + 1;

    return K;
}
/*
 *  Single Rotate With Right
 *     R          K
 *   A  K  -->  R  C+
 *     B C+    A B
 *
 */
AVLTree *SingleRotateWithRight(AVLTree *root)
{
    AVLTree *K = root->right;

    root->right = K->left;
    K->left = root;

    root->height = max(Height(root->left), Height(root->right)) + 1;
    K->height = max(Height(K->left), Height(K->right)) + 1;

    return K;
}
/*
 *  Double Rotate With Left
 *     R          R         R         K1
 *   K  C  -->  K  C  --> K1  C --> K    R
 * A B+       A  K1      K  E      A D  E C
 *              D E     A D
 * Mind: the first Rotate do not make K balenced, it just Rotate, only
 * after two rotate, balenced is for sure
 */
AVLTree *DoubleRotateWithLeft(AVLTree *root)
{
    root->left = SingleRotateWithRight(root->left);

    return SingleRotateWithLeft(root);
}
AVLTree *DoubleRotateWithRight(AVLTree *root)
{
    root->right = SingleRotateWithLeft(root->right);

    return SingleRotateWithRight(root);
}
AVLTree *Insert(AVLTree *root, int val)
{
    if (root == NULL)
        return new AVLTree(val);
    if (root->val > val)
    {
        root->left = Insert(root->left, val);
        if (Height(root->left) - Height(root->right) == 2)
        {
            if (root->left->val > val)
                root = SingleRotateWithLeft(root);
            else
                root = DoubleRotateWithLeft(root);
        }
    }
    else if (root->val < val)
    {
        root->right = Insert(root->right, val);
        if (Height(root->right) - Height(root->left) == 2)
        {
            if (root->right->val > val)
                root = DoubleRotateWithRight(root);
            else
                root = SingleRotateWithRight(root);
        }
    }
    /* else no insert */

    root->height = max(Height(root->left), Height(root->right)) + 1;
    return root;
}
int main()
{
/* for PAT Advance 1066 */
    int N;
    cin >> N;
    vector<int> num(N);
    for(int i = 0; i < N; i++)
    {
        cin >> num[i];
    }
    AVLTree *root = NULL;
    for(int i = 0; i < N; i++)
        root = Insert(root, num[i]);

    cout << root->val;

    return 0;
}
