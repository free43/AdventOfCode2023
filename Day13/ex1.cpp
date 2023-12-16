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

int analyze_h(const vector<string>& lines)
{
    for(int mid = 1; mid < lines.size(); mid++)
    {
        bool r = true;
        for(int i = mid - 1, j = mid; i >= 0 && j < lines.size(); i--, j++)
        {
            r = r && lines[i] == lines[j];
            if(!r)
                break; 
        }
        if(r)
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