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
#include <queue>

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
    pos p(2U);
    switch(d)
    {
    case dir::east:
        p[0] = 0; p[1] = 1;
        break;
    case dir::south:
        p[0] = 1; p[1] = 0;
        break;
    case dir::west:
        p[0] = 0; p[1] = -1;
        break;
    case dir::north:
        p[0] = -1; p[1] = 0;
        break;
    }
    return p;
}

bool is_out_of_map(const pos& p, int width, int height)
{
    return p[0] < 0 || p[1] < 0 || p[0] >= height || p[1] >= width;
}

int pos_linear(const pos& p, int width)
{
    return p[0] * width + p[1];
}
pos pos_unlinear(int v, int width) 
{
    pos p(2U);
    p[0] = static_cast<int>(v / width);
    p[1] = static_cast<int>(v % width);
    return p;
}

dir get_opposite(dir d)
{
    switch(d)
    {
        case dir::north:
            return dir::south;
        case dir::south:
            return dir::north;
        case dir::west:
            return dir::east;
        case dir::east:
            return dir::west;
    }
    return {};
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
    using T = tuple<int, int, int, dir>;
    using TT = tuple<int, dir>;
    unordered_multimap<int, TT> m;
    auto cmp = [](const T& t0, const T& t1)
    {
        return get<0>(t0) > get<0>(t1);
    };
    priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);
    pos start(2);
    start[0] = start[1] = 0;
    const int width = map[0].size();
    const int height = map.size();
    start[0] = 0; start[1] = 0;
    for(dir dd : {dir::east, dir::north, dir::south, dir::west})
    {
        pos offset = get_offset(dd);
        pos res = start + offset;

    }
    pq.emplace(make_tuple(0, pos_linear(start, width), 0, dir::east));
    while(!pq.empty())    
    {
        auto [hl, p_lin, same_dir_cnt, d] = pq.top();
        pq.pop();
        if(same_dir_cnt > 3)
            continue;
        auto p = pos_unlinear(p_lin, width);
        if(is_out_of_map(p, width, height))
        {
            continue;
        }
        if(p[0] == height - 1 && p[1] == width - 1)
        {
            cout << hl << endl;
            break;
        }
        //cout << hl << " " << p[0] << "|" << p[1] << endl;
        
        bool b = false;
        if(m.contains(p_lin))
        {
            auto [f, e] = m.equal_range(p_lin);
            auto tt = make_tuple(same_dir_cnt, d);
            auto it = find_if(f, e, [&tt](const auto& p){
                return p.second == tt;
            });
            b = it != e;
        }
        if(b)
            continue;
        m.emplace(make_pair(p_lin, make_tuple(same_dir_cnt, d)));
        for(dir dd : {dir::east, dir::north, dir::south, dir::west})
        {
            if(dd == get_opposite(d))
                continue;
            pos offset = get_offset(dd);
            pos np = p + offset;
            if(is_out_of_map(np, width, height))
                continue;
            auto np_lin = pos_linear(np, width);
            int nhl = hl + static_cast<int>(map[np[0]][np[1]] - '0');
            if(dd == d)
            {
                pq.emplace(make_tuple(nhl, np_lin, same_dir_cnt + 1, dd));
            }
            else
                pq.emplace(make_tuple(nhl, np_lin, 1, dd));
        }
    }
    return 0;
}

