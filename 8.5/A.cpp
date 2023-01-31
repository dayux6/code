#include <bits/stdc++.h>

void read(int &x)
{
    x = 0;

    char c = getchar();
    while (!isdigit(c))
        c = getchar();

    while (isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
}

void write(int x)
{
    static int t = 0, s[10];

    do
    {
        s[t] = x % 10;
        ++t;
        x /= 10;
    } while (x);

    while (t > 0)
    {
        --t;
        putchar(s[t] + 48);
    }
}

int main()
{
    freopen("A.in", "r", stdin);
    int n;
    read(n);

    int *p = new int[n];
    p[0] = 0;
    std::fill_n(p + 1, n - 1, -1);

    int a, s = 0;
    for (int i = 1; i <= n; ++i)
    {
        read(a);
        s = (s + a) % n;

        if (~p[s])
        {
            write(i - p[s]);
            putchar('\n');
            for (int j = p[s] + 1; j <= i; ++j)
            {
                write(j);
                putchar(' ');
            }
            putchar('\n');
            break;
        }
        else
            p[s] = i;
    }
    return 0;
}