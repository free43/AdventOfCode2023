#include <fstream>
#include <numeric>
#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <ranges>
#include <valarray>
#include <optional>
#include <list>
#include <unordered_set>

using namespace std;


using pos = valarray<int>;

enum struct dir
{
    north,
    west,
    south,
    east,
};


pos get_offset(dir d)
{
    switch(d)
    {
    case dir::east:
        return {0, 1};
    case dir::south:
        return {1, 0};
    case dir::west:
        return {0, -1};
    case dir::north:
        return {-1, 0};
    }
    return {0,0};
}

pair<dir, optional<dir>> get_dir(char c, dir d)
{
    switch (c)
    {
    case '/':
        switch (d)
        {
        case dir::north:
            return {dir::east, {}};
        case dir::south:
            return {dir::west, {}};
        case dir::east:
            return {dir::north, {}};
        case dir::west:
            return {dir::south, {}};
        }
        break;
    case '\\':
        switch (d)
        {
        case dir::north:
            return {dir::west, {}};
        case dir::south:
            return {dir::east, {}};
        case dir::east:
            return {dir::south, {}};
        case dir::west:
            return {dir::north, {}};
        }
        break;
    case '-':
        switch (d)
        {
        case dir::north:
        case dir::south:
            return {dir::west, dir::east};
        case dir::east:
        case dir::west:
            return {d, {}};
        }
        break;
    case '|':
        switch (d)
        {
        case dir::north:
        case dir::south:
            return {d, {}};
        case dir::east:
        case dir::west:
            return {dir::north, dir::south};
        }
        break;
    }
    return {d, {}};
}

bool is_out_of_map(pos p, int width, int height)
{
    return p[0] < 0 || p [1] < 0 || p[0] >= height || p[1] >= width;
}

int pos_linear(const pos& p, int width)
{
    return p[0] * width + p[1];
}

int main(int argc, char** argv)
{
    ifstream f(argv[1], ios::in);
    string s;
    vector<string> map;
    while(getline(f, s))
    {
        map.emplace_back(move(s));
    }
    list<pair<pos, dir>> l;
    using IT = decltype(l)::iterator;
    unordered_map<int, vector<dir>> v;
    const int width = map[0].size();
    const int height = map.size();
    l.emplace_back(initializer_list{0, 0}, dir::east);
    while(!l.empty())
    {
        vector<pair<pos, dir>> to_emplace;
        vector<IT> to_rem;
        for(auto i = begin(l); i != end(l); ++i)
        {
            auto& [p, d] = *i;
            if(is_out_of_map(p, width, height))
            {
                to_rem.emplace_back(i);
                continue;
            }
            int p_lin = pos_linear(p, width);
            const char c = map[p[0]][p[1]];
            if(c == '.')
            {
                map[p[0]][p[1]] = '#';
            }
            if(v.contains(p_lin))
            {
                const auto& vv = v[p_lin];
                auto it = find(begin(vv), end(vv), d);
                if(it != end(vv))
                {
                    to_rem.emplace_back(i);
                    continue;
                }
            }
            v[p_lin].emplace_back(d);
            auto [nd, od] = get_dir(c, d);
            if(od.has_value())
            {
                v[p_lin].emplace_back(*od);
                auto offset = get_offset(*od);
                auto np = p + offset;
                to_emplace.emplace_back(np, *od);
            }
            p += get_offset(nd);
            d = nd;
        }
        for(auto i : to_rem)
            l.erase(i);
        for(auto& p : to_emplace)
            l.emplace_back(move(p));
    }
    for_each(begin(map), end(map), [](const auto& s){
        cout << s << endl;
    });
    cout << v.size() << endl;
    return 0;
}