#include <fstream>
#include <numeric>
#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <ranges>

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

struct chars
{
    bool operator==(const chars& other) const
    {
        string_view a(&chs.front(), chs.size());
        string_view b(&other.chs.front(), other.chs.size());
        return a == b;
    }
    bool operator!=(const chars& other) const
    {
        return !((*this) == other);
    }
    array<char, 3> chs;
};

template<>
struct std::hash<chars>
{
    auto operator()(const chars& c) const
    {
        string_view s(&c.chs.front(), c.chs.size());
        return hash<string_view>{}(s);
    };
};

int main()
{
    ifstream f("input.txt", ios::in);
    string lr_steps;
    getline(f, lr_steps);
    unordered_map<chars, pair<chars, chars>> m;
    string s;
    getline(f, s);
    while(getline(f,s))
    {
        chars key;
        copy(begin(s), begin(s) + 3, begin(key.chs));
        auto it = find_if(begin(s) + 3, end(s), [](auto c){
            return isalpha(c);
        });
        chars left;
        copy(it, it + 3, begin(left.chs));
        it = find_if(it + 3, end(s), [](auto c){
            return isalpha(c);
        });
        chars right;
        copy(it, it + 3, begin(right.chs));
        m[key] = make_pair(left, right);
    }
    
    int cnt = 0;
    chars start;
    start.chs.fill('A');
    chars goal;
    goal.chs.fill('Z');
    int i = 0;
    while(start != goal)
    {
        char lr_step = lr_steps[i];
        if(lr_step == 'L')
        {
            start = m[start].first;
        }
        else
        {
            start = m[start].second;
        }
        i = (i + 1) % lr_steps.size();
        cnt++;
    }
    cout << cnt << endl;
    

    return 0;
}