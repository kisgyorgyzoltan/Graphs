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
    void tarjanSeged(int csucs,int* belep, int* low, bool* vermen, stack<int>* verem);
public:
    Graf();
    Graf(const char* filenev);
    ~Graf();
    void hozzafuz(int, int);
    void tarjan();
};

Graf::Graf()
{
    n = 1;
    m = 0;
    szlista = new list<int>[1];
}

Graf::~Graf()
{
    szlista->clear();
    delete[]szlista;
}

void Graf::hozzafuz(int u, int v)
{
    szlista[u].push_front(v);
}

Graf::Graf(const char* filenev)
{
    int seged1, seged2;
    ifstream f;
    f.open(filenev);
    f >> n >> m;
    szlista = new list<int>[n];
    for (int i = 0; i < m; i++)
    {
        f >> seged1 >> seged2;
        hozzafuz(seged1, seged2);
    }
    f.close();
}

void Graf::tarjanSeged(int csucs, int* belep, int* low, bool* vermen, stack<int>* verem)
{
    static int time = 0;
    time++;
    belep[csucs] = time;
    low[csucs] = time;
    verem->push(csucs);
    vermen[csucs] = true;

    list<int>::iterator i;
    for (i = szlista[csucs].begin(); i != szlista[csucs].end(); ++i)
    {
        if (belep[*i] == -1)
        {
            tarjanSeged(*i, belep, low, vermen, verem);
            low[csucs] = min(low[csucs], low[*i]);
        }
        else if (vermen[*i])
            low[csucs] = min(low[csucs], belep[*i]);
    }

    int kivett_elem = 0;
    if (low[csucs] == belep[csucs])
    {
        while (verem->top() != csucs)
        {
            kivett_elem = (int)verem->top();
            cout << kivett_elem << " ";
            vermen[kivett_elem] = false;
            verem->pop();
        }
        kivett_elem = (int)verem->top();
        cout << kivett_elem << "\n";
        vermen[kivett_elem] = false;
        verem->pop();
    }
}


void Graf::tarjan()
{
    int* belep = new int[n];
    int* low = new int[n];
    bool* vermen = new bool[n];
    stack<int>* verem = new stack<int>();

    for (int i = 0; i < n; i++)
    {
        belep[i] = -1;
        low[i] = -1;
        vermen[i] = false;
    }

    for (int i = 0; i < n; i++)
    {
        if (belep[i] == -1)
        {
            tarjanSeged(i, belep, low, vermen, verem);
        }
    }   
}

int main()
{
    Graf g("graf.in");
    g.tarjan();
    return 0;
}