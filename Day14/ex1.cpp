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

int main(int argc, char** argv)
{
    ifstream f(argv[1], ios::in);
    vector<int> cnts;
    vector<string> lines;
    string s;
    while(getline(f,s))
    {
        lines.emplace_back(move(s));
    }
    int sum = 0;
    vector<int> rocks(lines.front().size(), 0);
    for(int i = lines.size() - 1, k = 1; i >= 0; i--, ++k)
    {
        for(int j = 0; j < lines[i].size(); ++j)
        {
            if(lines[i][j] == 'O')
            {
                rocks[j]++;
            }
            else if(lines[i][j] == '#')
            {
                int l = 1;
                while(rocks[j] > 0)
                {
                    sum += k - l;
                    l++;
                    rocks[j]--;
                }
            }
        }
    }
    for(int j = 0; j < lines[0].size(); ++j)
    {
        int l = 0;
        while(rocks[j] > 0)
        {
            sum += lines.size() - l;
            l++;
            rocks[j]--;
        }
    }
    cout << sum << endl;
}