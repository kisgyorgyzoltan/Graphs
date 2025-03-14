// Kisgyorgy Zoltan, 512

#include <iostream>
#include <fstream>

#define d 11

using namespace std;

void beolvas(int& n, int& m, unsigned int**& matrix, unsigned int**& feszitofa)
{
    unsigned int s1, s2, s3;
    ifstream f;
    f.open("graf.in");
    f >> n;
    f >> m;
    matrix = new unsigned int* [m + 1];
    for (int i = 1; i <= m; i++)
    {
        matrix[i] = new unsigned int[4];
    }
    feszitofa = new unsigned int* [n];
    for (int i = 1; i <= n - 1; i++)
    {
        feszitofa[i] = new unsigned int[4]{0};
    }
    for (int i = 1; i <= m; i++)
    {
        f >> s1 >> s2 >> s3;
        matrix[i][1] = s1;
        matrix[i][2] = s2;
        matrix[i][3] = s3;
    }
    f.close();
}
void cs(int m, unsigned int**& elek, int hatvany)
{
    unsigned int** seged = new unsigned int* [m + 1];
    int db[10];
    for (int i = 1; i <= m; i++)
    {
        seged[i] = new unsigned int[4];
    }
    for (int i = 0; i < 10; i++)
    {
        db[i] = 0;
    }
    for (int i = 1; i <= m; i++)
    {
        db[(elek[i][3] / hatvany) % 10]++;
    }
    for (int i = 1; i < 10; i++)
    {
        db[i] += db[i - 1];
    }
    for (int i = m; i >= 1; i--)
    {
        seged[db[(elek[i][3] / hatvany) % 10]][2] = elek[i][2];
        seged[db[(elek[i][3] / hatvany) % 10]][1] = elek[i][1];
        seged[db[(elek[i][3] / hatvany) % 10]][3] = elek[i][3];
        db[(elek[i][3] / hatvany) % 10]--;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            elek[i][j] = seged[i][j];
        }
    }
    for (int i = 1; i <= m; i++)
    {
        delete[]seged[i];
    }
    delete[]seged;
}
void radixsort(int m, unsigned int**& elek)
{
    int hatvany = 1;
    for (int i = 0; i <= d; i++)
    {
        cs(m, elek, hatvany);
        hatvany *= 10;
    }
}
void kiir(int m, unsigned int** elek)
{
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            cout << elek[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void hozzafuz(unsigned int**& feszitofa, unsigned int** elek, int j, int n)
{
    int i = 1;
    while (feszitofa[i][1] != 0 && i <= n - 1)
    {
        i++;
    }
    feszitofa[i][1] = elek[j][1];
    feszitofa[i][2] = elek[j][2];
    feszitofa[i][3] = elek[j][3];
}


void kruszkal(int m, int n, unsigned int** elek, unsigned int**& feszitofa)
{
    radixsort(m, elek);
    //kiir(m, elek);
    int* komp;
    komp = new int[n + 1];
    for (int i = 1; i <= n; i++)
    {
        komp[i] = i;
    }

    int i = 0, j = 1, id;
    while ((j <= m) && (i < (n - 1)) )
    {
        if (komp[elek[j][1]] != komp[elek[j][2]])
        {
            i++;
            id = komp[elek[j][2]];
            hozzafuz(feszitofa, elek, j, n);
            for (int k = 1; k <= n; k++)
            {
                if (komp[k] == id)
                {
                    komp[k] = komp[elek[j][1]];
                }
            }
        }
        j++;
    }
}

int fa_koltseg(int m, unsigned int **feszitofa)
{
    int s = 0;
    for (int i = 1; i <= m-1; i++)
    {
        s += feszitofa[i][3];
    }
    return s;
}
int main()
{
    int n, m;
    unsigned int** elek, osszeg = 0, ** feszitofa;
    beolvas(n, m, elek,feszitofa);
    kruszkal(m, n, elek, feszitofa);
    int koltseg = fa_koltseg(m,feszitofa);
    cout << koltseg << "\n\n";
    for (int i = 1; i <= n - 1; i++)
    {
        cout /* << feszitofa[i][1] << " " */<< feszitofa[i][2] /* << " " << feszitofa[i][3] */<< endl;
    }
    return 0;
}