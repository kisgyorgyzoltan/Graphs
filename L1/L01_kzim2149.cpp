// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>

using namespace std;
struct szomszed
{
    int csucs;
    int suly;
};
struct szlista
{
    int dbszomszed;
    szomszed* szomszedok;
};
void beolvas(int **&bemenet,int &n ,int &m)
{
    ifstream f;
    f.open("graf.in");
    f >> n;
    f >> m;
    bemenet = new int* [m + 1];
    for (int i = 1; i <= m; i++)
    {
        bemenet[i] = new int [4];
    }


    for (int i = 1; i <= m; i++)
    {
        f >> bemenet[i][1] >> bemenet[i][2] >> bemenet[i][3];
    }
    f.close();
}
void kiir_matrix(int** matrix, int v1, int v2)
{
    for (int i = 1; i <= v1; i++)
    {
        for (int j = 1; j <= v2; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void kiir_szlista(szlista* lista, int n)
{
    for (int i = 1; i <= n; i++)
    {
        cout << i << "-nek " << lista[i].dbszomszed << " db szomszedja van : ";
        for (int j = 1; j <= lista[i].dbszomszed; j++)
        {
            cout << lista[i].szomszedok[j].csucs << " (suly:"<< lista[i].szomszedok[j].suly<<")  ";
        }
        cout << endl;
    }
    cout << endl;
}
void kiir_ellista(int** ellista, int m)
{
    for (int i = 1; i <= m; i++)
    {
        cout << ellista[i][1] << " " << ellista[i][2] << " " << ellista[i][3] << endl;
    }
    cout << endl;
}
void adj_epit(int **&adjmatrix, int n, int** bemenet, int m)
{
    adjmatrix = new int* [n + 1];
    for (int i = 1; i <= n; i++)
    {
        adjmatrix[i] = new int[n + 1]{ 0 };
    }


    for (int i = 1; i <= m; i++)
    {
        adjmatrix[bemenet[i][1]][bemenet[i][2]] = bemenet[i][3];
        adjmatrix[bemenet[i][2]][bemenet[i][1]] = bemenet[i][3];
    }
}
void adj_inc(int** adjmatrix,int n,int m,int** &incmatrix)
{
    incmatrix = new int* [n + 1];
    for (int i = 1; i <= n; i++)
    {
        incmatrix[i] = new int[m + 1];
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            incmatrix[i][j] = 0;
        }
    }

    int k = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i+1; j <= n; j++)
        {
            if (adjmatrix[i][j])
            {
                incmatrix[i][k] = adjmatrix[i][j];
                incmatrix[j][k] = adjmatrix[i][j];
                k++;
            }
        }
    }
}
int szamolszomszed(int** incmatrix, int n, int m,int sor)
{
    int db = 0;
    for (int i = 1; i <= m; i++)
    {
        if (incmatrix[sor][i])
        {
            db++;
        }
    }
    return db;
}
void feltoltszomszed(int** incmatrix, int n, int m, szlista*& lista)
{
    int s = 1;
    // elso ket for ==> vegigmegy az incidenciamatrixon
    // harmadik for az oszlopon megy vegig keresve az i-edik csucs parjat
    // n^3 :(
    for (int i = 1; i <= n; i++)
    {
        s = 1;
        for (int j = 1; j <= m; j++)
        {
            if (incmatrix[i][j])
            {
                for (int k = 1; k <= n; k++)
                {
                    if(incmatrix[k][j]!=0  &&  k!=i) 
                    {
                        lista[i].szomszedok[s].csucs = k;
                        lista[i].szomszedok[s].suly = incmatrix[k][j];
                        s++;
                    }
                }
            }
        }
    }
}
void inc_szl(int **incmatrix, int n, int m,szlista *&lista)
{
    lista = new szlista[n + 1];
    for (int i = 1; i <= n; i++)
    {
        lista[i].dbszomszed = szamolszomszed(incmatrix, n, m, i);
        lista[i].szomszedok = new szomszed[lista[i].dbszomszed + 1]{0};
    }
    feltoltszomszed(incmatrix, n, m, lista);
}
void szl_l(szlista* lista, int n, int m, int**& ellista)
{
    ellista = new int* [m + 1];
    int s = 1;
    for (int i = 1; i <= m; i++)
    {
        ellista[i] = new int[4];
    }
    for (int i = 1; i <= n; i++) //vegig szlista csucsain
    {
        for (int j = 1; j <= lista[i].dbszomszed; j++)
        {
            if (i <= lista[i].szomszedok[j].csucs && s<=m)
            {
                ellista[s][1] = i;
                ellista[s][2] = lista[i].szomszedok[j].csucs;
                ellista[s][3] = lista[i].szomszedok[j].suly;
                s++;
            }
        }
    }
}
void izolalt(int** adjmatrix, int n)
{
    int* csucsok = new int[n + 1], dbcs = 0;
    bool iz;
    for (int i = 1; i <= n; i++)
    {
        iz = true;
        for (int j = 1; j <= n; j++)
        {
            if (adjmatrix[i][j])    iz = false;
        }
        if (iz)
        {
            dbcs++;
            csucsok[dbcs] = i;
        }
    }
    if (!dbcs)
    {
        cout << "Nincsenek izolalt csucsok" << endl;
    }
    else
    {
        if (dbcs > 1)  cout << "Az izolalt csucsok: ";
        else        cout << "Az izolalt csucs: ";
        for (int i = 1; i <= dbcs; i++)
        {
            cout << csucsok[i] << " ";
        }
        cout << endl;
    }
}
void vegpontok(int** incmatrix, int n, int m)
{
    int *vp=new int[n+1],dbsz,s=0;
    for (int i = 1; i <= n; i++)
    {
        dbsz = szamolszomszed(incmatrix, n, m, i);
        if (dbsz == 1)
        {
            s++;
            vp[s] = i;
        }
    }
    if (!s) cout << "Nincsenek vegpontok" << endl;
    else
    {
        if (s == 1) cout << "A vegpont: ";
        else        cout << "A vegpontok: ";
        for (int i = 1; i <= s; i++)
        {
            cout << vp[i] << " ";
        }
        cout << endl;
    }
}
int adjszomszed(int** adjmatrix, int n, int sor)
{
    int db = 0;
    for (int j = 1; j <= n; j++)
    {
        if (adjmatrix[sor][j])
        {
            db++;
        }
    }
    return db;
}
void regularis(int** adjmatrix, int n)
{
    bool jo = true;
    int regi = adjszomszed(adjmatrix, n, 1),uj;
    for (int i = 2; i <= n; i++)
    {
        uj = adjszomszed(adjmatrix, n, i);
        if (regi != uj)
        {
            jo = false;
            i = n + 1;
        }
        else
        {
            regi = uj;
        }
    }
    if (jo)
    {
        cout << "A graf regularis\n";
    }
    else
    {
        cout << "A graf nem regularis\n";
    }
}
int main()
{
    int **bemenet,**adjmatrix, **incmatrix,**ellista, n, m;
    szlista* lista;
    beolvas(bemenet, n, m);
    //kiir_ellista(bemenet, m);
    
    // 1.
    adj_epit(adjmatrix, n, bemenet, m);
    //kiir_matrix(adjmatrix, n, n);

    // 2.
    adj_inc(adjmatrix, n, m, incmatrix);
    //kiir_matrix(incmatrix, n, m);

    inc_szl(incmatrix, n, m, lista);
    //kiir_szlista(lista, n);

    szl_l(lista, n, m, ellista);
    //kiir_ellista(ellista, n);

    // 3.
    izolalt(adjmatrix, n);

    // 4.
    vegpontok(incmatrix, n, m);

    // 5.
    regularis(adjmatrix, n);
    return 0;
}
