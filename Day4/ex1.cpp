#include <fstream>
#include <unordered_map>
#include <iostream>
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
    
    int sum = 0;
    while(getline(f, s))
    {
        unordered_map<int, bool> m;
        int cnt = 0;
        auto p = s.find(':');
        while(!isdigit(s[p]))
            p++;
        while(s[p] != '|')
        {
            int v = toi(s.data(), &p);
            //cout << v << endl;
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
                cnt = cnt == 0 ? 1 : cnt << 1;
            }
            while(p < s.size())
            {
                if(isdigit(s[p]))
                    break;
                p++;
            }
        }
        sum += cnt;
        

    }
    cout << sum << endl;
}