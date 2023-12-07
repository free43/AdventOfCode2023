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


const array labels{'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'}; 

int get_type(array<char, 5> cards)
{ 
    ranges::sort(cards);
    int cnt = 1;
    vector<int> diffs;
    char b = cards.front();
    for(int i = 1; i < cards.size(); ++i)
    {
        if(cards[i] != b)
        {
            diffs.emplace_back(cnt);
            cnt = 0;
            b = cards[i];
        }
        cnt++;
    }
    diffs.emplace_back(cnt);
    if(diffs.size() == 1)
        return 0;
    ranges::sort(diffs);
    if(diffs.size() == 2)
    {
        if(diffs.front() == 1)
            return 1;
        return 2;
    }
    if(diffs.size() == 3)
    {
        if(diffs.back() == 3)
            return 3;
        return 4;
    }
    return diffs.size() + 1;
    
}

int main()
{
    ifstream f("input.txt", ios::in);
    string s;
    vector<tuple<array<char, 5>,int, size_t>> comb;
    size_t p = 0;
    while(getline(f,s))
    {
        array<char, 5> tmp;
        for(int i = 0; i < tmp.size(); ++i)
        {
            tmp[i] = s[i];
        }
        int type = get_type(tmp);
        string_view ss(begin(s) + 5, end(s));
        while(p != string::npos)
        {
            p = find_c(ss, p);
            if(p == string::npos)
                break;
            size_t offset = 0;
            auto v = stoul(string{begin(ss) + p, end(ss)}, &offset);
            p += offset;
            comb.emplace_back(tmp, type, v);
        }
        p = 0;
    }
    unordered_map<char, int> m;
    for(int i = 0; i < labels.size(); ++i)
        m[labels[i]] = i;
    ranges::sort(comb, [&m](const auto& a, const auto& b){
        auto [cards0, type0, _] = a;
        auto [cards1, type1, __] = b;
        if(type0 == type1)
        {
            for(int i = 0; i < cards0.size(); ++i)
            {
                int v0 = m.at(cards0[i]);
                int v1 = m.at(cards1[i]);
                if(v0 < v1)
                    return true;
                else if(v0 > v1)
                    return false;
            }
            return false;
        }
        else
            return type0 < type1;
    });
    size_t rank = comb.size();
    auto res = accumulate(begin(comb), end(comb), 0U, [&rank](auto init, const auto& v){
        auto [_, __, amount] = v;
        init += rank * amount;
        rank--;
        return init;
    });
    cout << res << endl;
    return 0;
}