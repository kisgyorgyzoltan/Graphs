// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>

using namespace std;

class Graf
{
    int n;
    int m;
    int** szmatrix;
public:
    Graf();
    Graf(const Graf&);
    Graf(int dbsor, int dbel, int **szomszedsagi_matrix);
    Graf(const char* filenev);
    void Feladat();
    int koltseg();
};

Graf::Graf()
{
    n = 2;
    m = 1;
    szmatrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        szmatrix[i] = new int[n] {0};
    }
    szmatrix[0][1] = 1;
    szmatrix[1][0] = 1;
}

Graf::Graf(int dbsor, int dbel, int** szomszedsagi_matrix)
{
    n = dbsor;
    m = dbel;
    szmatrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        szmatrix[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            szmatrix[i][j] = szomszedsagi_matrix[i][j];
        }
    }
}

Graf::Graf(const char* filenev)
{
    int cs1, cs2, s;
    ifstream f;
    f.open(filenev);
    f >> n >> m;
    szmatrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        szmatrix[i] = new int[n]{0};
    }

    for (int i = 0; i < m; i++)
    {
        f >> cs1 >> cs2 >> s;
        szmatrix[cs1][cs2] = s;
        szmatrix[cs2][cs1] = s;
    }
    f.close();
}

Graf::Graf(const Graf& b)
{
    n = b.n;
    m = b.m;
    szmatrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        szmatrix[i] = new int[n] {0};
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            szmatrix[i][j] = b.szmatrix[i][j];
        }
    }
}

void Graf::Feladat()
{
    int** eredmeny=new int*[n];
    for (int i = 0; i < n; i++)
    {
        eredmeny[i] = new int[n] {0};
    }

    bool* volt = new bool[n];
    for (int i = 0; i < n; i++)
        volt[i] = false;
    volt[0] = true;

    int sor, oszlop,N=0,minimum,koltseg=0;

    while (N<n-1)
    {
        minimum = INT_MAX;        
        sor = 0;
        oszlop = 0;
        for (int i = 0; i < n; i++) 
        {
            if (volt[i]) 
            {
                for (int j = 0; j < n; j++) 
                {
                    if (!volt[j] && szmatrix[i][j]) 
                    {
                        if (minimum > szmatrix[i][j])
                        {
                            minimum = szmatrix[i][j];
                            sor = i;
                            oszlop = j;
                        }
                    }
                }
            }
        }

        cout << sor << " " << oszlop << " : " << szmatrix[sor][oszlop] << endl;
        eredmeny[sor][oszlop] = szmatrix[sor][oszlop];
        koltseg += szmatrix[sor][oszlop];
        volt[oszlop] = true;
        N++;
    }

    // kimentes
    ofstream g;
    g.open("kimenet.out");
    g << koltseg << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (eredmeny[i][j])
            {
                g << j << endl;
            }
        }
    }
    g.close();
}

int main()
{
    Graf g("graf.in");
    g.Feladat();
    
    //cout << g.koltseg();
    return 0;
}