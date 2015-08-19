#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
int fx[4] = {-1,1,0,0};
int fy[4] = {0,0,-1,1};
const char *op = "udlr";
int id(char ch)
{
    return strchr(op, ch) - op;
}
bool test(vector<vector<int> > room, pair<int, int> user, pair<int, int> box, string in)
{
    if(room.size() == 0 || room[0].size() == 0)
    {
        return false;
    } 
    for(int i = 0; i < in.size(); i++)
    {
        int idx = id(in[i]);
        int x = user.first + fx[idx];
        int y = user.second + fy[idx];
        if(x >= 0 && x < room.size() && y >= 0 && y < room[0].size())
        {
            int cur = room[x][y];
            if(cur == 0 || cur == 2)
            {
                room[user.first][user.second] = 0;
                room[x][y] = 1;
                user.first = x;
                user.second = y; 
            }
            else if(cur == 3)
            {
                int xx = user.first + fx[idx] * 2;      
                int yy = user.second + fy[idx] * 2;
                if(xx >= 0 && xx < room.size() && yy >= 0 && yy < room[0].size())
                {   
                    int cur = room[xx][yy];
                    if(cur == 0 || cur == 2)
                    {
                        room[user.first][user.second] = 0;
                        room[x][y] = 1;
                        if(cur == 2)
                            return true;
                        room[xx][yy] = 3;
                        user.first = x;
                        user.second = y;
                        box.first = xx;
                        box.second = yy;  
                    } 
                } 
            } 
        }
    }
    return false; 
}
int main()
{
    int N, M, S;
    cin >> N >> M >> S;
    vector<vector<int> > room;
    pair<int, int> user;
    pair<int, int> box;
    for(int i = 0; i < M; i++)
    {
        string cur;
        cin >> cur;
        vector<int> line;
        for(int j = 0; j < cur.size(); j++)
        {
            int num = cur[j] - '0';
            if(num == 1)
            {
                user.first = i;
                user.second = j; 
            }
            if(num == 3)
            {
                box.first = i;
                box.second = j;
            } 
            line.push_back(num); 
        } 
        room.push_back(line);
    }
    vector<string> inputs(S);
    for(int i = 0; i < S; i++)
    {
        int t;
        cin >> t >> inputs[i];
        if(test(room, user, box, inputs[i]))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
      
    return 0;
}
