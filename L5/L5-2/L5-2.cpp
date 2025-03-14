// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>
#include <queue>

#define INF INT_MAX

using namespace std;

class Graf
{
    int n, forras, nyelo;
    int** szmatrix;
    void push(int u, int v,int** c, int** &f, int* &x, queue<int> &tobbletcsucsok);
    void relabel(int u, int*& h, int** f);
    void discharge(int u, int*& x, int*& volt, int**& f, int*& h, queue<int>& tobbletcsucsok);
public:
    Graf(const char* filenev);
    void PumpaloEmelo();
};

Graf::Graf(const char* filenev)
{
    int cs1, cs2, s;
    ifstream f;
    f.open(filenev);
    f >> n >> forras >> nyelo;
    szmatrix = new int* [n+1];
    for (int i = 0; i <= n; i++)
    {
        szmatrix[i] = new int[n+1]{ 0 };
    }
    while (!f.eof())
    {
        f >> cs1 >> cs2 >> s;
        szmatrix[cs1][cs2] = s;
        szmatrix[cs2][cs1] = s;
    }
    f.close();
}

void Graf::push(int u, int v, int** c, int** &f, int* &x, queue<int> &tobbletcsucsok)
{

    int m = min(x[u], c[u][v] - f[u][v]);
    f[u][v] -= m;
    f[v][u] += m;
    x[u] -= m;
    x[v] += m;

    if(m && x[v] == m)
        tobbletcsucsok.push(v);
}

void Graf::relabel(int u, int*& h,int **f)
{
    int m = INF;
    for (int v= 0; v < n; v++)
    {
        if (szmatrix[u][v] - f[u][v] > 0)
        {
            m = min(m, h[v]);
        }
    }
    if(m < INF)
        h[u] = m + 1;
}

void Graf::discharge(int u, int*& x, int*& volt, int**& f, int*& h, queue<int>& tobbletcsucsok)
{
    while (x[u]>0)
    {
        if (volt[u] < n)
        {
            int v = volt[u];
            if (szmatrix[u][v] - f[u][v] > 0 && h[u] > h[v])
            {
                push(u, v, szmatrix, f, x, tobbletcsucsok);
            }
            else
            {
                volt[u]++;
            }
        }
        else
        {
            relabel(u, h, f);
            volt[u] = 0;
        }
    }
}

void Graf::PumpaloEmelo()
{
    queue<int> tobbletcsucsok;
    int* h, * x, ** f, * volt;

    volt = new int[n];
    for (int i = 0; i < n; i++)
    {
        volt[i] = 0;
    }

    x = new int[n]{ 0 };
    x[forras] = INF;

    h = new int[n]{ 0 };
    for (int i = 0; i < n; i++)
    {
        h[i] = 0;
    }
    h[forras] = n;

    f = new int* [n+1];
    for (int i = 0; i <= n; i++)
    {
        f[i] = new int[n+1]{ 0 };
    }


    for (int i = 0; i < n; i++)
    {
        if (i != forras)
        {
            push(forras, i, szmatrix, f, x,tobbletcsucsok);
        }
    }

    while (!tobbletcsucsok.empty())
    {
        int u = tobbletcsucsok.front();
        tobbletcsucsok.pop();
        if (u != forras && u != nyelo)
        {
            discharge(u, x, volt, f, h, tobbletcsucsok);
        }
    }
    int maxfolyam = 0;
    for (int i = 0; i < n; i++)
    {
        maxfolyam += f[i][nyelo];
    }
    cout << "Maximalis folyam " << maxfolyam;
}

int main()
{
    Graf G("2_be.txt");
    G.PumpaloEmelo();
    return 0;
}