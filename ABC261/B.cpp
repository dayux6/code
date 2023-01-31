#include <bits/stdc++.h>

int main()
{
    int n;
    std::cin >> n;
    std::string *s = new std::string[n];
    for (int i = 0; i < n; ++i)
        std::cin >> s[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if ((s[i][j] == 'W' && s[j][i] != 'L') || (s[i][j] == 'L' && s[j][i] != 'W') || (s[i][j] == 'D' && s[j][i] != 'D'))
            {
                std::cout << "incorrect" << std::endl;
                return 0;
            }
    std::cout << "correct" << std::endl;
    return 0;
}