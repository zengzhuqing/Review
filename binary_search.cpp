#include <iostream>
#include <vector>
using namespace std;
int bsearch(vector<int> &A, int val)
{
    int left = 0;
    int right = A.size() - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (A[mid] == val)
        {
            return mid;
        }
        else if (A[mid] < val)
        {
            left = mid + 1; 
        }
        else
        {
            right = mid - 1;
        }  
    }
    return -1; 
}
int binary_search(vector<int> &A, int val)
{
    int left = 0;
    int right = A.size() - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (A[mid] == val)
        {
            if (mid == 0 || A[mid - 1] < A[mid])
                return mid;
            else
                right = mid - 1;  
        }
        else if (A[mid] < val)
        {
            left = mid + 1; 
        }
        else
        {
            right = mid - 1;
        }  
    }
    return -1; 
}
vector<int>::iterator upper_bound(vector<int> &A, int val)
{
    int left = 0;
    int right = A.size() - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (A[mid] <= val)
        {
            left = mid + 1; 
        }     
        else
        {
            if(mid == 0 || A[mid - 1] <= val)
                return A.begin() + mid; 
            else
                right = mid - 1;  
        }
    }
    return A.end(); 
}
vector<int>::iterator lower_bound(vector<int> &A, int val)
{
    int left = 0;
    int right = A.size() - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (A[mid] < val)
        {
            left = mid + 1; 
        }     
        else
        {
            if(mid == 0 || A[mid - 1] < val)
                return A.begin() + mid; 
            else
                right = mid - 1;  
        }
    }
    return A.end(); 
}
int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int v;
    cin >> v;
    cout << "binary search:" << binary_search(A, v) << endl; 
    cout << "upper bound:" << upper_bound(A, v)  - A.begin() << endl; 
    cout << "lower bound:" << lower_bound(A, v)  - A.begin() << endl; 
 
    return 0;
}
