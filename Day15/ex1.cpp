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


int get_hash(string_view s)
{
    int ret = 0;
    for (auto c : s)
    {
        ret += c;
        ret *= 17;
        ret %= 256;
    }
    return ret;
    
}





int main(int argc, char** argv)
{
    ifstream f(argv[1], ios::in);
    string s;
    int sum = 0; 
    while(getline(f,s))
    {
        auto it = begin(s);
        while(it != end(s))
        {
            auto nxt = find_if(it, end(s), [](char c){
                return c == '=' || c == '-';
            });
            string_view ss{it, nxt};
            sum += get_hash(ss);
            if(nxt == end(s))
                break;
            it = next(nxt);
        }
    }
    cout << sum << endl;
    
    return 0;
}