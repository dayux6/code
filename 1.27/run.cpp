#include <bits/stdc++.h>

int main()
{
    int cnt = 0;

    while (true)
    {
        system("./gen");
        system("./B");
        system("./B-bf");

        if (system("diff lele.out lele.ans"))
        {
            std::cout << "Wrong Answer" << std::endl;
            break;
        }
        else
            std::cout << "Accepted #" << ++cnt << std::endl;
    }
    return 0;
}