#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>
int main()
{
    std::ifstream f("input.txt", std::ios::in);
    std::string s;
    unsigned int sum = 0;
    while((f>>s))
    {
        auto f = std::find_if(begin(s), end(s), [](auto c){
            return (bool)std::isdigit(c);
        });
        auto e = std::find_if(s.rbegin(), s.rend(), [](auto c){
            return (bool)std::isdigit(c);
        });
        unsigned int val = ((unsigned int)(*f - '0'))*10 + (unsigned int)(*e - '0');
        sum += val;
    }
    std::cout << sum << std::endl;
}