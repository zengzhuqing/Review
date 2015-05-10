#include <iostream>
#include <cassert>
using namespace std;
/*

 * Binary search tree:
 *  Read operation: Search, FindMax, FindMin, Next, Previous
 *  Write Operation: Insert, Delete
 *
 *  Search, Insert, Delete is different from the recursion one
 *
 * Refer to Algorithm Book
 */
struct Tree{
    int val;
    Tree *left;
    Tree *right;
    Tree *p;
    Tree(int val):val(val), left(NULL), right(NULL), p(NULL){}
};
Tree *search(Tree *root, int val)
{
    while (root != NULL)
    {
        if (root->val == val)
            return root;
        else if (root->val > val)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}
Tree *FindMin(Tree *root)
{
    if (root == NULL)
        return NULL;
    while(root->left != NULL)
    {
        root = root->left;
    }
    return root;
}
Tree *FindMax(Tree *root)
{
    if (root == NULL)
        return NULL;
    while(root->right != NULL)
    {
        root = root->right;
    }
    return root;
}
Tree *next(Tree *cur)
{
    if (cur == NULL)
        return NULL;

    if (cur->right != NULL)
    {
        return FindMin(cur->right);
    }
    else
    {
        while (cur->p != NULL)
        {
            if(cur->p->left == cur)
                return cur->p;
            cur = cur->p;
        }
        return NULL;
    }
}
Tree *previous(Tree *cur)
{
    if (cur == NULL)
        return NULL;

    if (cur->left != NULL)
    {
        return FindMax(cur->left);
    }
    else
    {
        while (cur->p != NULL)
        {
            if(cur->p->right == cur)
                return cur->p;
            cur = cur->p;
        }
        return NULL;
    }
}
/*
 * Insert: without recursion
 *  Resposibility: new A node && update parent's children
 *  1. find position and the parent;
 *  2. new the node with val;
 *  3. update parent's children
 *  Corner Case: root is NULL
 */
Tree *Insert(Tree *root, int val)
{
    Tree *x = root;
    Tree *y = NULL;
    if (x == NULL)
    {
        return new Tree(val);
    }
    do
    {
        y = root;
        if (root->val > val)
            root = root->left;
        else if(root->val < val)
            root = root->right;
        else // val exists
            return x;
    } while (root != NULL);
    Tree *z = new Tree(val);
    z->p = y;
    if (y->val < val)
        y->right = z;
    else
        y->left = z;

    return x;
}
/*
 * Delete: without recursion
 *  Responsibility: find the node with val delete and connect to rest
 *
 * Three Cases:
 *  Help function: Transplant
 *      Corner Case: old_node is root
 */
Tree *Transplant(Tree *root, Tree *old_node, Tree *new_node)
{
    if (old_node->p == NULL)
    {
        if (new_node != NULL)
            new_node->p = NULL;
        return new_node;
    }
    if (old_node->p->left == old_node)
        old_node->p->left = new_node;
    else
        old_node->p->right = new_node;

    if (new_node != NULL)
    {
        new_node->p = old_node->p;
    }

    return root;
}

void print(Tree *root)
{
    cout << "Tree:" << endl;
    if (root == NULL)
        return;
    Tree *i;
    for(i = FindMin(root); i != NULL; i = next(i))
    {
        cout << i->val << " ";
    }
    cout << endl;
}

Tree *Delete(Tree *root, int val)
{
    Tree *x = root;
    Tree *y = NULL;
    if (x == NULL)
    {
        return NULL;
    }
    while (root != NULL && root->val != val)
    {
        y = root;
        if (root->val > val)
            root = root->left;
        else if (root->val < val)
            root = root->right;
    }
    if (root == NULL) // val is not exist
        return x;
    if (root->left == NULL)
    {
        x = Transplant(x, root, root->right);
    }
    else if (root->right == NULL)
    {
        x = Transplant(x, root, root->left);
    }
    else
    {
        Tree *new_node = FindMin(root->right);
        if (root->right != new_node)
        {
            x = Transplant(x, new_node, new_node->right);
            new_node->right = root->right;
            new_node->right->p = new_node;
        }
        x = Transplant(x, root, new_node);
        new_node->left = root->left;
        new_node->left->p = new_node;
    }
    delete root;

    return x;
}

int main()
{
    Tree *root = new Tree(5);

    Insert(root, 3);
    Insert(root, 7);
    Insert(root, 6);
    Insert(root, 4);
    Insert(root, 1);
    Insert(root, 2);
    Insert(root, 9);
    Insert(root, 8);
    Tree *min = FindMin(root);
    cout << "min: " << min->val << endl;
    Tree *max = FindMax(root);
    cout << "max: " << max->val << endl;
    min = search(root, 8);
    max = previous(min);
    cout << min->val << "previous: " << max->val << endl;
    min = search(root, 2);
    max = next(min);
    cout << min->val << "next: " << max->val << endl;
    Insert(root, 3);
    print(root);
    root = Delete(root, 3);
    print(root);
    assert(search(root, 3) == NULL);
    assert(root->p == NULL);
    root = Delete(root, 5);
    assert(root->p == NULL);
    print(root);
    root = Delete(root, 1);
    print(root);
    root = Delete(root, 2);
    print(root);
    root = Delete(root, 4);
    print(root);
    root = Delete(root, 6);
    print(root);
    root = Delete(root, 7);
    print(root);
    root = Delete(root, 8);
    print(root);
    root = Delete(root, 9);
    print(root);
    assert(root == NULL);

    return 0;
}
