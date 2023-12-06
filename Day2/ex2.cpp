#include <fstream>
#include <unordered_map>
#include <iostream>
int main()
{
    using namespace std;
    ifstream f("input.txt", ios::in);
    string s;
    unordered_map<char, int> m;
    m['r'] = 1;
    m['g'] = 1;
    m['b'] = 1;
    int sum = 0;
    while(getline(f, s))
    {
        auto p = s.find(':');
        bool is_possible = true;
        for(int i = p; i < s.size(); ++i)
        {
            if(isdigit(s[i]))
            {
                int c = 0;
                while(isdigit(s[i]))
                {
                    c = c * 10 + (s[i] - '0');
                    i++;
                }
                //space
                i++;
                m[s[i]] = max(m[s[i]], c);
                if(s[i] == 'r')
                    i += 2;
                else if(s[i] == 'g')
                    i += 4;
                else if(s[i] == 'b')
                    i += 3;

            }
        }
        sum += m['r'] * m['g'] * m['b'];
        m['r'] = m['g'] = m['b'] = 1;

    }
    cout << sum << endl;
}