#include <fstream>
#include <unordered_map>
#include <iostream>
int main()
{
    using namespace std;
    ifstream f("input.txt", ios::in);
    string s;
    unordered_map<char, int> m;
    m['r'] = 0;
    m['g'] = 0;
    m['b'] = 0;
    unordered_map<char, int> sm;
    sm['r'] = 12;
    sm['g'] = 13;
    sm['b'] = 14;
    int indx = 1;
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
                //cout << c << endl;
                //space
                i++;
                m[s[i]] += c;
                if(m[s[i]] > sm[s[i]])
                {
                    is_possible = false;
                    break;
                }
                if(s[i] == 'r')
                    i += 2;
                else if(s[i] == 'g')
                    i += 4;
                else if(s[i] == 'b')
                    i += 3;

            }
            else if(s[i] == ';')
            {
                m['r'] = m['g'] = m['b'] = 0;
            }
        }
        if(is_possible)
        {
            //cout << indx << endl;
            sum += indx;
        }
        indx++;
        m['r'] = m['g'] = m['b'] = 0;

    }
    cout << sum << endl;
}