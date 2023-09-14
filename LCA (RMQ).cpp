/// Moca Andrei - 100p - https://www.infoarena.ro/problema/lca

#include <bits/stdc++.h>
using namespace std;

string const& task("f");
ifstream fin(task + ".in");
ofstream fout(task + ".out");

const int NMAX(2e5 + 5), LMAX(19), MOD(1e9 + 7);
vector<int> g[NMAX];
int n, idx, E[2 * NMAX], niv[2 * NMAX], pos[NMAX], p2[LMAX], l2[2 * NMAX], r[LMAX][2 * NMAX];

inline void DFS(int const& x = 1, int const& nv = 1)
{
    ++idx;
    E[idx] = x, niv[idx] = nv, pos[x] = idx;
    for (int const& y : g[x])
    {
        DFS(y, nv + 1);
        ++idx;
        E[idx] = x, niv[idx] = nv;
    }
}

inline void RMQ()
{
    for (int i = 1; i <= idx; ++i)
        r[0][i] = i;
    for (int p = 1; p <= l2[idx]; ++p)
        for (int i = 1; i + p2[p] - 1 <= idx; ++i)
        {
            int r1 = r[p - 1][i];
            int r2 = r[p - 1][i + p2[p - 1]];
            if (niv[r1] < niv[r2])
                r[p][i] = r1;
            else r[p][i] = r2;
        }
}

inline int LCA(int const& a, int const& b)
{
    int x = pos[a], y = pos[b];
    if (x > y)
        swap(x, y);
    int k = l2[y - x];
    int r1 = r[k][x];
    int r2 = r[k][y - p2[k] + 1];
    if (niv[r1] < niv[r2])
        return E[r1];
    return E[r2];
}



int main()
{
    for (int i = 2; i < 2 * NMAX; ++i)
        l2[i] = l2[i / 2] + 1;
    p2[0] = 1;
    for (int i = 1; i < LMAX; ++i)
        p2[i] = p2[i - 1] * 2;

    int q;
    fin >> n >> q;
    for (int i = 2; i <= n; ++i)
    {
        int j;
        fin >> j;
        g[j].emplace_back(i);
    }
    DFS();
    RMQ();
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
