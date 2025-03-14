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
    bool szelessegi_bejaras(int** szmatrix, int* &szulo);
public:
    Graf(const char* filenev);
    void EdmondsKarp();
    void matrixKiir();
};

Graf::Graf(const char* filenev)
{
    int cs1, cs2, s;
    ifstream f;
    f.open(filenev);
    f >> n >> forras >> nyelo;
    szmatrix = new int* [n + 1];
    for (int i = 0; i <= n; i++)
    {
        szmatrix[i] = new int[n + 1]{ 0 };
    }
    while (!f.eof())
    {
        f >> cs1 >> cs2 >> s;
        szmatrix[cs1][cs2] = s;
        szmatrix[cs2][cs1] = s;
    }
    f.close();
}

void Graf::EdmondsKarp()
{
    int* szulo = new int[n+1], maximalis_folyam = 0, u, v;
    int** rezidualis = new int* [n + 1];
    for (int i = 0; i <= n; i++)
    {
        rezidualis[i] = new int[n + 1]{ 0 };
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            rezidualis[i][j] = szmatrix[i][j];
        }
    }

    while (szelessegi_bejaras(rezidualis,szulo))
    {
        int folyam = INF;
        for (v = nyelo; v != forras; v=szulo[v])
        {
            u = szulo[v];
            folyam= min(folyam,rezidualis[u][v]);
        }

        for (v = nyelo; v != forras; v = szulo[v])
        {
            u = szulo[v];
            rezidualis[u][v] -= folyam;
            rezidualis[v][u] += folyam;
        }
        maximalis_folyam += folyam;

    }
    


    bool* meglatogatva = new bool[n + 1];
    for (int i = 0; i <= n; i++)
    {
        meglatogatva[i] = false;
    }
    meglatogatva[forras] = true;

    queue<int> varakozasi_sor;
    varakozasi_sor.push(forras);

    while (!varakozasi_sor.empty())
    {
        int jelenlegi_cucs = varakozasi_sor.front();
        varakozasi_sor.pop();
        for (int szomszedos_csucs = 0; szomszedos_csucs <= n; szomszedos_csucs++)
        {
            if (rezidualis[jelenlegi_cucs][szomszedos_csucs])
            {
                if (!meglatogatva[szomszedos_csucs])
                {
                    meglatogatva[szomszedos_csucs] = true;
                    varakozasi_sor.push(szomszedos_csucs);
                }
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (meglatogatva[i]) cout << i << " ";
    }
    cout << "; ";
    for (int i = 1; i <= n; i++)
    {
        if (!meglatogatva[i]) cout << i << " ";
    }
    cout << endl;
    cout <<"A maximalis folyam = " << maximalis_folyam<<endl;
    ofstream g;
    g.open("1_ki.txt");
    g << maximalis_folyam << endl;
    for (int i = 1; i <= n; i++)
    {
        if (meglatogatva[i]) g << i << " ";
    }
    g << "; ";
    for (int i = 1; i <= n; i++)
    {
        if (!meglatogatva[i]) g << i << " ";
    }
    g.close();
}

void Graf::matrixKiir()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << szmatrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool Graf::szelessegi_bejaras(int** elek, int* &szulo)
{
    bool* meglatogatva = new bool[n+1];
    for (int i = 0; i <= n; i++)
    {
        meglatogatva[i] = false;
    }
    meglatogatva[forras] = true;
    szulo[forras] = -1;

    queue<int> varakozasi_sor;
    varakozasi_sor.push(forras);

    while (!varakozasi_sor.empty())
    {
        int jelenlegi_cucs = varakozasi_sor.front();
        varakozasi_sor.pop();
        for(int szomszedos_csucs=0; szomszedos_csucs<=n; szomszedos_csucs++)
        {
            if (elek[jelenlegi_cucs][szomszedos_csucs])
            {
                if (!meglatogatva[szomszedos_csucs])
                {
                    if (szomszedos_csucs == nyelo)
                    {
                        szulo[szomszedos_csucs] = jelenlegi_cucs;
                        return true;
                    }
                    meglatogatva[szomszedos_csucs] = true;
                    varakozasi_sor.push(szomszedos_csucs);
                    szulo[szomszedos_csucs] = jelenlegi_cucs;
                }
            }
        }
    }
    return false;
}

int main()
{
    Graf G("1_be.txt");
    G.matrixKiir();
    //G.EdmondsKarp();
    return 0;
}