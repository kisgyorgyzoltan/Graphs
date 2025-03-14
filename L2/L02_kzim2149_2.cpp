// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class Graf
{
    int n;
    int m;
    list<int>* szlista;
    bool* meglatogatva;
public:
    Graf(int, int);
    ~Graf();
    void Hozzafuz(int, int);
    void kUt(int, int);
};

Graf::Graf(int csucsok = 1, int elek = 0)
{
    n = csucsok;
    m = elek;
    szlista = new list<int>[csucsok];
    meglatogatva = new bool[csucsok];
    for (int i = 0; i < n; i++)
    {
        meglatogatva[i] = false;
    }
}

Graf::~Graf()
{
    szlista->clear();
    delete[]szlista;
    delete[]meglatogatva;
}

void Graf::Hozzafuz(int u, int v)
{
    szlista[u].push_front(v);
}

void Graf::kUt(int indul, int k)
{
    int* tavok = new int[n] {0}, tav=0;

    for (int i = 0; i < n; i++)
    {
        meglatogatva[i] = false;
    }
    meglatogatva[indul] = true;

    list<int> varakozasi_sor;
    varakozasi_sor.push_back(indul);
    list<int>::iterator i;

    while ( !varakozasi_sor.empty() )
    {
        int jelenlegi_cucs = varakozasi_sor.front();
        //cout << jelenlegi_cucs << " ";
        varakozasi_sor.pop_front();
        for (i = szlista[jelenlegi_cucs].begin(); i != szlista[jelenlegi_cucs].end(); ++i)
        {
            int szomszedos_csucs = *i;

            if (!meglatogatva[szomszedos_csucs])
            {
                tavok[szomszedos_csucs] = tavok[jelenlegi_cucs] + 1;
                meglatogatva[szomszedos_csucs] = true;
                varakozasi_sor.push_back(szomszedos_csucs);
            }
        }
    }

    for (int j = 0; j < n; j++)
    {
        //cout << indul << " tavolsaga " << j << "-tol: " << tavok[j] << endl;
        if (tavok[j] == k)
            cout << j << " ";
    }
    cout << endl;
}

void beolvas(Graf& G,int &v, int &k)
{
    int seged1, seged2, s;
    ifstream f;
    f.open("graf.in");
    f >> seged1 >> s >> v >> k;
    G.Graf::Graf(seged1, s);
    for (int i = 0; i < s; i++)
    {
        f >> seged1 >> seged2;
        G.Hozzafuz(seged1, seged2);
    }
    f.close();
}

int main()
{
    int v, k;
    Graf G;
    beolvas(G,v,k);
    G.kUt(v, k);
    return 0;
}
