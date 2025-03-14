// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <utility>

using namespace std;

class Graf
{
    int n;
    int m;
    int indul;
    list<pair<int, int>>* szlista;
    void Ut(int indul, vector<int> P, vector<int>& a);
public:
    Graf(const char* filenev);
    void hozzafuz(int csucs1, int csucs2, int suly);
    void Dijkstra();  
};

Graf::Graf(const char* filenev)
{
    int cs1, cs2, s;
    ifstream f;
    f.open(filenev);
    f >> n >> m >> indul;
    szlista = new list<pair<int, int>>[n];
    for (int i = 0; i < m; i++)
    {
        f >> cs1 >> cs2 >> s;
        hozzafuz(cs1, cs2, s);
    }
    f.close();
}

void Graf::hozzafuz(int csucs1, int csucs2, int suly)
{
    szlista[csucs1].push_back(make_pair(csucs2, suly));
}

void Graf::Dijkstra()
{
    set<pair<int,int>>szett;
	
    vector<int> tavolsag(n, INT_MAX);
	
	vector<int> p(n, -1);
	
    szett.insert(make_pair(0, indul));
	
    tavolsag[indul] = 0; 
	
    while (!szett.empty())
    {
        pair<int, int> elso = *(szett.begin());
        szett.erase(szett.begin()); // ki is veszem

        int csucs1 = elso.second,csucs2,suly;
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

void Graf::Ut(int indul, vector<int> P, vector<int>& a)
{
    if (P[indul] != -1)
        Ut(P[indul], P, a);
    //cout << indul << " ";
    a.push_back(indul);
}

int main()
{
    Graf G("graf.in");
    G.Dijkstra();
    return 0;
}