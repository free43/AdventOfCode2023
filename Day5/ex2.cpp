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
    while(!isdigit(s[p]))
    {
        p++;
        if(p >= s.size())
            return string::npos;
    }
    return p;
}
auto get_min(auto p, const auto& mapping, int idx) -> long long
{
    if(idx >= mapping.size())
        return p.first;
    auto init_min = static_cast<long long>(INT64_MAX);
    bool found = false;
    for(const auto& ary : mapping[idx])
    {
        auto [s, e] = p;
        auto dst_start = ary[0];
        auto src_start = ary[1];
        auto src_range = ary[2];
        auto src_end = src_start + src_range - 1;
        auto dst_end = dst_start + src_range - 1;
        if(e < src_start)
        {
            
        }
        else
        {
            if(s > src_end)
            {
            }
            else
            {
                found = true;
                if(s == src_start && e == src_end)
                {
                    init_min = min(init_min, get_min(make_pair(dst_start, dst_end), mapping, idx + 1));
                }
                else if(s <= src_start && e <= src_end)
                {
                    auto diff = e - src_start;
                    init_min = min(init_min, get_min(make_pair(dst_start, dst_start + diff), mapping, idx + 1));
                    if(src_start > s)
                        init_min = min(init_min, get_min(make_pair(s, src_start - 1), mapping, idx));
                }
                else if(e >= src_end && s <= src_start)
                {
                    init_min = min(init_min, get_min(make_pair(dst_start, dst_end), mapping, idx + 1));
                    if(src_start > s)
                        init_min = min(init_min, get_min(make_pair(s, src_start - 1), mapping, idx));
                    if(e > src_end)
                       init_min = min(init_min, get_min(make_pair(src_end + 1, e), mapping, idx));
                }
                else if(s >= src_start && e >= src_end)
                {
                    auto diff = s - src_start;
                    init_min = min(init_min, get_min(make_pair(dst_start + diff, dst_end), mapping, idx + 1));
                    if(e > src_end)
                        init_min = min(init_min, get_min(make_pair(src_end + 1, e), mapping, idx));
                }
                else if(s >= src_start && e <= src_end)
                {
                    auto ldiff = s - src_start;
                    auto hdiff = src_end - e;
                    init_min = min(init_min, get_min(make_pair(dst_start + ldiff, dst_end - hdiff), mapping, idx + 1));
                }
            }  
        }
    }
    if(!found)
        init_min = min(init_min, get_min(p, mapping, idx + 1));
    return init_min;
}

int main(int argc, char const *argv[])
{
    ifstream f("input.txt", ios::in);
    string s;
    getline(f, s);
    size_t p = 0;
    vector<pair<long long, long long>> seeds;
    int i = 0;
    while(p < s.size())
    {
        p = find_c(s, p);
        if(p == string::npos)
            break;
        long long start = toi(s.data(), &p);
        p = find_c(s, p);
        long long offset = toi(s.data(), &p);
        seeds.emplace_back(make_pair(start, offset));
    }
    auto eat_two_newlines = [&f]{
        string s;
        getline(f, s);
        getline(f, s);
    };
    eat_two_newlines();
    auto is_in_range = [](auto seed, auto range)
    {
        return seed >= range.first && seed <= range.second;
    };
    vector<vector<array<long long, 3>>> mapping;
    while(getline(f, s))
    {
        vector<array<long long, 3>> tmp;
        do
        {
            if(!isdigit(s[0]))
                break;
            p = 0;
            long long dest_start = toi(s.data(), &p);
            p = find_c(s, p);
            long long src_start = toi(s.data(), &p);
            p = find_c(s, p);
            long long range = toi(s.data(), &p);
            tmp.push_back(array<long long, 3>{dest_start, src_start, range});
        }while (getline(f,s));
        mapping.emplace_back(move(tmp));
        if(!f)
            break;        
        getline(f, s);
    }

    long long mn = INT64_MAX;
    for(auto [start, range] : seeds)
    {
        auto m = get_min(make_pair(start, start + range), mapping, 0);
        mn = min(mn, m);
    }
    cout << mn << endl;
    return 0;
}
