#include <fstream>
#include <unordered_set>
#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>

using namespace std;

size_t find_c(string_view s, size_t p)
{
    if(p >= s.size())
        return string::npos;
    auto it = find_if(begin(s) + p, end(s), [](char c){
        return isdigit(c);
    });
    return it == end(s) ? string::npos : distance(begin(s), it);
}

int main()
{
    ifstream f("input.txt", ios::in);
    string s;
    vector<pair<long long, long long>> comb;
    size_t p = 0;
    int i = 0;
    while(getline(f,s))
    {
        auto newend = remove(begin(s), end(s), ' ');
        string_view ss {begin(s), newend};
        while(p != string::npos)
        {
            p = find_c(ss, p);
            if(p == string::npos)
                break;
            size_t offset = 0;
            auto v = stoll(string{begin(ss) + p, end(ss)}, &offset);
            p += offset;
            if(i == 0)
            {
                comb.emplace_back(v, 0);
            }
            else
            {
                comb[i - 1].second = v;
                i++;
            }
        }
        p = 0;
        i++;
    }
    long long res = 1;
    for(auto [t, d] : comb)
    {
        long long cnt = 0;
        for(long long i = 1; i < t; ++i)
        {
            long long rem = t - i;
            long long current_dist = rem * i;
            if(current_dist > d)
                cnt++;
        }
        res *= cnt;
    }
    cout << res << endl;
    return 0;
}