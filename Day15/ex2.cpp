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
    array<unordered_map<string, pair<int, int>>, 256> boxes;
    array<int, 256> cnt;
    cnt.fill(0);
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
            int box_indx = get_hash(ss);
            char op = *nxt;
            string sss(ss);
            if(op == '=')
            {
                nxt = next(nxt);
                int strength = (*nxt) - '0';
                if(boxes[box_indx].contains(sss))
                {
                    boxes[box_indx][sss].first = strength;
                }
                else
                {
                    boxes[box_indx][sss] = make_pair(strength, cnt[box_indx]);
                    cnt[box_indx]++;
                }
            }
            else
            {
                if(boxes[box_indx].contains(sss))
                {
                    boxes[box_indx].erase(sss);
                }
            }
            nxt = next(nxt);
            if(nxt == end(s))
                break;
            it = next(nxt);
        }
    }
    int bx_indx = 1;
    for(const auto& b : boxes)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;
        for(const auto & [_, p] : b)
        {
            pq.push(make_pair(p.second, p.first));
        }
        int i = 1;
        while(!pq.empty())
        {
            auto [_, s] = pq.top();
            int tmp = s * i * bx_indx;
            sum += tmp;
            i++;
            pq.pop();
        }
        bx_indx++;
    }
    cout << sum << endl;
    
    return 0;
}