#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("C.in");
#endif
using std::cout;

int main()
{
    std::string s, t;
    cin >> s >> t;
    std::vector<std::pair<char, int>> vs, vt;
    for (char c : s)
        if (!vs.empty() && c == vs.back().first)
            ++vs.back().second;
        else
            vs.emplace_back(c, 1);
    for (char c : t)
        if (!vt.empty() && c == vt.back().first)
            ++vt.back().second;
        else
            vt.emplace_back(c, 1);
    if (vs.size() == vt.size())
    {
        bool flg = true;
        for (int i = 0; i < vs.size(); ++i)
        {
            if (vs.at(i).first != vt.at(i).first)
                flg = false;
            else if (vs.at(i).second == 1 && vt.at(i).second ^ 1)
                flg = false;
            else if (vs.at(i).second > vt.at(i).second)
                flg = false;
            if (!flg)
                break;
        }
        if (flg)
            std::cout << "Yes" << std::endl;
        else
            std::cout << "No" << std::endl;
    }
    else
        std::cout << "No" << std::endl;
    return 0;
}