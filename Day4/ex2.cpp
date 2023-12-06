#include <fstream>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <numeric>
int toi(const char* s, size_t* p)
{
    int c = 0;
    while(isdigit(s[*p]))
    {
        c = c * 10 + s[*p] - '0';
        (*p)++;
    }
    return c;
}
int main()
{
    using namespace std;
    ifstream f("input.txt", ios::in);
    string s;
    int numb_of_lines = count(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>(), '\n');
    f.seekg(ios::beg);
    int indx = 0;
    vector<int> vec(numb_of_lines, 1);
    while(getline(f, s))
    {
        unordered_map<int, bool> m;
        cout << s << endl;
        int cnt = 0;
        auto p = s.find(':');
        while(!isdigit(s[p]))
            p++;
        while(s[p] != '|')
        {
            int v = toi(s.data(), &p);
            m[v]; 
            while(!isdigit(s[p]))
            {
                if(s[p] == '|')
                    break;
                p++;
            }
        }
        while(!isdigit(s[p]))
            p++;
        //cout << s << endl;
        while(p < s.size())
        {
            int v = toi(s.data(), &p);
            if(m.contains(v))
            {
                cnt++;
            }
            while(p < s.size())
            {
                if(isdigit(s[p]))
                    break;
                p++;
            }
        }
        for(int i = indx + 1; i < vec.size() && i <= indx + cnt; ++i)
        {
            vec[i] += vec[indx];
        }
        indx++;
    }
    int sum = accumulate(begin(vec), end(vec), 0);
    cout << sum << endl;
}