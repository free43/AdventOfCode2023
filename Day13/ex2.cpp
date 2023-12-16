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
#include <queue>

using namespace std;

int get_diff_cnt(string_view s0, string_view s1)
{
    int cnt = 0;
    int indx = 0;
    for(int i = 0; i < s0.size(); ++i)
    {
        cnt += static_cast<int>(s0[i] != s1[i]);
    }
    return cnt;
}

int analyze_h(const vector<string>& lines)
{
    for(int mid = 1; mid < lines.size(); mid++)
    {
        bool r = true;
        bool has_wrong_sign = false;
        for(int i = mid - 1, j = mid; i >= 0 && j < lines.size(); i--, j++)
        {
            int cnt = get_diff_cnt(lines[i], lines[j]);
            if(cnt == 1)
            {
                has_wrong_sign = true;
            }
            else
                r = r && (cnt == 0);
            if(!r)
                break; 
        }
        if(r && has_wrong_sign)
            return mid;
    }
    return -1;
}

auto transpose(const vector<string>& lines)
{
    size_t n = lines[0].size();
    vector<string> ret(n, string('0', lines.size()));
    for(int i = 0; i < lines.size(); ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            ret[j][i] = lines[i][j];
        }
    }
    return ret;
}




int main(int argc, char** argv)
{
    ifstream f(argv[1], ios::in);
    string s;
    vector<string> lines;
    int sum = 0;
    auto get = [](const auto& lines)
    {
        int m = analyze_h(lines);
        if(m == -1)
        {
            auto t = transpose(lines);
            m = analyze_h(t);
            return m;
        }
        return m * 100;
    };
    while(getline(f,s))
    {
        if(s.empty())
        {
            sum += get(lines);
            lines.clear();
        }
        else
            lines.emplace_back(move(s));
    }
    sum += get(lines);
    cout << sum << endl;
    return 0;
}