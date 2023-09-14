/// Moca Andrei - 100p - https://www.infoarena.ro/problema/aib

#include <bits/stdc++.h>
#define EXIT fin.close(); fout.close(); return 0;
using namespace std;

string const task("aib");
ifstream fin(task + ".in");
ofstream fout(task + ".out");

class AIB {
public:
    AIB() {}
    AIB(int const& _n) :
        n(_n), aib(vector<int>(_n + 1)) {}

    inline void Update(int const& pos, int const& val)
    {
        for (int i = pos; i <= n; i += i & -i)
            aib[i] += val;
    }

    inline int Query(int const& l, int const& r) const
    {
        return Query(r) - Query(l - 1);
    }

    inline int Search(int const& val) const
    {
        int st(1), dr(n), mid, curr;
        while (st <= dr) {
            mid = (st + dr) / 2;
            curr = Query(mid);
            if (curr == val)
                return mid;
            if (curr < val)
                st = mid + 1;
            else dr = mid - 1;
        }
        return -1;
    }

private:
    inline int Query(int const& pos) const
    {
        int sum(0);
        for (int i = pos; i >= 1; i -= i & -i)
            sum += aib[i];
        return sum;
    }
    vector<int> aib;
    int n;
};

int n, q, op, a, b;

int main()
{
    fin >> n >> q;
    AIB aib(n);
    for (int i = 1; i <= n; ++i)
    {
        fin >> a;
        aib.Update(i, a);
    }
    while (q--)
    {
        fin >> op >> a;
        if (op == 2)
            fout << aib.Search(a) << '\n';
        else {
            fin >> b;
            if (op == 1)
                fout << aib.Query(a, b) << '\n';
            else aib.Update(a, b);
        }
    }
    EXIT
}
