#include <fstream>
#include <unordered_map>
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
    if(c < 0)
        cout << c << endl;
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
int main(int argc, char const *argv[])
{
    ifstream f("input.txt", ios::in);
    string s;
    getline(f, s);
    size_t p = 0;
    vector<long long> seeds;
    while(p < s.size())
    {
        p = find_c(s, p);
        if(p == string::npos)
            break;
        long long c = toi(s.data(), &p);
        seeds.emplace_back(c);
    }
    auto eat_three_newlines = [&f]{
        string s;
        getline(f, s);
        getline(f, s);
        getline(f, s);
    };
    eat_three_newlines();
    auto is_in_range = [](auto seed, auto range)
    {
        return seed >= range.first && seed <= range.second;
    };
    while(getline(f, s))
    {
        vector<long long> next_seeds;
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
            for(auto& seed : seeds)
            {
                long long src_end = src_start + range;
                if(is_in_range(seed, make_pair(src_start, src_end)))
                {
                    long long offset = seed - src_start;
                    long long next = dest_start + offset;
                    next_seeds.emplace_back(next);
                    seed = -1LL;
                }
            }
        }while (getline(f,s));
        for(auto v : seeds)
        {
            if(v != -1)
            {
                next_seeds.emplace_back(v);
            }
        }
        seeds = next_seeds;
        if(!f)
            break;        
        getline(f, s);
        getline(f, s);
    }
    int m = *min_element(begin(seeds), end(seeds));
    cout << m << endl;
    return 0;
}
