#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class Solution {
public:
    int longest(string &s, int idx)
    {
        int odd = 0;
        int even = 0;
        int l, r;
        for(l = idx - 1, r = idx + 1; l >= 0 && r < s.size(); l--, r++)
        {
            if(s[l] != s[r])
                break;
        }
        odd = r - l - 1;
        for(l = idx, r = idx + 1; l >= 0 && r < s.size(); l--, r++)
        {
            if(s[l] != s[r])
                break;
        }
        even = r - l - 1;
        return max(odd, even);
    }
    string longestPalindrome(string s) {
        int ans = 0;
        int ans_head = 0;
        for(int i = 0; i < s.size(); i++)
        {
            if(2 * (s.size() - i) - 1 <= ans)
            {
                break;
            }
            else
            {
                int cur = longest(s, i);
                if(cur > ans)
                {
                    ans_head = i - (cur - 1) / 2;
                    ans = cur;
                }
            }
        }
        return s.substr(ans_head, ans);
    }
};
int main()
{
	string in;
	cin >> in;
	Solution sol;
	cout << sol.longestPalindrome(in) << endl;

	return 0;
}
