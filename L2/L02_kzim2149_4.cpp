// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>
#include <list>
#include <stack>

using namespace std;

class Graf
{
    int n;
    int m;
    list<int>* szlista;
    bool* meglatogatva;
    void rendezSeged(int, bool*, stack<int>&);
public:
    Graf(int, int);
    ~Graf();
    void hozzafuz(int, int);
    void rendez();
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

void Graf::rendezSeged(int csucs, bool* meglatogatva, stack<int>& verem)
{
    meglatogatva[csucs] = true;
    list<int>::iterator i;
    for (i = szlista[csucs].begin(); i != szlista[csucs].end(); ++i)
    {
        if (!meglatogatva[*i])
        {
            rendezSeged(*i, meglatogatva, verem);
        }
    }
    verem.push(csucs);
}

void Graf::rendez()
{
    stack<int> verem;

    bool* meglatogatva = new bool[n];
    for (int i = 0; i < n; i++)
    {
        meglatogatva[i] = false;
    }

    for (int i = 0; i < n; i++)
    {
        if (!meglatogatva[i])
        {
            rendezSeged(i, meglatogatva, verem);
        }           
    }
        
    //verem kiirasa
    while ( !verem.empty() )
    {
        cout << verem.top() << " ";
        verem.pop();
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
    /*Graf G;
    beolvas(G);
    G.rendez();*/

    Graf g(6);
    g.hozzafuz(5, 2);
    g.hozzafuz(5, 0);
    g.hozzafuz(4, 0);
    g.hozzafuz(4, 1);
    g.hozzafuz(2, 3);
    g.hozzafuz(3, 1);

    g.rendez();
    return 0;
}