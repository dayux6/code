#include <bits/stdc++.h>

int main()
{
    freopen("A.in", "r", stdin);
    std::string s;
    std::cin >> s;
    int indent = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s.at(i) == '{')
        {
            for (int j = 0; j < indent; ++j)
                std::cout << ' ';
            std::cout << "{\n";
            indent += 2;
        }
        else if (s.at(i) == '}')
        {
            indent -= 2;
            for (int j = 0; j < indent; ++j)
                std::cout << ' ';
            std::cout << '}';
            if (i + 1 < s.size() && s.at(i + 1) == ',')
            {
                std::cout << ',';
                ++i;
            }
            std::cout << std::endl;
        }
        else
        {
            for (int j = 0; j < indent; ++j)
                std::cout << ' ';
            while (i < s.size() && isalpha(s.at(i)))
            {
                std::cout << s.at(i);
                ++i;
            }
            if (s.at(i) == ',')
                std::cout << ',';
            else
                --i;
            std::cout << '\n';
        }
    }
    return 0;
}