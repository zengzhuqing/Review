#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;
int f[8][3] = {
    {0,1,2},
    {3,4,5},
    {6,7,8},
    {0,3,6},
    {1,4,7},
    {2,5,8},
    {0,4,8},
    {2,4,6} 
};
int check_x[9];
int check_o[9];
int check[9];
void build_check(char *s, char ch, int check[])
{
    for(int i = 0; i < 8; i++)
    {
        check[i] = 1;
        for(int j = 0; j < 3; j++)
            if(s[f[i][j]] != ch)
                check[i] = 0; 
    }      
}
bool next_win(char *s, char ch)
{
    for(int i = 0; i < 9; i++)
    {
        if(s[i] == '_')
        {
            s[i] = ch;
            build_check(s, ch, check);
            if(count(check, check + 8, 1))
                return true;   
            s[i] = '_'; 
        } 
    }
    return false;
}
void test(char *s)
{
    int cntx = count(s, s + 9, 'X');
    int cnto = count(s, s + 9, 'O');
    if(cntx != cnto && cntx - 1 != cnto)
    {
        cout << "Invalid" << endl;
        return;
    }
    build_check(s, 'X', check_x);
    build_check(s, 'O', check_o);
    int ok_x = count(check_x, check_x + 8, 1);   
    int ok_o = count(check_o, check_o + 8, 1);
    if(ok_x > 0 && ok_o > 0)
    {
        cout << "Invalid" << endl;
        return;
    }
    if(ok_x > 0 && cntx == cnto)
    {
        cout << "Invalid" << endl;
        return;
    }
    if(ok_o > 0 && cntx != cnto)
    {
        cout << "Invalid" << endl;
        return;
    }
    if(ok_x > 0)
    {
        cout << "X win" << endl;
        return; 
    }     
    if(ok_o > 0)
    {
        cout << "O win" << endl;
        return; 
    }
    if(count(s, s + 9, '_') == 0)
    {
        cout << "Draw" << endl;
        return; 
    } 
    if(next_win(s, cntx > cnto ? 'O' : 'X'))
    {
        cout << "Next win" << endl;
        return; 
    }
    else
    {
        cout << "Next can not win" << endl;
        return; 
    } 
}
int main()
{
    int N;
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        char in[10];
        scanf("%s", in);  
        scanf("%s", in + 3);  
        scanf("%s", in + 6);
        test(in);  
    }
 
    return 0;
}
