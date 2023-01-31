#include <bits/stdc++.h>

int main()
{
    int cnt = 0;

    while (true)
    {
        system("./gen");
        system("./A");
        system("./A-bf");

        if (system("diff tournament.out tournament.ans"))
        {
            std::cout << "Wrong Answer" << std::endl;
            break;
        }
        else
            std::cout << "Accepted #" << ++cnt << std::endl;
    }
    return 0;
}