#include <iostream>
#include <cassert>
using namespace std;
/*

 * Red Black tree:
 *  Read operation: Search, FindMax, FindMin, Next, Previous
 *  Write Operation: Insert, Delete
 *
 *  Only Insert, Delete is special
 *
 * Refer to Algorithm Book
 */
enum Color
{
    BLACK, RED
};
struct RBTree{
    int val;
    RBTree *left;
    RBTree *right;
    RBTree *p;
    Color color;
    RBTree(int v):val(v), color(BLACK){}
};
RBTree Nil_Node(0);
RBTree *Nil = &Nil_Node;

RBTree *search(RBTree *root, int val)
{
    while (root != Nil)
    {
        if (root->val == val)
            return root;
        else if (root->val > val)
            root = root->left;
        else
            root = root->right;
    }
    return Nil;
}

RBTree *FindMin(RBTree *root)
{
    if (root == Nil)
        return Nil;
    while(root->left != Nil)
    {
        root = root->left;
    }
    return root;
}

RBTree *FindMax(RBTree *root)
{
    if (root == Nil)
        return Nil;
    while(root->right != Nil)
    {
        root = root->right;
    }
    return root;
}

RBTree *next(RBTree *cur)
{
    if (cur == Nil)
        return Nil;

    if (cur->right != Nil)
    {
        return FindMin(cur->right);
    }
    else
    {
        while (cur->p != Nil)
        {
            if(cur->p->left == cur)
                return cur->p;
            cur = cur->p;
        }
        return Nil;
    }
}

RBTree *previous(RBTree *cur)
{
    if (cur == Nil)
        return Nil;

    if (cur->left != Nil)
    {
        return FindMax(cur->left);
    }
    else
    {
        while (cur->p != Nil)
        {
            if(cur->p->right == cur)
                return cur->p;
            cur = cur->p;
        }
        return Nil;
    }
}

/*
 * SingleRotateWithLeft
 *  Rotate may cause root change, return new root
 *
 *      K1         K2
 *    K2  C  --> A   K1
 *  A   B           B  C
 *  Mind that it is little more difficult than the one in AVLTree,
 * for it is not use in Recursion Environment
 *  Every Time you update a pointer, a corresponding p should be set
 */
static RBTree *SingleRotateWithLeft(RBTree *root, RBTree *k1)
{
    assert(k1 != Nil);
    assert(k1->left != Nil);
    RBTree *k2 = k1->left;

    k1->left = k2->right;
    if (k2->right != Nil)
        k2->right->p = k1;

    k2->right = k1;
    RBTree *old_p = k1->p;
    k1->p = k2;

    k2->p = old_p;
    if (old_p->left == k1)
        old_p->left = k2;
    else
        old_p->right = k2;

    if (old_p == Nil)
        root = k2;

    return root;
}

/*
 * SingleRotateWithRight
 *      K1         K2
 *    A  K2  --> K1  C
 *      B  C    A  B
 */
static RBTree *SingleRotateWithRight(RBTree *root, RBTree *k1)
{
    assert(k1 != Nil);
    assert(k1->right != Nil);
    RBTree *k2 = k1->right;

     k1->right  = k2->left;
    if (k2->left != Nil)
        k2->left->p = k1;

    k2->left = k1;
    RBTree *old_p = k1->p;
    k1->p = k2;

    k2->p = old_p;
    if (old_p->left == k1)
        old_p->left = k2;
    else
        old_p->right = k2;

    if (old_p == Nil)
        root = k2;

    return root;
}

/*
 * RBFixInsert:
 *  RBFixInsert may cause root change, return new root
 *  Three Cases:
 *    Case 1:
 *          B          R
 *        R   R -->  B   B, Next Z is Z->p->p
 *       Z         Z
 *    Case 2:
 *         B          B
 *       R   B -->   R
 *     B   Z        Z
 *                 B
 *    Case 3:
 *       B            R          B
 *      R     -->    B   -->   Z   R
 *     Z            Z         B
 *    B            B
 */
