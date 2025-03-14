// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>
#include <vector>

#define INF INT_MAX

using namespace std;

class Graf
{
public:
	Graf(const char* filenev);
    void RFW();
private:
    int** szmatrix;
    int n, m,indul,erkezik;
};

Graf::Graf(const char* filenev)
{
    int cs1, cs2, s;
    ifstream f;
    f.open(filenev);
    f >> n >> m >> indul >> erkezik;
    szmatrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        szmatrix[i] = new int[n] {0};
    }

    for (int i = 0; i < m; i++)
    {
        f >> cs1 >> cs2 >> s;
        szmatrix[cs1][cs2] = s;
    }
    f.close();
}

void Graf::RFW()
{

    int** D = new int* [n];
    int** kovetkezo = new int* [n];
    for (int i = 0; i < n; i++)
    {
        D[i] = new int[n] {0};
        kovetkezo[i] = new int[n];
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (szmatrix[i][j] == 0)
            {
                D[i][j] = INF;
                kovetkezo[i][j] = -1;
            }
            else
            {
                D[i][j] = szmatrix[i][j];
                kovetkezo[i][j] = j;
            }     
        }
        D[i][i] = 0;
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (D[i][j] > D[i][k] + D[k][j])
                {
                    if (D[i][k] != INF && D[k][j]!=INF)
                    {
                        D[i][j] = D[i][k] + D[k][j];
                        kovetkezo[i][j] = kovetkezo[i][k];
                    }
                }
            }
        }
    }

    // tavolsagi matrix kiirasa
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (D[i][j] == INF)
            {
                cout << "INF\t";
            }
            else
            {
                cout << D[i][j] << "\t";
            }
        }
        cout << endl;
    }

    // ut meghatarozasa
    bool vanut = false;
    vector<int> ut;
    if (kovetkezo[indul][erkezik] == -1)
    {
        cout << "Nincs ut" << indul << " es " << erkezik << " kozott\n";
    }
    else
    {
        vanut = true;
        ut.push_back(indul);
        while (indul != erkezik)
        {
            cout<<indul<<" ";
            indul = kovetkezo[indul][erkezik];
            ut.push_back(indul);
        }
    }
    // kiiras allomanyba
    ofstream g;
    g.open("kimenet.out");
    vector<int>::iterator i;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (D[i][j] == INF)
            {
                g << "INF\t";
            }
            else
            {
                g << D[i][j] << "\t";
            }
        }
        g << endl;
    }
    if (vanut)
    {
        for (i = ut.begin(); i != ut.end(); ++i)
        {
            g << (*i) << " ";
        }
    }
    else
    {
        g << "Nincs ut" << indul << " es " << erkezik << " kozott";
    }
    g.close();
}


int main()
{
    Graf G("graf.in");
    G.RFW();
    return 0;
}