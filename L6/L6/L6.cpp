// Kisgyorgy Zoltan, 512
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

#define MAXHOSSZ 10000

using namespace std;

struct Pont
{
	int cs;
	int x;
	int y;
};

class Graf
{
	int n, m;
	vector<Pont> ut;
	int** bemenet;
	double** szmatrix;
	int ntav(int x1, int y1, int x2, int y2);
	double tav(int x1, int y1, int x2, int y2);
	int nUtHossz();
	double UtHossz();
	void twoOptSeged(int i, int j);
public:
	Graf(const char* filenev);
	void twoOpt();
};

Graf::Graf(const char* filenev)
{
	m = 0;
	ifstream f;
	f.open(filenev);
	bemenet = new int*[MAXHOSSZ];
	for (int i = 0; i < MAXHOSSZ; i++)
	{
		bemenet[i] = new int[3]{ 0 };
	}
	while (f >> bemenet[m][0] >> bemenet[m][1] >> bemenet[m][2])
	{
		m++;
	}
	n = bemenet[m - 1][0];
	f.close();


	szmatrix = new double* [n];
	for (int i = 0; i < n; i++)
	{
		szmatrix[i] = new double[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				szmatrix[i][j] = tav(bemenet[i][1], bemenet[i][2], bemenet[j][1], bemenet[j][2]);
			}
		}
		szmatrix[i][i] = 0;
	}

	Pont tmp;
	for (int i = 0; i < m; i++)
	{
		tmp.cs = bemenet[i][0];
		tmp.x = bemenet[i][1];
		tmp.y = bemenet[i][2];
		ut.push_back(tmp);
	}
}

void Graf::twoOpt()
{
	int njelenlegiHossz = nUtHossz();
	bool javult = true;
	while (javult)
	{
		javult = false;
		for (int i = 0; i < n-1; i++)
		{
			for (int j = i+1; j < n; j++)
			{
				int tavkulonbseg = -ntav(ut[i].x, ut[i].y, ut[(i + 1) % n].x, ut[(i + 1) % n].y) - ntav(ut[j].x, ut[j].y, ut[(j + 1) % n].x, ut[(j + 1) % n].y) + ntav(ut[i].x, ut[i].y, ut[j].x, ut[j].y) + ntav(ut[i + 1 % n].x, ut[i + 1 % n].y, ut[(j + 1) % n].x, ut[(j + 1) % n].y);
				if (tavkulonbseg < 0)
				{
					twoOptSeged(i, j);
					njelenlegiHossz += tavkulonbseg;
					javult = true;
				}
			}
		}
	}
	double jelenlegiHossz =UtHossz();
	
	
	cout << jelenlegiHossz << endl;
	for (int i = 0; i < n; i++)
	{
		cout << ut[i].cs << " ";
	}

	ofstream g;
	g.open("output.txt");
	g << jelenlegiHossz << endl;
	for (int i = 0; i < n; i++)
	{
		g << ut[i].cs << " ";
	}
	g.close();

}

int Graf::ntav(int x1, int y1, int x2, int y2)
{
	return ( (x2 - x1) * (x2 - x1) ) + ( (y2 - y1) * (y2 - y1) );
}

double Graf::tav(int x1, int y1, int x2, int y2)
{
	return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)) );
}

int Graf::nUtHossz()
{
	int h = 0;
	for (int i = 1; i < n; i++)
	{
		h += ntav(ut[i - 1].x, ut[i - 1].y, ut[i].x, ut[i].y);
	}
	return h;
}

double Graf::UtHossz()
{
	double h = 0;
	for (int i = 1; i < n; i++)
	{
		h += tav(ut[i - 1].x, ut[i - 1].y, ut[i].x, ut[i].y);
	}
	return h;
}

void Graf::twoOptSeged(int i, int j)
{
	reverse(begin(ut) + i + 1, begin(ut) + j + 1);
}

int main()
{
	Graf g("tsp3.txt");
	clock_t m;
	m = clock();
	g.twoOpt();
	m = clock() - m;
	double t = m;
	t /= CLOCKS_PER_SEC;
	t *= 1000;
	cout << "\nFutasi ido: " << t << " ms";
	return 0;
}