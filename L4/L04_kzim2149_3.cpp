// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <utility>

using namespace std;

struct El {
    int u, v, s;
};

class Graf
{
public:
    Graf(const char* filenev);
    void Johnson();
private:
    int n, m, indul;
    struct El* elek;
    int* BellmanFord(int indul, struct El* elek, int dbcsucs, int dbel);
    void Dijkstra(list<pair<int, int>>* szlista, int indul);
    void Ut(int indul, vector<int> P, vector<int>& a);
};

Graf::Graf(const char* filenev)
{
    int cs1, cs2, s;
    ifstream f;
    f.open(filenev);
    f >> n >> m >> indul;
    elek = new El[m];
    for (int i = 0; i < m; i++)
    {
        f >> cs1 >> cs2 >> s;
        elek[i].u = cs1;
        elek[i].v = cs2;
        elek[i].s = s;
    }
}

void Graf::Johnson()
{
    // s = n
    struct El* q_elek=new El[n+m];
    for (int i = 0; i < m; i++)
    {
        q_elek[i] = elek[i];
    }

    for (int i = m; i < n+m; i++)
    {
        q_elek[i].u = n;
        q_elek[i].v = i - m;
        q_elek[i].s = 0;
    }

    int* bellman_tavolsag = BellmanFord(n, q_elek, n + 1, m + n);

    for (int i = 0; i < m; i++)
    {
        elek[i].s += bellman_tavolsag[elek[i].u] - bellman_tavolsag[elek[i].v];
    }

    delete[]bellman_tavolsag;
    delete[]q_elek; // s torolve

    // atalakitas szomszedsagi listara
    list<pair<int, int>>* szlista = new list<pair<int, int>>[n];
    for (int i = 0; i < m; i++)
    {
        szlista[elek[i].u].push_back(make_pair(elek[i].v, elek[i].s));
    }

    for (int i = 0; i < n; i++)
    {
        //cout << i << ":\n";
        Dijkstra(szlista,i);
    }
}


int* Graf::BellmanFord(int indul,struct El* elek,int dbcsucs,int dbel)
{
    int* tavolsag = new int[dbcsucs];
    // tavolsag inicializalas
    for (int i = 0; i < dbcsucs; i++)
    {
        tavolsag[i] = INT_MAX;
    }
    tavolsag[indul] = 0;


    for (int i = 1; i <= dbcsucs - 1; i++)
    {
        for (int j = 0; j < dbel; j++)
        {
            if (tavolsag[elek[j].u] != INT_MAX && tavolsag[elek[j].u] + elek[j].s < tavolsag[elek[j].v])
            {
                tavolsag[elek[j].v] = tavolsag[elek[j].u] + elek[j].s;
            }
        }
    }
    return tavolsag;
}

void Graf::Dijkstra(list<pair<int, int>>* szlista, int indul)
{
    set<pair<int, int>>szett;
    vector<int> tavolsag(n, INT_MAX);
    vector<int> p(n, -1);
    szett.insert(make_pair(0, indul));
    tavolsag[indul] = 0;
    while (!szett.empty())
    {
        pair<int, int> elso = *(szett.begin());
        szett.erase(szett.begin()); // ki is veszem

        int csucs1 = elso.second, csucs2, suly;
        list<pair<int, int>>::iterator i;
        for (i = szlista[csucs1].begin(); i != szlista[csucs1].end(); ++i)
        {
            csucs2 = (*i).first;
            suly = (*i).second;
            // van-e rovidebb ut csucs2-bol csucs1-be
            if (tavolsag[csucs2] > tavolsag[csucs1] + suly)
            {
                if (tavolsag[csucs2] != INT_MAX)
                {
                    szett.erase(szett.find(make_pair(tavolsag[csucs2], csucs2)));
                }
                // uj tavolsag csucs2-be
                tavolsag[csucs2] = tavolsag[csucs1] + suly;
                p[csucs2] = csucs1;
                szett.insert(make_pair(tavolsag[csucs2], csucs2));
            }
        }
    }

    // Eredmeny kiirasa
    ofstream g;
    g.open("kimenet.out");
    for (int i = 0; i < n; i++)
    {
        if (tavolsag[i] != INT_MAX)
        {
            vector<int>ut;
            cout << "A legrovidebb ut hossza " << i << "-ba: " << tavolsag[i] << endl;
            g << "A legrovidebb ut hossza " << i << "-ba: " << tavolsag[i] << endl;
            cout << "A legrovidebb ut " << i << "-ba: ";
            g << "A legrovidebb ut " << i << "-ba: ";
            Ut(i, p,ut);
            vector<int>::iterator j;
            for (j = ut.begin(); j != ut.end(); ++j)
            {
                cout << (*j) << " ";
                g << (*j) << " ";
            }
            cout << endl;
            g << endl;
        }
        else
        {
            cout << "A legrovidebb ut hossza " << i << "-ba: nem elerheto" << endl;
            g << "A legrovidebb ut hossza " << i << "-ba: nem elerheto" << endl;
        }
        cout << endl;
        g<< endl;
    }
    cout << endl;
    g << endl;
    g.close();
}

void Graf::Ut(int indul, vector<int> P,vector<int>& a)
{
    if (P[indul] != -1)
        Ut(P[indul], P,a); 
    //cout << indul << " ";
    a.push_back(indul);
}

int main()
{
    Graf G("graf.in");
    G.Johnson();
    return 0;
}