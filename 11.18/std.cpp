#ifndef LOCAL_RUN
#define NDEBUG
#endif
#ifdef GNU_DEBUG
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif
#include <bits/stdc++.h>
#define def(v) auto &v = e[i].v
#define ALL(v) std::begin(v), std::end(v)
#define mset(a, b) memset(&a, b, sizeof(a))
#define go(i, e, u, ...) for (int i = (u), ##__VA_ARGS__; i; i = e[i].nt)
#define fir(i, a, b, ...) for (int i = (a), ##__VA_ARGS__; i <= (b); ++i)
#define firr(i, a, b, ...) for (int i = (a), ##__VA_ARGS__; i >= (b); --i)
#ifdef LOCAL_RUN
template <class T>
void dbgpr(const T &x)
{
    std::cerr << x << std::endl;
}
template <class T, class... Args>
void dbgpr(const T &x, const Args &...args)
{
    std::cerr << x << ", ", dbgpr(args...);
}
template <class... Args>
void dbgprint(const char *s, const Args &...args)
{
    std::cerr << s << " = ", dbgpr(args...);
}
#define debug(...) dbgprint(#__VA_ARGS__, __VA_ARGS__)
#define DEBUG if (true)
#else
#define debug(...) void()
#define DEBUG if (false)
namespace IO
{
    static char ibuf[1 << 21], *p1 = ibuf, *p2 = ibuf, obuf[1 << 21], *p = obuf;
#define getchar()                                                                                  \
    (IO::p1 == IO::p2 &&                                                                           \
             (IO::p2 = (IO::p1 = IO::ibuf) + fread(IO::ibuf, 1, 1 << 21, stdin), IO::p1 == IO::p2) \
         ? EOF                                                                                     \
         : *IO::p1++)
#define putchar(x)                                                                                     \
    (IO::p == IO::obuf + sizeof(IO::obuf) && (fwrite(IO::obuf, 1, 1 << 21, stdout), IO::p = IO::obuf), \
     *IO::p++ = x)
    static struct Flush
    {
        ~Flush() { fwrite(IO::obuf, 1, IO::p - IO::obuf, stdout); }
    } flush;
} // namespace IO
#endif
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
inline int rec()
{
    int ch;
    while (isspace(ch = getchar()))
        ;
    return ch;
}
inline bool rei(char &c)
{
    int ch;
    while (isspace(ch = getchar()))
        ;
    if (ch == EOF)
        return false;
    c = (char)ch;
    return true;
}
inline bool rei(char *s)
{
    if (!rei(*s))
        return false;
    int ch;
    while (ch = getchar(), ch != EOF && !isspace(ch))
        *++s = (char)ch;
    *++s = '\0';
    return true;
}
template <class T>
inline bool rei(T &x)
{
    bool f = true;
    int ch;
    x = 0;
    while (!isdigit(ch = getchar()))
    {
        if (ch == EOF)
            return false;
        f = ch != '-';
    }
    if (f)
        do
            x = x * 10 + (ch & 15);
        while (isdigit(ch = getchar()));
    else
        do
            x = x * 10 - (ch & 15);
        while (isdigit(ch = getchar()));
    return true;
}
inline void pti(char c) { putchar(c); }
inline void pti(const char *s)
{
    while (*s)
        putchar(*s++);
}
template <class T>
inline void pti(T x)
{
    char buf[sizeof(T) * 3], *p = buf + 1;
    if (x >= 0)
        *buf = char(x % 10 | 48), x /= 10;
    else
        putchar('-'), *buf = char(-(x % 10) | 48), x = -(x / 10);
    while (x)
        *p++ = char(x % 10 | 48), x /= 10;
    while (p != buf)
        putchar(*--p);
}
template <class T>
inline void pri(const T &x)
{
    pti(x), putchar(' ');
}
template <class T>
inline void prn(const T &x)
{
    pti(x), putchar('\n');
}
template <class T, class... Args>
inline bool rei(T &&x, Args &&...args)
{
    return rei(std::forward<T>(x)) && rei(std::forward<Args>(args)...);
}
template <class T, class... Args>
inline void pti(const T &x, const Args &...args)
{
    pti(x), pti(args...);
}
template <class T, class... Args>
inline void pri(const T &x, const Args &...args)
{
    pri(x), pri(args...);
}
template <class T, class... Args>
inline void prn(const T &x, const Args &...args)
{
    pri(x), prn(args...);
}
template <class T1, class T2>
inline bool cmax(T1 &a, const T2 &b)
{
    return a < b ? a = b, true : false;
}
template <class T1, class T2>
inline bool cmin(T1 &a, const T2 &b)
{
    return b < a ? a = b, true : false;
}
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 5000 + 5;
int num;
array<int, MAXN> a;
array<array<int, MAXN>, MAXN> dp;
void work(int L)
{
    static array<int, MAXN> len, val, suf;
    int tot = 0;
    assert(!len[0] && !val[0] && !suf[0]);
    firr(i, L - 1, 1)
    {
        ++tot;
        len[tot] = len[tot - 1] + a[i];
        val[tot] = dp[i][L - 1];
    }
    suf[tot] = val[tot];
    firr(i, tot - 1, 1) suf[i] = max(suf[i + 1], val[i]);

    dp[L][L] = suf[1];
    int cur = a[L];
    int pos = 1, has = 0;
    fir(R, L + 1, num)
    {
        while (pos < tot && len[pos] <= cur)
            pos++;
        if (len[pos - 1] == cur)
            has++;
        dp[L][R] = max(dp[L][R - 1], has + suf[pos]);
        cur += a[R];
    }
}
signed main()
{
    freopen("brick.in", "r", stdin);
    freopen("brick.std", "w", stdout);
    rei(num);
    fir(i, 1, num) rei(a[i]);

    dp[0].fill(-INF);
    fir(L, 2, num) { work(L); }

    fir(L, 1, num) fir(R, 1, num)
    {
        pri(dp[L][R]);
        if (R == num)
            pti('\n');
    }

    int ans = 0;
    fir(L, 1, num) cmax(ans, dp[L][num]);
    prn(ans);
}