static RBTree *RBFixInsert(RBTree *root, RBTree *z)
{
    while (z->p->color == RED)
    {
        if (z->p->p->left == z->p)
        {
            RBTree *y = z->p->p->right;
            if (y->color == RED) //Case 1
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z->p->right == z) // Case 2
                {
                    z = z->p;
                    root = SingleRotateWithRight(root, z);
                }
                //Case 3
                z->p->color = BLACK;
                z->p->p->color = RED;
                root = SingleRotateWithLeft(root, z->p->p);
            }
        }
        else
        {
            RBTree *y = z->p->p->left;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z->p->left == z)
                {
                    z = z->p;
                    root = SingleRotateWithLeft(root, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                root = SingleRotateWithRight(root, z->p->p);
            }
        }
        root->color = BLACK;//Case 1 may violate rule: root is Black
    }

    return root;
}

/*
 * Insert:
 *  Resposibility: new A node && update parent's children
 *      Fix Red Black Tree 's feature
 *  1. find position and the parent;
 *  2. new the node with val;
 *  3. update parent's children
 *  4. Fix
 */
RBTree *Insert(RBTree *root, int val)
{
    RBTree *x = root;
    RBTree *y = Nil;
    while (root != Nil)
    {
        y = root;
        if (root->val > val)
            root = root->left;
        else if(root->val < val)
            root = root->right;
        else // val exists
            return x;
    }
    RBTree *z = new RBTree(val);
    z->left = Nil;
    z->right = Nil;
    z->p = y;
    if (y == Nil) // root is Nil
        return z;
    if (y->val < val)
        y->right = z;
    else
        y->left = z;
    z->color = RED;
    x = RBFixInsert(x, z);

    return x;
}

static void print(RBTree *root)
{
    cout << "RBTree:" << endl;
    if (root == Nil)
        return;
    RBTree *i;
    for(i = FindMin(root); i != Nil; i = next(i))
    {
        cout << i->val << " ";
    }
    cout << endl;
}

/*
 * Transplant:
 *  Responsibility: find the node with val delete and connect to rest
 *
 *  Corner Case: old_node is root
 *
 *  Differnet from binary_search_tree, now Nil can also set p
 */
RBTree *Transplant(RBTree *root, RBTree *old_node, RBTree *new_node)
{
    if (old_node->p == Nil)
    {
        new_node->p = Nil;
        return new_node;
    }
    if (old_node->p->left == old_node)
        old_node->p->left = new_node;
    else
        old_node->p->right = new_node;

    new_node->p = old_node->p;

    return root;
}

/*
 * RBFixDelete:
 *
 * in the while:
 *  1. xx is not the root
 *  2. xx is double black node
 *
 * Four Cases:
 *     a) Only when Brother is is black, we have oportunity to throw
 *        the extra Black up
 *     b) when we want to turn a node's color to red, it must have double
 *        black children
 *     c) if brother has red children, we just throw brother's black to
 *     our path so we can get rid of the extra black 
 *   
 *   Case 1:
 *          B(B)            C(B)
 *       A(XX) C(R) -->  B(R)  E(B)  --> So to case 2,3,4
 *          D(B) E(B) A(XX) D(B)
 *   
 *   Case 2:
 *         B(BR)           B(XX)
 *      A(XX)  C(B)  --> A(B) C(R)      just let xx up
 *           D(B) E(B)      D(B) E(B)
 *
 *   Case 3:
 *         B(BR)           B(BR)
 *      A(XX)  C(B)  --> A(XX) D(B)  --> so to case 4
 *          D(R) E(BR)           C(R)
 *                                 E(BR)
 *   Case 4:
 *          B(BR)             C(BR)
 *      A(XX)  C(B)  -->  B(B)    E(B) --> OK
 *          D(BR) E(R) A(XX) D(BR)
 */
