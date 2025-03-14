
#include <iostream>
#include <fstream>

#define d 12

using namespace std;

class Graf
{
	int** elek;
	int n, m;
	void cs(int hatvany);
	void radix();
	void hozzafuz(int**& feszitofa, int j);
public:
	Graf(const char* filenev);
	void Kruszkal();
};

void Graf::cs(int hatvany)
{
	int db[10];
	for (int i = 0; i < 10; i++)
	{
		db[i] = 0;
	}
	int** seged = new int* [m];
	for (int i = 0; i < m; i++)
	{
		seged[i] = new int[3];
	}
	for (int i = 0; i < m; i++)
	{
		db[(elek[i][2]) % 10]++;
	}
	for (int i = 1; i < 10; i++)
	{
		db[i] += db[i - 1];
	}
	for (int i = m-1; i >= 0; i--)
	{
		seged[db[(elek[i][2]) % 10]][0] = elek[i][0];
		seged[db[(elek[i][2]) % 10]][1] = elek[i][1];
		seged[db[(elek[i][2]) % 10]][2] = elek[i][2];
		db[(elek[i][2]) % 10]--;
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			elek[i][j] = seged[i][j];
		}
	}
	for (int i = 0; i < m; i++)
	{
		delete[]seged[i];
	}
	delete[]seged;
}

void Graf::radix()
{
	int hatvany = 1;
	for (int i = 0; i < d; i++)
	{
		cs(hatvany);
		hatvany *= 10;
	}
}

void Graf::hozzafuz(int**& feszitofa, int j)
{
	int i = 0;
	while (feszitofa[i][0] !=0 && i < n-1)
	{
		i++;
	}
	feszitofa[i][0] = elek[j][0];
	feszitofa[i][1] = elek[j][1];
	feszitofa[i][2] = elek[j][2];
}

Graf::Graf(const char* filenev)
{
	ifstream f;
	f.open(filenev);
	f >> n;
	f >> m;
	elek = new int* [m];
	for (int i = 0; i < m; i++)
	{
		elek[i] = new int[3]{0};
	}
	for (int i = 0; i < m; i++)
	{
		f >> elek[i][0] >> elek[i][1] >> elek[i][2];
	}
	f.close();
}

void Graf::Kruszkal()
{
	int** feszitofa = new int* [n - 1];
	for (int i = 0; i < n-1; i++)
	{
		feszitofa[i] = new int[3];
	}
	radix();
	int* komp = new int[n];
	for (int i = 0; i < n; i++)
	{
		komp[i] = i;
	}
	int i = -1, j = 0,id;
	while ((j < m) && (i < n-2))
	{
		if (komp[elek[j][0]] != komp[elek[j][1]])
		{
			i++;
			id = komp[elek[j][1]];
			hozzafuz(feszitofa, j);
			for (int k = 0; k < n; k++)
			{
				if (komp[k] == id)
				{
					komp[k] = komp[elek[k][0]];
				}
			}
		}
		j++;
	}
	for (int i = 0; i < n - 1; i++)
	{
		cout  << feszitofa[i][0] << " "  << feszitofa[i][1]  << " " << feszitofa[i][2]  << endl;
	}
}

int main()
{
	Graf g("graf.in");
	g.Kruszkal();
    return 0;
}
