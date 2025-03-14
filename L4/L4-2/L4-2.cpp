// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

struct El {
    int u, v, s;
};

class Graf
{
public:
    Graf(const char* filenev);
    void BellmanFord();
private:
    int n, m,indul;
    struct El* elek;
    void kiir(int tavolsag[], int n, bool vannegativkor, vector<int> p);
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

void Graf::kiir(int tavolsag[], int n, bool vannegativkor, vector<int> p)
{
    ofstream g;
    g.open("kimenet.out");
    if (vannegativkor)
    {
        g << "Van negativ kor";
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            vector<int>ut;
            cout << "A legrovidebb ut hossza " << i << "-ba: " << tavolsag[i] << endl;
            g << "A legrovidebb ut hossza " << i << "-ba: " << tavolsag[i] << endl;
            cout << "A legrovidebb ut " << i << "-ba: ";
            g << "A legrovidebb ut " << i << "-ba: ";
            Ut(i, p, ut);
            vector<int>::iterator j;
            for (j = ut.begin(); j != ut.end(); ++j)
            {
                cout << (*j) << " ";
                g << (*j) << " ";
            }
            cout << endl;
            g << endl;
        }
    }
    g.close();
}

void Graf::Ut(int indul, vector<int> P, vector<int>& a)
{
    if (P[indul] != -1)
        Ut(P[indul], P, a);
    a.push_back(indul);
}


void Graf::BellmanFord()
{
    int *tavolsag=new int[n];
    // tavolsag inicializalas
    for (int i = 0; i < n; i++)
    {
        tavolsag[i] = INT_MAX;
    }
    tavolsag[indul] = 0;
    vector<int> p(n, -1);
    
    for (int i = 1; i <= n - 1; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            if (tavolsag[elek[j].u] != INT_MAX && tavolsag[elek[j].u] + elek[j].s < tavolsag[elek[j].v])
            {
                tavolsag[elek[j].v] = tavolsag[elek[j].u] + elek[j].s;
                p[elek[j].v] = elek[j].u;
            }
        }
    }

    // van-e negativ kor
    bool vannegativkor = false;
    for (int i = 0; i < m; i++) {
        if (tavolsag[elek[i].u] != INT_MAX && tavolsag[elek[i].u] + elek[i].s < tavolsag[elek[i].v])
        {
            cout << "Negativ kor!!!";
            vannegativkor = true;
        }
    }
    kiir(tavolsag, n, vannegativkor, p);
}

int main()
{
    Graf G("graf.in");
    G.BellmanFord();
    return 0;
}