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
    vector<chars> all_chars_ends_with_a;
    while(getline(f,s))
    {
        chars key;
        copy(begin(s), begin(s) + 3, begin(key.chs));
        auto it = find_if(begin(s) + 3, end(s), [](auto c){
            return isalpha(c);
        });
        if(key.chs.back() == 'A')
        {
            all_chars_ends_with_a.emplace_back(key);
        }
        chars left;
        copy(it, it + 3, begin(left.chs));
        it = find_if(it + 3, end(s), [](auto c){
            return isalpha(c);
        });
        chars right;
        copy(it, it + 3, begin(right.chs));
        m[key] = make_pair(left, right);
    }
    
    vector<unordered_map<chars, vector<pair<size_t, size_t>> >>checks(all_chars_ends_with_a.size());
    for(int i = 0; i < all_chars_ends_with_a.size(); ++i)
    {
        size_t it = 0;
        auto start = all_chars_ends_with_a[i];
        size_t cnt = 0;
        int k = 0;
        while (true)
        {
            if(start.chs.back() == 'Z')
            {
                auto& v = checks[i][start];
                auto fit = find_if(begin(v), end(v),[it](auto v){
                    return v.first == it;
                });
                bool b = fit != end(v);
                if(b)
                {
                    break;
                }
                v.emplace_back(it, cnt);
            }
            char lr_step = lr_steps[it];
            cnt++;
            if(lr_step == 'L')
            {
                start = m[start].first;
            }
            else
            {
                start = m[start].second;
            }
            it = (it + 1) % lr_steps.size();

        }
    }
    vector<size_t> freq;
    freq.reserve(all_chars_ends_with_a.size());
    for(auto& mm : checks)
    {
        for(auto& [_, v] : mm)
        {
            for(auto& [_, cnt] : v)
            {
                //remove offset
                cnt -= cnt % lr_steps.size();
            }
            freq.emplace_back(v.front().second);
        }
    }
    cout << "use wolfram alpha to solve following equation: \n";
    for(int i = 0; i < freq.size(); ++i)
    {
        cout << "k" << i << "*" << freq[i] << (i != freq.size() - 1 ? "=" : "");
    }
    cout << endl;
    

    return 0;
}