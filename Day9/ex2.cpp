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
        return isdigit(c) || c == '-';
    });
    return it == end(s) ? string::npos : distance(begin(s), it);
}

auto get_val(const auto& seq, auto& res)
{
    bool is_all_zeros = accumulate(begin(seq), end(seq), true, [](bool init, int nvl){
        return init && nvl == 0LL;
    });
    if(is_all_zeros)
    {
        res = 0LL;
        return;
    }
    vector<int> v;
    adjacent_difference(begin(seq), end(seq), back_inserter(v));
    get_val(vector<int>{std::next(begin(v)), end(v)}, res);
    res = seq.front() - res;
}

int main(int argc, char** argv)
{
    ifstream f(argv[1], ios::in);
    string s;
    size_t p = 0;
    long long sum = 0;
    while(getline(f,s))
    {
        vector<long long> v;
        while ((p = find_c(s, p)) != string::npos)
        {
            size_t offset = 0;
            auto val = stoll(string{begin(s)+ p, end(s)}, &offset);
            p += offset;
            v.emplace_back(val);
        }
        p = 0;
        long long part = 0;
        get_val(v, part);
        sum += part;
    }
    
    cout << sum << endl;
    

    return 0;
}