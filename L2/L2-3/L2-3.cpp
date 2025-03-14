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
    bool ciklusSeged(int, bool*);
public:
    Graf(int, int);
    ~Graf();
    void hozzafuz(int, int);
    void vanCiklus();
};

Graf::Graf(int csucsok = 1, int elek = 0)
{
    n = csucsok;
    m = elek;
    szlista = new list<int>[csucsok];
    meglatogatva = new bool[n];
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

void Graf::hozzafuz(int u, int v)
{
    szlista[u].push_front(v);
}
bool Graf::ciklusSeged(int csucs, bool* rekurziv_verem)
{
    if (!meglatogatva[csucs])
    {
        meglatogatva[csucs] = true;
        rekurziv_verem[csucs] = true;

        list<int>::iterator i;
        for (i = szlista[csucs].begin(); i != szlista[csucs].end(); ++i)
        {
            if (!meglatogatva[*i] && ciklusSeged(*i, rekurziv_verem))
                return true;
            else if(rekurziv_verem[*i])
            {
                return true;
            }
        }
    }
    rekurziv_verem[csucs] = false;
    return false;
}
void Graf::vanCiklus()
{
    bool* rekurziv_verem;
    meglatogatva = new bool[n];
    rekurziv_verem = new bool[n];
    for (int i = 0; i < n; i++)
    {
        meglatogatva[i] = false;
        rekurziv_verem[i] = false;
    }

    bool van = false;
    for (int i = 0; i < n; i++)
    {
        if (!meglatogatva[i] && ciklusSeged(i, rekurziv_verem))
        {
            van = true;
        }
    }
    
    if (van)
    {
        cout << "Igen";
    }
    else
    {
        cout << "Nem";
    }
}


void beolvas(Graf& G)
{
    int seged1, seged2, k;
    ifstream f;
    f.open("graf.in");
    f >> seged1 >> k;
    G.Graf::Graf(seged1, k);
    for (int i = 0; i < k; i++)
    {
        f >> seged1 >> seged2;
        G.hozzafuz(seged1, seged2);
    }
    f.close();
}

int main()
{
    Graf G;
    beolvas(G);
    G.vanCiklus();
    return 0;
}