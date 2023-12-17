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

void get_cnt(const auto& map, pair<pos, dir> pp, unordered_map<int, vector<dir>>& v)
{
    const int width = map[0].size();
    const int height = map.size();
    auto [p, d] = pp;
    int sum = 0;

    if(is_out_of_map(p, width, height))
    {
        return;
    }
    int p_lin = pos_linear(p, width);
    if(v.contains(p_lin))
    {
        const auto& vv = v[p_lin];
        auto it = find(begin(vv), end(vv), d);
        if(it != end(vv))
        {
            return;
        }
    }
    v[p_lin].emplace_back(d);
    const char c = map[p[0]][p[1]];

    auto [nd, od] = get_dir(c, d);
    if(od.has_value())
    {
        v[p_lin].emplace_back(*od);
        auto offset = get_offset(*od);
        auto np = p + offset;
        get_cnt(map, make_pair(np, *od), v);
    }
    auto offset = get_offset(nd);
    auto np = p + offset;
    get_cnt(map, make_pair(np, nd), v);
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
    int m = 0;
    pos p(2);
    p[1] = p[0] = 0;
    unordered_map<int, vector<pair<dir, int>>> dp;
    for(int i = 0; i < map[0].size(); ++i)
    {
        unordered_map<int, vector<dir>> v;
        p[1] = i;
        get_cnt(map, make_pair(p, dir::south), v);
        m = max(m, static_cast<int>(v.size()));
    }
    p[0] = map.size()- 1;
    for(int i = 0; i < map[0].size(); ++i)
    {
        unordered_map<int, vector<dir>> v;
        p[1] = i;
        get_cnt(map, make_pair(p, dir::north), v);
        m = max(m, static_cast<int>(v.size()));
    }
    p[1] = 0;
    for(int i = 0; i < map.size(); ++i)
    {
        unordered_map<int, vector<dir>> v;
        p[0] = i;
        get_cnt(map, make_pair(p, dir::east), v);
        m = max(m, static_cast<int>(v.size()));
    }
    p[1] = map[0].size() - 1;
    for(int i = 0; i < map.size(); ++i)
    {
        unordered_map<int, vector<dir>> v;
        p[0] = i;
        get_cnt(map, make_pair(p, dir::west), v);
        m = max(m, static_cast<int>(v.size()));
    }
    cout << m << endl;
    return 0;
}