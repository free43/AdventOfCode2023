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


void cycle_north(vector<string>& lines)
{
    for (int i = 0; i < lines.size(); i++)
    {
        for(int j = 0; j < lines[i].size(); ++j)
        {
            if(lines[i][j] == 'O')
            {
                for(int l = i - 1; l >= 0; --l)
                {
                    if(lines[l][j] == 'O' || lines[l][j] == '#')
                    {
                        lines[l + 1][j] = 'O'; 
                        if((l + 1) != i)
                        {
                            lines[i][j] = '.';
                        }
                        break;
                    }
                    else if(l == 0)
                    {
                        lines[0][j] = 'O';
                        if(i != 0)
                            lines[i][j] = '.';
                    }
                }   
            }
        }
    }
    
}

void cycle_south(vector<string>& lines)
{
    for (int i = lines.size() - 1; i >= 0; i--)
    {
        for(int j = 0; j < lines[i].size(); ++j)
        {
            if(lines[i][j] == 'O')
            {
                for(int l = i + 1; l < lines.size(); ++l)
                {
                    if(lines[l][j] == 'O' || lines[l][j] == '#')
                    {
                        lines[l - 1][j] = 'O'; 
                        if((l - 1) != i)
                        {
                            lines[i][j] = '.';
                        }
                        break;
                    }
                    else if(l == lines.size() - 1)
                    {
                        lines.back()[j] = 'O';
                        if(i != lines.size() - 1)
                            lines[i][j] = '.';
                    }
                }   
            }
        }
    }
    
}
void cycle_west(vector<string>& lines)
{
    for (int i = 0; i < lines.size(); i++)
    {
        for(int j = 0; j < lines[i].size(); ++j)
        {
            if(lines[i][j] == 'O')
            {
                for(int c = j - 1; c >= 0; --c)
                {
                    if(lines[i][c] == 'O' || lines[i][c] == '#')
                    {
                        lines[i][c + 1] = 'O'; 
                        if((c + 1) != j)
                        {
                            lines[i][j] = '.';
                        }
                        break;
                    }
                    else if(c == 0)
                    {
                        lines[i][0] = 'O';
                        if(0 != j)
                            lines[i][j] = '.';
                    }
                }   
            }
        }
    }
    
}
void cycle_east(vector<string>& lines)
{
    for (int i = 0; i < lines.size(); i++)
    {
        for(int j = lines[i].size() - 1; j >= 0; --j)
        {
            if(lines[i][j] == 'O')
            {
                for(int c = j + 1; c < lines[i].size(); ++c)
                {
                    if(lines[i][c] == 'O' || lines[i][c] == '#')
                    {
                        lines[i][c - 1] = 'O'; 
                        if((c - 1) != j)
                        {
                            lines[i][j] = '.';
                        }
                        break;
                    }
                    else if(c == lines[i].size() - 1)
                    {
                        lines[i].back() = 'O';
                        if(j != lines[i].size() - 1)
                            lines[i][j] = '.';
                    }
                }   
            }
        }
    }
}



int main(int argc, char** argv)
{
    ifstream f(argv[1], ios::in);
    vector<int> cnts;
    vector<string> lines;
    string s;
    vector<vector<int>> hashes(1U);
    while(getline(f,s))
    {
        hashes.back().emplace_back(hash<string>{}(s));
        lines.emplace_back(move(s));
    }
    size_t n = 0;
    const size_t N = 1'000'000'000U;
    auto one_cycle = [](auto& lines)
    {
        cycle_north(lines);
        cycle_west(lines);
        cycle_south(lines);
        cycle_east(lines);
    };
    for(int i = 0; i < N; ++i)
    {
        hashes.emplace_back();
        one_cycle(lines);
        for(const auto& l : lines)
        {
            hashes.back().emplace_back(hash<string>{}(l));
        }
        auto it = find_if(begin(hashes), prev(end(hashes)), [&hashes](const auto& v){
            return v == hashes.back();
        });
        if(it != prev(end(hashes)))
        {
            //for_each(begin(lines), end(lines), [](const auto& s){
            //    cout << s << endl;
            //});
            size_t offset = distance(begin(hashes), it);
            size_t freq = distance(it, prev(end(hashes)));
            n = (N - offset) % freq;
            break;
        }

    }
    for(int i = 0; i < n; ++i)
    {
        one_cycle(lines);
    }
    int sum = 0;
    for(int i = 0; i < lines.size(); ++i)
    {
        sum += count(begin(lines[i]), end(lines[i]), 'O') * (lines.size() - i);
    }
    cout << sum << endl;
}