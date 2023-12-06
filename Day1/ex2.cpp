#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>

int main()
{
    using namespace std;
    std::ifstream f("input.txt", std::ios::in);
    std::string s;
    unsigned int sum = 0;
    std::array<std::string_view, 9> digits({
        std::string_view("one"),
        std::string_view("two"),
        std::string_view("three"),
        std::string_view("four"),
        std::string_view("five"),
        std::string_view("six"),
        std::string_view("seven"),
        std::string_view("eight"),
        std::string_view("nine")
    });
    while((f>>s))
    {
        auto add = [&](int i){
            if(isdigit(s[i]))
            {
                return ((unsigned int)(s[i] - '0'));
            }
            else
            {
                for(unsigned int k = 0; k < digits.size(); ++k)
                {
                    if(i + digits[k].size() > s.size())
                        continue;
                    string_view ns(s.data() + i, digits[k].size());
                    if(ns == digits[k])
                    {
                        return (k + 1);
                    }

                }
            }
            return 0U;
        };
        for(int i = 0; i < s.size(); ++i)
        {
            auto val = add(i);
            sum += 10 * val;
            if(val != 0U)
                break;
        }
        for(int i = s.size() - 1; i >= 0; --i)
        {
            auto val = add(i);
            sum += val;
            if(val != 0U)
                break;
        }
    }
    std::cout << sum << std::endl;
}