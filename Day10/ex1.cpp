#include <fstream>
#include <numeric>
#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <ranges>
#include <valarray>
#include <optional>

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

bool is_orthogonal(dir d0, dir d1)
{
    if(d0 == dir::east || d0 == dir::west)
    {
        return d1 == dir::north || d1 == dir::south;
    }
    if(d0 == dir::north || d0 == dir::south)
    {
        return d1 == dir::west || d1 == dir::east;
    }
    return false;
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


bool is_out_of_bound(pos p, pair<size_t, size_t> width_height)
{
    const size_t width = width_height.first;
    const size_t height = width_height.second;
    return (p[1] < 0 || p[0] < 0 || p[1] >= width || p[0] >= height);
}

optional<dir> get_next_dir(pos p, dir d, const auto& map, const auto& mapping)
{
    char c = map[p[0]][p[1]];
    if(c == '.')
        return {};
    auto [d0, d1] = mapping.at(c);
    if(get_opposite(d) == d0)
    {
        if(is_orthogonal(d, d1))
            return d1;
        return d;
    }
    if(get_opposite(d) == d1)
    {
        if(is_orthogonal(d, d0))
            return d0;
        return d;
    }
    return {};
}

bool is_at_start(pos p, const auto& map)
{
    return map[p[0]][p[1]] == 'S';
}





int main(int argc, char** argv)
{
    ifstream f(argv[1], ios::in);
    vector<string> map;
    string s;
    int sr = 0;
    int sc = -1;
    while(getline(f,s))
    {
        if(sc == -1)
        {
            auto it = find(begin(s), end(s), 'S');
            if(it != end(s))
            {
                sc = distance(begin(s), it);
            }
        }
        map.emplace_back(move(s));
        if(sc == -1)
            sr++;
    }
    const size_t width = map[0].size();
    const size_t height = map.size();
    const unordered_map<char, pair<dir, dir>> mapping{
        {'|', make_pair(dir::north, dir::south)},
        {'-', make_pair(dir::east, dir::west)},
        {'L', make_pair(dir::north, dir::east)},
        {'J', make_pair(dir::north, dir::west)},
        {'7', make_pair(dir::south, dir::west)},
        {'F', make_pair(dir::south, dir::east)},
    };
    
    pos start{sr, sc};
    int gmax = -1;
    for(auto d : {dir::east, dir::north, dir::south, dir::west})
    {
        pos next_pos = get_offset(d) + start;
        dir next_coming_dir = d;
        if(is_out_of_bound(next_pos, make_pair(width, height)))
            continue;
        int cnt = 1;
        while(true)
        {
            if(is_at_start(next_pos, map))
            {
                cnt /= 2;
                break;
            }
            auto next_dir_opt = get_next_dir(next_pos, d, map, mapping);
            if(!next_dir_opt.has_value())
            {
                cnt = -1;
                break;
            }
            d = *next_dir_opt;
            next_pos = get_offset(d) + next_pos;
            if(is_out_of_bound(next_pos, make_pair(width, height)))
            {
                cnt = -1;
                break;
            }
            cnt++;
        }
        gmax = max(cnt, gmax);
    }
    cout << gmax << endl;
    

    return 0;
}