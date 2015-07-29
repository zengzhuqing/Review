#include <iostream>
#include <bitset>
#include <fstream>
using namespace std;
#define MAX_NUM 1000
#define CHAR_SZ 8
void use_stl()
{
    cout << "using stl bitset api" << endl;
    ifstream in("in");
    int v;
    bitset<MAX_NUM> record;
    while(in >> v)
    {
        cout << v << endl;
        record.set(v);
    }
    int t;
    cin >> t;
    cout << record.test(t) << endl; 
}

unsigned char array[MAX_NUM/CHAR_SZ];
void set(int pos)
{
    int idx = pos / CHAR_SZ;
    int p = pos % CHAR_SZ;
    array[idx] |= 1 << p; 
}
bool test(int pos)
{
    int idx = pos / CHAR_SZ;
    int p = pos % CHAR_SZ;
    return array[idx] & (1 << p); 
}
void self_realized()
{
    cout << "self realized version" << endl;
    ifstream in("in");
    int v;
    while(in >> v)
    {
        cout << v << endl;
        test(v);
    }
    int t;
    cin >> t;
    cout << test(t) << endl; 
}

int main()
{
    use_stl();

    return 0; 
}
