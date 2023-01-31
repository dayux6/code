#include <bits/stdc++.h>

int main()
{
    while (true)
    {
        system("./B-gen");
        system("./B-bf > B.ans");
        system("./B");

        if (system("diff xor.out B.ans"))
            break;
    }
    return 0;
}