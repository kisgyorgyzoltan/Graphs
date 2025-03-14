// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <vector>

#define INF INT_MAX

using namespace std;

class Graf
{
    int n;
    int* tevekenyseg;
    int** szmatrix;
    list<int>* szlista;
    void rendezSeged(int, bool*, stack<int>&);
    vector<int> rendez();
public:
    Graf(const char* filenev);
    void CPM();
};

Graf::Graf(const char* filenev)
{
    ifstream f;
    f.open(filenev);
    f >> n;
    
    szlista = new list<int>[n+1];
    szmatrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        szmatrix[i] = new int[n] {0};
    }
    tevekenyseg = new int[n];
    for (int i = 0; i < n; i++)
    {
        f >> tevekenyseg[i];
    }
    int cs1, cs2;
    while (!f.eof())
    {
        f >> cs1 >> cs2;
        szlista[cs1-1].push_front(cs2-1);
        szmatrix[cs1-1][cs2-1] = 1;
    }
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

vector<int> Graf::rendez()
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


    vector<int> tp;
    //verem kiirasa
    while (!verem.empty())
    {
        tp.push_back(verem.top());
        //cout << verem.top() << " ";
        verem.pop();
    }

    return tp;
}

void Graf::CPM()
{
    int* t0min, * t1min, * t0max, * t1max, u;
    t0min = new int[n] {0};
    t0max = new int[n] {0};
    t1min = new int[n] {0};
    t1max = new int[n] {0};

    for (int i = 0; i < n; i++)
    {
        t0min[i] = 0;
        t1min[i] = 0;
        t0max[i] = INF;
        t1max[i] = INF;
    }

    vector<int> topo = rendez();

    t0min[topo[0]] = 0;
    t1min[topo[0]] = tevekenyseg[topo[0]];

    for (int i = 1; i <= n-1; i++)
    {
        u = topo[i];
        for (int v = 0; v < n; v++)
        {
            if(szmatrix[v][u])
                t0min[u] = max(t0min[u], t1min[v]);
        }
        t1min[u] = t0min[u] + tevekenyseg[u];
    }

    for (int i = 0; i < n; i++)
    {
        t1max[i] = t1min[topo[n - 1]];
        t0max[i] = t1min[topo[n - 1]];
    }

    t1max[topo[n-1]] = t1min[topo[n-1]];
    t0max[topo[n-1]] = t1max[topo[n-1]] - tevekenyseg[topo[n-1]];
    for (int i = n-2; i >= 0; i--)
    {
        u = topo[i];
        for (int w = 0; w < n; w++)
        {
            if(szmatrix[u][w])
                t1max[u] = min(t1max[u], t0max[w]);
        }
        t0max[u] = t1max[u] - tevekenyseg[u];
    }
    ofstream g;
    g.open("3_ki.txt");
    for (int i = 0; i < n; i++)
    {
        if (t0min[i] == t0max[i] && t1min[i] == t1max[i])
        {
            cout << i+1 << " ";
            g << i+1 << " ";
        }
    }

    cout << endl;
    g << endl;

    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << " " << tevekenyseg[i] << " " << t0min[i] << " " << t1min[i] << " " << t0max[i] << " " << t1max[i] << endl;
        g << i + 1 << " " << tevekenyseg[i] << " " << t0min[i] << " " << t1min[i] << " " << t0max[i] << " " << t1max[i] << endl;
    }
    g.close();
}

int main()
{
    Graf G("3_be.txt");
    G.CPM();
    return 0;
}