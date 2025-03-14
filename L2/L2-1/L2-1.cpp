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
    void melysegi_bejaras(int);
    void szelessegi_bejaras(int);
};

Graf::Graf(int csucsok=1, int elek=0)
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

void Graf::melysegi_bejaras(int indul)
{
    meglatogatva[indul] = true;
    list<int> jelenlegi_szlista = szlista[indul];
    cout << indul << " ";
    list<int>::iterator i;
    for (i = jelenlegi_szlista.begin(); i != jelenlegi_szlista.end(); ++i)
    {
        if (!meglatogatva[*i])
        {
            melysegi_bejaras(*i);
        }
    }
}

void Graf::szelessegi_bejaras(int indul)
{
    for (int i = 0; i < n; i++)
    {
        meglatogatva[i] = false;
    }
    meglatogatva[indul] = true;

    list<int> varakozasi_sor;
    varakozasi_sor.push_back(indul);
    list<int>::iterator i;

    while (!varakozasi_sor.empty())
    {
        int jelenlegi_cucs = varakozasi_sor.front();
        cout << jelenlegi_cucs << " ";
        varakozasi_sor.pop_front();

        for (i = szlista[jelenlegi_cucs].begin(); i != szlista[jelenlegi_cucs].end() ; ++i)
        {
            int szomszedos_csucs = *i;

            if (!meglatogatva[szomszedos_csucs])
            {
                meglatogatva[szomszedos_csucs] = true;
                varakozasi_sor.push_back(szomszedos_csucs);
            }
        }
    }
}

void beolvas(Graf& G)
{
    int seged1, seged2,k;
    ifstream f;
    f.open("graf.in");
    f >> seged1 >> k;
    G.Graf::Graf(seged1, k);
    for (int i = 0; i < k; i++)
    {
        f >> seged1 >> seged2;
        G.Hozzafuz(seged1, seged2);
    }
    f.close();
}

int main()
{
    Graf G;
    beolvas(G);
    cout << "Melysegi bejaras: ";
    G.melysegi_bejaras(0);
    cout << endl;
    cout << "Szelessegi bejaras: ";
    G.szelessegi_bejaras(0);
    cout << endl;
	return 0;
}
