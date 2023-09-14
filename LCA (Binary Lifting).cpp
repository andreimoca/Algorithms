/// Moca Andrei - 100p - https://www.infoarena.ro/problema/lca

#include <bits/stdc++.h>
using namespace std;

string const& task("lca");
ifstream fin(task + ".in");
ofstream fout(task + ".out");

const int NMAX(1e5 + 5), LMAX(17);
int n, q, t[NMAX][LMAX], lvl[NMAX], l2[NMAX], p2[LMAX];
vector<int> g[NMAX];

inline void DFS(int const& x = 1)
{
    for (int i = 1; i < LMAX; ++i)
    {
        t[x][i] = t[t[x][i - 1]][i - 1];
        if (!t[x][i]) break;
    }
    for (int const& y : g[x])
        if (y != t[x][0])
        {
            t[y][0] = x;
            lvl[y] = lvl[x] + 1;
            DFS(y);
        }
}

inline int LCA(int const& a, int const& b)
{
    int x = a, y = b;
    if (lvl[x] < lvl[y])
        swap(x, y);

    for (int i = l2[lvl[x] - lvl[y] + 1]; i >= 0; --i)
        if (lvl[x] - p2[i] >= lvl[y])
            x = t[x][i];

    if (x == y)
        return x;

    for (int i = l2[lvl[x] + 1]; i >= 0; --i)
        if (t[x][i] != t[y][i])
            x = t[x][i], y = t[y][i];
    return t[x][0];
}

int main()
{
    for (int i = 2; i < NMAX; ++i)
        l2[i] = l2[i / 2] + 1;
    p2[0] = 1;
    for (int i = 1; i < LMAX; ++i)
        p2[i] = p2[i - 1] * 2;

    fin >> n >> q;
    for (int i = 2; i <= n; ++i)
    {
        int x;
        fin >> x;
        g[x].emplace_back(i);
    }
    DFS();
    while (q--)
    {
        int x, y;
        fin >> x >> y;
        fout << LCA(x, y) << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}
