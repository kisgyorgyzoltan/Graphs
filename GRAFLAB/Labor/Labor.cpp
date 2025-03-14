// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <vector>
#include <utility>

using namespace std;

class Graf
{
	int n,m;
	double** bemenet;
	double** szmatrix;
	void Ut(int indul,vector<int>p,vector<double>&a);
public:
	Graf(const char* filenev);
	double tav(double x1, double y1, double x2, double y2);
	void epitMatrix();
	void epitIlleszkedes();
	void minimalis();
	void Dijkstra();
};

Graf::Graf(const char* filenev)
{
	m = 0;
	ifstream f;
	f.open(filenev);
	f >> n;
	bemenet = new double* [n];
	szmatrix = new double* [n];
	for (int i = 0; i < n; i++)
	{
		bemenet[i] = new double[3]{ 0 };
		szmatrix[i] = new double[n] {0};
	}
	for (int i = 0; i < n; i++)
		f >> bemenet[i][0] >> bemenet[i][1] >> bemenet[i][2];
	f.close();


}

double Graf::tav(double x1, double y1, double x2, double y2)
{
	return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

void Graf::epitMatrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				szmatrix[ i ][ j ] = tav(bemenet[i][1], bemenet[i][2], bemenet[j][1], bemenet[j][2]);
				m++;
			}
		}
		szmatrix[i][i] = 0;
	}

	cout << "A szomszedsagi matrix:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << szmatrix[i][j] << "\t";

		}
		cout << endl;
	}
	cout << endl;
}

void Graf::epitIlleszkedes()
{
	double** im = new double* [n];
	for (int i = 0; i < n; i++)
	{
		im[i] = new double[m] {0};
	}
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (szmatrix[i][j])
			{
				im[i][k] = szmatrix[i][j];
				im[j][k] = szmatrix[i][j];
				k++;
			}
		}
	}
	cout << "Az illeszkedesi matrix:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << im[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void Graf::minimalis()
{
	bool* volt = new bool[n];
	double** eredmeny;
	eredmeny = new double* [n];
	for (int i = 0; i < n; i++)
	{
		eredmeny[i] = new double[n] {0};
		volt[i] = false;
	}
	volt[0] = true;


	int N = 0, sor, oszlop;
	double minimum, koltseg = 0;
	while (N < n-1)
	{
		minimum = DBL_MAX;
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
		eredmeny[sor][oszlop] = szmatrix[sor][oszlop];
		cout << sor +1 << " " << oszlop +1 << " " << eredmeny[sor][oszlop] << endl;
		koltseg += eredmeny[sor][oszlop];
		volt[oszlop] = true;
		N++;
	}
	cout << "A csatornarendszer koltsege = " << koltseg << "\n\n";
}

void Graf::Dijkstra()
{
	// atalakitas szomszedsagi listara
	list<pair<double, double>>* szlista = new list<pair<double, double>>[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (szmatrix[i][j])
			{
				szlista[i].push_back(make_pair(j, szmatrix[i][j]));
			}
		}
	}
	set<pair<double, double>> szett;
	int indul, hova;
	cout << "Kerem az indulasi pontot : ";
	cin >> indul;
	if (indul < 1 || indul > n)
	{
		cout << "Hibas pont"; exit(1);
	}
	cout << "Kerem az erkezesi pontot : ";
	cin >> hova;
	if (hova < 1 || hova > n)
	{
		cout << "Hibas pont"; exit(1);
	}
	indul--;
	hova--;

	vector<double> tavolsag(n, DBL_MAX);
	vector<int> p(n, -1);

	szett.insert(make_pair(0, indul));
	tavolsag[indul] = 0;

	while (!szett.empty())
	{
		pair<double, double> elso = *(szett.begin());
		int cs1 = elso.second;
		szett.erase(szett.begin());
		list<pair<double, double>>::iterator it;
		for ( it = szlista[cs1].begin(); it != szlista[cs1].end(); ++it)
		{
			int cs2 = (*it).first;
			double suly = (*it).second;
			if (tavolsag[cs2] > tavolsag[cs1] + suly)
			{
				if (tavolsag[cs2] != DBL_MAX)
				{
					szett.erase(szett.find(make_pair(tavolsag[cs2], cs2)));
				}
				tavolsag[cs2] = tavolsag[cs1] + suly;
				p[cs2] = cs1;
				szett.insert(make_pair(tavolsag[cs2], cs2));
			}
			
		}
	}

	cout << indul +1  << "-bol a tavolsag " << hova +1 << "-be = " << tavolsag[hova] << endl;
	vector<double> ut;
	Ut(hova, p, ut);
	cout << "Az ut pedig: ";
	vector<double>::iterator v;
	for ( v = ut.begin(); v != ut.end(); ++v)
	{
		cout << *v +1  << " ";
	}
}

void Graf::Ut(int indul, vector<int> p, vector<double>& a)
{
	if (p[indul] != -1)
	{
		Ut(p[indul], p, a);
	}
	a.push_back(indul);
}

int main()
{
	Graf g("operencia.txt");
	cout << "a)\n";
	g.epitMatrix();

	cout << "b)\n";
	g.epitIlleszkedes();

	cout << "d)\n";
	g.minimalis();

	cout << "e)\n";
	g.Dijkstra();
    return 0;
}