#include <fstream>
#include <numeric>
#include <iostream>
#include <string_view>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <ranges>
#include <valarray>
#include <optional>

using namespace std;


bool is_valid(const string& s, const vector<int>& v)
{
    int i = 0;
    int cnt = -1;
    for(auto c : s)
    {
        if(c == '#')
        {
            if(cnt < 0)
                cnt = 1;
            else
            {
                cnt++;
            }
        }
        else
        {
            if(cnt > 0)
            {
                if(i >= v.size())
                    return false;
                if(v[i] != cnt)
                    return false;
                i++;
            }
            cnt = -1;
        }
    }
    if(i >= v.size() && cnt > 0)
        return false;
    if(i >= v.size())
        return true;
    if(i + 1 != v.size())
        return false;
    return v[i] == cnt;
}

void cnt_pos(string& s, const vector<int>& v, int i, int& cnt)
{
    if(i >= s.size())
    {
        if(is_valid(s, v))
            cnt++;
        return;
    }
    for(int ii = i; ii < s.size(); ++ii)
    {
        if(s[ii] == '?')
        {
            s[ii] = '.';
            cnt_pos(s, v, ii + 1, cnt);
            s[ii] = '#';
            cnt_pos(s, v, ii + 1, cnt);
            s[ii] = '?';
            return;
        }
    }
    if(is_valid(s, v))
        cnt++;
}





int main(int argc, char** argv)
{
    ifstream f(argv[1], ios::in);
    string s;
    size_t r = 0;
    size_t c = 0;
    vector<string> conditions;
    vector<vector<int>> numbs;
    while(getline(f,s))
    {
        c = s.size();
        auto it = find(begin(s), end(s), ' ');
        conditions.emplace_back(begin(s), it);
        numbs.emplace_back();
        while((it = find_if(it, end(s), [](auto c){
            return isdigit(c);
        })) != end(s))
        {
            size_t offset;
            int i = stoi(string{it, end(s)}, &offset);
            numbs.back().emplace_back(i);
            it = next(it, offset);
        }
 
    }
    for(int i = 0; i < conditions.size(); ++i)
    {
        cout << conditions[i] << " : ";
        for(auto v : numbs[i])
            cout << v << ", ";
        cout << endl;
    }
    int sum = 0;
    for(int i = 0; i <conditions.size(); ++i)
    {
        cnt_pos(conditions[i], numbs[i], 0, sum);
    }
    cout << sum << endl;

    return 0;
}