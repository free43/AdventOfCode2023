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
using myint = long long;

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
        else if(c == '.')
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

bool is_sub_valid(const string& s, int v, int i)
{
    int cnt = -1;
    if(i > 0 && s[i - 1] == '#')
        return false;
    for(; i < s.size(); ++i)
    {
        if(s[i] == '#')
        {
            if(cnt < 0)
            {
                cnt = 1;
            }
            else
            {
                cnt++;
            }

        }
        else if(s[i] == '?')
        {
            if(cnt < v)
                cnt++;
            else if(cnt == v)
                return true;
        }
        else
        {
            if(cnt > 0)
            {
                return v == cnt;
            }
        }
    }
    return cnt == v;
}

auto cnt_pos(string& s, const vector<int>& v, int i, int vi, auto& dp) -> myint
{
    if(i > s.size())
        return 0;
    if(i == s.size())
    {
        if(vi >= v.size())
            return 1;
        return 0;
    }
    myint ret = 0;
    if(s[i] == '#')
    {
        if(vi >= v.size())
            return 0;
        if(is_sub_valid(s, v[vi], i))
        {
            string tmp = s;
            if(i + v[vi] > s.size())
                return 0;
            fill_n(begin(tmp) + i, v[vi], '#');
            ret += cnt_pos(tmp, v, i + v[vi], vi + 1, dp);
        }
        else
        {
            ret += 0;
        }
    }
    if(s[i] == '?')
    {
        s[i] = '#';
        if(dp[i][vi][0].has_value() && is_sub_valid(s, v[vi], i))  
            ret += *dp[i][vi][0];
        else
        {
            dp[i][vi][0] = cnt_pos(s, v, i, vi, dp);
            ret += *dp[i][vi][0];
        }
        s[i] = '.';
        if(dp[i][vi][1].has_value())
            ret += *dp[i][vi][1];
        else
        {
            dp[i][vi][1] = cnt_pos(s, v, i, vi, dp);
            ret += *dp[i][vi][1]; 
        }
        
        s[i] = '?';
    }
    if(s[i] == '.')
    {
        ret += cnt_pos(s, v, i + 1, vi, dp);
    }
    return ret;
}
auto cnt_pos(string& s, const vector<int>& v)
{
    
    vector<
    vector<
    vector<optional<myint> >>> dp(s.size() + 1, vector<vector<optional<myint>>>(v.size() + 1, vector<optional<myint>>(2), {}));
    return cnt_pos(s, v, 0, 0, dp);
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
        string ss{begin(s), it};
        conditions.emplace_back(ss);
        for(int i = 0; i < 4; ++i)
        {
            conditions.back() += '?' + ss;
        }
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
        int sz = numbs.back().size();
        for(int i = 0; i < 4; ++i)
        {
            for(int k = 0; k < sz; ++k)
            {
                numbs.back().emplace_back(numbs.back()[k]);
            }
        }
    }
    for(int i = 0; i < conditions.size(); ++i)
    {
        cout << conditions[i] << " : ";
        for(auto v : numbs[i])
            cout << v << ", ";
        cout << endl;
    }
    
    myint sum = 0;
    for(int i = 0; i < conditions.size(); ++i)
    {
        auto tmp = cnt_pos(conditions[i], numbs[i]);
        cout << tmp << endl;
        sum += tmp;
    }
    cout << sum << endl;

    return 0;
}