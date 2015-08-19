#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool test(vector<vector<int> > room, pair<int, int> user, pair<int, int> box, string in)
{
    if(room.size() == 0 || room[0].size() == 0)
    {
        return false;
    } 
    for(int i = 0; i < in.size(); i++)
    {
        if(room[box.first][box.second] == 2)
        {
            //reach
            return true;    
        }
        if(in[i] == 'u' && user.first != 0 )
        {
            int up = room[user.first - 1][user.second];
            if(up == 0 || up == 2)
            {
                //update room, user
                room[user.first][user.second] = 0;
                room[user.first - 1][user.second] = 1;
                user.first--;    
            }
            else if(up == 4)
            {
                //do nothing  
            }
            else if(up == 3 && user.first >= 2)
            {
                //test upup, if OK, update room, user, box, otherwise, do nothing
                int upup = room[user.first - 2][user.second];
                if(upup == 0 || upup == 2)
                {
                    if(upup == 2)
                    {
                        return true; 
                    }
                    room[user.first][user.second] = 0;
                    room[user.first - 1][user.second] = 1;
                    room[user.first - 2][user.second] = 3;
                    user.first--;
                    box.first--;
                }
            }
        }
        else if(in[i] == 'd' && user.first + 1 != room.size())
        {
            int down = room[user.first + 1][user.second];
            if(down == 0 || down == 2)
            {
                //update room, user
                room[user.first][user.second] = 0;
                room[user.first + 1][user.second] = 1;
                user.first++;    
            }
            else if(down == 4)
            {
                //do nothing  
            }
            else if(down == 3 && user.first + 3 <= room.size())
            {
                //test downdown, if OK, update room, user, box, otherwise, do nothing
                int downdown = room[user.first + 2][user.second];
                if(downdown == 0 || downdown == 2)
                {
                    if(downdown == 2)
                    {
                        return true; 
                    }
                    room[user.first][user.second] = 0;
                    room[user.first + 1][user.second] = 1;
                    room[user.first + 2][user.second] = 3;
                    user.first++;
                    box.first++;
                }
            }
            
        }
        else if(in[i] == 'l' && user.second != 0)
        {
            int left = room[user.first][user.second - 1];
            if(left == 0 || left == 2)
            {
                //update room, user
                room[user.first][user.second] = 0;
                room[user.first][user.second - 1] = 1;
                user.second--;    
            }
            else if(left == 4)
            {
                //do nothing  
            }
            else if(left == 3 && user.second >= 2)
            {
                //test leftleft, if OK, update room, user, box, otherwise, do nothing
                int leftleft = room[user.first][user.second - 2];
                if(leftleft == 0 || leftleft == 2)
                {
                    if(leftleft == 2)
                    {
                        return true; 
                    }
                    room[user.first][user.second] = 0;
                    room[user.first][user.second - 1] = 1;
                    room[user.first][user.second - 2] = 3;
                    user.second--;
                    box.second--;
                }
            }
        }
        else if(in[i] == 'r' && user.second + 1 != room[0].size())
        {
            int right = room[user.first][user.second + 1];
            if(right == 0 || right == 2)
            {
                //update room, user
                room[user.first][user.second] = 0;
                room[user.first][user.second + 1] = 1;
                user.second++;    
            }
            else if(right == 4)
            {
                //do nothing  
            }
            else if(right == 3 && user.second + 3 <= room[0].size())
            {
                //test rightright, if OK, update room, user, box, otherwise, do nothing
                int rightright = room[user.first][user.second + 2];
                if(rightright == 0 || rightright == 2)
                {
                    if(rightright == 2)
                    {
                        return true; 
                    }
                    room[user.first][user.second] = 0;
                    room[user.first][user.second + 1] = 1;
                    room[user.first][user.second + 2] = 3;
                    user.second++;
                    box.second++;
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
