#include <fstream>
#include <unordered_set>
#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>

using namespace std;

auto toi(const char* s, size_t* p)
{
    long long c = 0LL;
    while(isdigit(s[*p]))
    {
        c = c * 10LL + static_cast<long long>(s[*p] - '0');
        (*p)++;
    }
    return c;
}

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
    vector<pair<int, int>> comb;
    size_t p = 0;
    int i = 0;
    while(getline(f,s))
    {
        while(p != string::npos)
        {
            p = find_c(s, p);
            if(p == string::npos)
                break;
            size_t offset = 0;
            auto v = stoi(string{begin(s) + p, end(s)}, &offset);
            p+=offset;
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
    int res = 1;
    for(auto [t, d] : comb)
    {
        int cnt = 0;
        for(int i = 1; i < t; ++i)
        {
            int rem = t - i;
            int current_dist = rem * i;
            if(current_dist > d)
                cnt++;
        }
        res *= cnt;
    }
    cout << res << endl;
    return 0;
}