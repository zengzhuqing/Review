#include <iostream>
using namespace std;
/*

 * Binary search tree:
 *  Read operation: Search, FindMax, FindMin, Next, Previous
 *  Write Operation: Insert, Delete
 * Refer to DS Book(Chen Yue) 
 */
#define USE_NEXT_PREVIOUS
struct Tree{
    int val;
    Tree *left;
    Tree *right;
#ifdef USE_NEXT_PREVIOUS
    Tree *p;
    Tree(int val):val(val), left(NULL), right(NULL), p(NULL){}
#else
    Tree(int val):val(val), left(NULL), right(NULL){}
#endif
};
Tree *search(Tree *root, int val)
{
    if (root == NULL)
        return NULL;
    if (root->val == val)
        return root;
    else if (root->val > val)
        return search(root->left, val);
    else
        return search(root->right, val);
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
#ifdef USE_NEXT_PREVIOUS
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
#endif
Tree *Insert(Tree *root, int val)
{
    if (root == NULL)
    {
        return new Tree(val);
    }
    if (root->val > val)
    {
        root->left = Insert(root->left, val);
        #ifdef USE_NEXT_PREVIOUS
        if(root->left != NULL)
            root->left->p = root;
        #endif
    }
    else if (root->val < val)
    {
        root->right = Insert(root->right, val);
        #ifdef USE_NEXT_PREVIOUS
        if(root->right != NULL)
            root->right->p = root;
        #endif
    }
    /* else not insert */
    return root;
}
Tree *Delete(Tree *root, int val)
{
    if (root == NULL)
        return NULL;
    if (root->val > val)
    {
        root->left = Delete(root->left, val);
        #ifdef USE_NEXT_PREVIOUS
        if(root->left != NULL)
            root->left->p = root;
        #endif
    }
    else if(root->val < val)
    {
        root->right = Delete(root->right, val);
        #ifdef USE_NEXT_PREVIOUS
        if(root->right != NULL)
            root->right->p = root;
        #endif
    }
    else
    {
        if (root->left != NULL && root->right != NULL)
        {
            Tree *cur = root->right;
            while(cur->left != NULL)
            {
                cur = cur->left;
            }
            /* now cur is the min of right */
            root->val = cur->val;
            root->right = Delete(root->right, cur->val);
            #ifdef USE_NEXT_PREVIOUS
            if(root->right != NULL)
                root->right->p = root;
            #endif
        }
        else if(root->left == NULL)
        {
            Tree *tmp = root;
            #ifdef USE_NEXT_PREVIOUS
            if(root->right != NULL)
                root->right->p = root->p;
            #endif
            root = root->right;
            delete tmp;
        }
        else
        {
            Tree *tmp = root;
            #ifdef USE_NEXT_PREVIOUS
            root->left->p = root->p;
            #endif
            root = root->left;
            delete tmp;
        }
    }
    return root;
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
    Delete(root, 3);
    Delete(root, 3);
}
