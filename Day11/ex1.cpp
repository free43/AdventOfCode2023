#include <fstream>
#include <numeric>
#include <iostream>
#include <string_view>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <ranges>
#include <valarray>
#include <optional>

using namespace std;


using pos = valarray<int>;


void build_pairs(const vector<pos>& poses, vector<pair<pos, pos>>& res)
{
    for(int i = 0; i < poses.size(); ++i)
    {
        for(int ii = i + 1; ii < poses.size(); ii++)
        {
            res.emplace_back(poses[i], poses[ii]);
        }
    }
}



int get_cnt(const auto& pairs)
{
    int cnt = 0;
    for(auto [start, goal] : pairs)
    {
       cnt += abs(goal - start).sum();
    }
    return cnt;
}




int main(int argc, char** argv)
{
    ifstream f(argv[1], ios::in);
    string s;
    size_t r = 0;
    size_t c = 0;
    unordered_set<int> r_wo_gx;
    unordered_set<int> c_w_gx;
    while(getline(f,s))
    {
        c = s.size();
        auto it = find(begin(s), end(s), '#');
        if(it == end(s))
        {
            r_wo_gx.emplace(r);
        }
        else
        {
            while(it != end(s))
            {
                int d = distance(begin(s), it);
                c_w_gx.emplace(d);
                it = find(it + 1, end(s), '#');
            } 
        }
        r++;
    }
    f.clear();
    f.seekg(ios_base::beg);
    r = 0;
    size_t r_i = 0;
    vector<pos> poses;
    while(getline(f,s))
    {
        size_t c = 0;
        for(size_t c = 0, c_i = 0; c < s.size(); ++c, c_i++)
        {
            if(!c_w_gx.contains(c))
            {
                c_i++;
            }
            if(s[c] == '#')
            {
                pos p{static_cast<int>(r_i), static_cast<int>(c_i)};
                poses.emplace_back(move(p));
            }
        }
        if(r_wo_gx.contains(r))
            r_i++;
        r_i++;
        r++;
    }

    vector<pair<pos, pos>> pairs;
    build_pairs(poses, pairs);
    cout << get_cnt(pairs) << endl;


    return 0;
}