static RBTree *RBFixDelete(RBTree *root, RBTree *xx)
{
    while (xx->p != Nil && xx->color == BLACK)
    {
        if (xx->p->left == xx)
        {
            RBTree *w = xx->p->right;
            if (w->color == RED) //Case 1
            {
                w->color = BLACK;
                xx->p->color = RED;
                root = SingleRotateWithRight(root, xx->p);
                w = xx->p->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            { //Case 2
                w->color = RED;
                xx = xx->p;
            }
            else
            {
                if (w->right->color == RED)
                { //Case 3
                    w->color = RED;
                    w->left->color = BLACK;
                    root = SingleRotateWithLeft(root, w);
                    w = xx->p->right;//update w
                }
                //Case 4
                w->right->color = BLACK;
                w->color = xx->p->color;
                xx->p->color = BLACK;
                root = SingleRotateWithRight(root, xx->p);
                break;
            }
        }
        else
        {
            RBTree *w = xx->p->left;
            if (w->color == RED) //Case 1
            {
                w->color = BLACK;
                xx->p->color = RED;
                root = SingleRotateWithLeft(root, xx->p);
                w = xx->p->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            { //Case 2
                w->color = RED;
                xx = xx->p;
            }
            else
            {
                if (w->right->color == RED)
                { //Case 3
                    w->color = RED;
                    w->right->color = BLACK;
                    root = SingleRotateWithRight(root, w);
                    w = xx->p->left;
                }
                //Case 4
                w->left->color = BLACK;
                w->color = xx->p->color;
                xx->p->color = BLACK;
                root = SingleRotateWithLeft(root, xx->p);
                break;
            }
        }
    }
    root->color = BLACK;

    return root;
}

/*
 * Delete:
 *  Responsibility: find the node with val delete and connect to rest
 *  and than fix
 *
 *  1.A color is deleted only in the leaf
 */
RBTree *Delete(RBTree *root, int val)
{
    RBTree *x = root;
    RBTree *y = Nil;
    if (x == Nil)
    {
        return Nil;
    }
    while (root != Nil && root->val != val)
    {
        y = root;
        if (root->val > val)
            root = root->left;
        else if (root->val < val)
            root = root->right;
    }
    if (root == Nil) // val is not exist
        return x;

    RBTree *xx;
    Color delete_color = root->color;
    if (root->left == Nil)
    {
        xx = root->right;
        x = Transplant(x, root, root->right);
    }
    else if (root->right == Nil)
    {
        xx = root->left;
        x = Transplant(x, root, root->left);
    }
    else
    {
        RBTree *new_node = FindMin(root->right);
        delete_color = new_node->color;
        xx = new_node->right;
        if (root->right != new_node)
        {
            x = Transplant(x, new_node, new_node->right);
            new_node->right = root->right;
            new_node->right->p = new_node;
        }
        else
        {
            xx->p = new_node;
        }
        x = Transplant(x, root, new_node);
        new_node->left = root->left;
        new_node->left->p = new_node;
        // though we delete root, we do not delete root's color,
        // the color we delete is new_node's
        new_node->color = root->color;//although we
    }

    if (delete_color == BLACK)
        x = RBFixDelete(x, xx);

    delete root;
    return x;
}
int main()
{
    RBTree *root = new RBTree(5);
    root->left = Nil;
    root->right = Nil;
    root->p = Nil;

    Insert(root, 3);
    Insert(root, 7);
    Insert(root, 6);
    Insert(root, 4);
    Insert(root, 1);
    Insert(root, 2);
    Insert(root, 9);
    Insert(root, 8);
    RBTree *min = FindMin(root);
    cout << "min: " << min->val << endl;
    RBTree *max = FindMax(root);
    cout << "max: " << max->val << endl;
    min = search(root, 8);
    max = previous(min);
    cout << min->val << "previous: " << max->val << endl;
    min = search(root, 2);
    max = next(min);
    cout << min->val << "next: " << max->val << endl;
    Insert(root, 3);
    cout << "All insert finished" << endl;
    print(root);
    root = Delete(root, 3);
    cout << "3 is deleted" << endl;
    print(root);
    assert(search(root, 3) == Nil);
    root = Delete(root, 5);
    cout << "5 is deleted" << endl;
    print(root);
    root = Delete(root, 1);
    cout << "1 is deleted" << endl;
    print(root);
    root = Delete(root, 2);
    cout << "2 is deleted" << endl;
    print(root);
    root = Delete(root, 4);
    cout << "4 is deleted" << endl;
    print(root);
    root = Delete(root, 6);
    cout << "6 is deleted" << endl;
    print(root);
    root = Delete(root, 7);
    cout << "7 is deleted" << endl;
    print(root);
    root = Delete(root, 8);
    cout << "8 is deleted" << endl;
    print(root);
    root = Delete(root, 9);
    cout << "9 is deleted" << endl;
    print(root);
    assert(root == Nil);

    return 0;
}
