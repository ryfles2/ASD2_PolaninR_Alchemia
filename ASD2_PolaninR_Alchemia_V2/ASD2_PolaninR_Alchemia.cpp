#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define niesk 1000000000
//IMPLEMENTACJA ALGORYTMU DIKSTRY ZE STRONY 'http://kondel.dx.am/?pid=51'

using namespace std;


long *D, *N, np;
long najmniejszy();
void Dijkstra(long);
long m, n;
struct metale
{
	long numer;
	long cena;
	long bajtary=0;
};
struct S_kraw
{
	long gdzie;
	long waga;
};
struct S_wierz
{
	long ile_kraw;
	struct S_kraw *kraw;
	void dodaj_kraw(long, long);
	void zwolnij_pamiec();
};
struct S_wierz *wierz;
void S_wierz::dodaj_kraw(long dest, long length)
{
	this->ile_kraw++;
	this->kraw = (struct S_kraw *) realloc(this->kraw, ((sizeof(struct S_kraw))*(this->ile_kraw)));
	this->kraw[this->ile_kraw - 1].gdzie = dest;
	this->kraw[this->ile_kraw - 1].waga = length;
}
void S_wierz::zwolnij_pamiec()
{
	free(this->kraw);
	this->kraw = NULL;
}

int main()
{
	long long lPrzyp = 0;
	cin >> lPrzyp;
	metale *Metale;

	for (long long i = 0; i < lPrzyp; i++)
	{
		bool flaga = true;
		cin >> n;
		
		Metale = new metale[n];

		wierz = new struct S_wierz[n];
		for (long i = 0; i<n; i++)
		{
			wierz[i].ile_kraw = 0;
			wierz[i].kraw = NULL;
		}
		for (long j = 0; j < n; j++)
		{
			Metale[j].numer = j + 1;
			cin >> Metale[j].cena;
			Metale[j].bajtary = Metale[j].cena/2;
		}
		cin >> m;
		long a, b, c;
		for (long i = 0; i<m; i++)
		{
			cin >> a;
			cin >> b;
			cin >> c;
			wierz[(a - 1)].dodaj_kraw((b - 1), c);
		};
		for (long x = 0; x < n; x++)
		{
			Dijkstra(x);
			if (flaga)
			{
				for (long y = 0; y < n; y++)
				{
					Metale[y].bajtary += D[y];
				}
				flaga = false;
			}
			for (long y = 0; y < 1; y++)
			{
				Metale[x].bajtary += D[0];
			}
		}
		/*for ( long j = 0; j < n; j++)
		{
			cout << Metale[j].numer << " ";
			cout << Metale[j].bajtary << endl;
		}*/
		long min = Metale[0].bajtary;
		for (long i = 1; i < n; i++)
		{
			if (Metale[i].bajtary < min)	min = Metale[i].bajtary;
		}
		cout << min << endl;

		delete[] D, N, Metale;
	}
	return 0;
}

void Dijkstra(long s)
{
	np = 0; //ilosc wierzcholkow niepewnych
	D = new long[n];
	N = new long[n];

	for (long i = 0; i<n; i++) D[i] = niesk;
	for (long i = 0; i<wierz[s].ile_kraw; i++) D[wierz[s].kraw[i].gdzie] = wierz[s].kraw[i].waga;
	D[s] = 0;
	for (long i = 0; i<n; i++)
	{
		if (i == s) continue;
		N[np++] = i;
	};

	while (np>0)
	{
		long i = najmniejszy();
		for (long k = 0; k<wierz[i].ile_kraw; k++)
			if (D[wierz[i].kraw[k].gdzie] > D[i] + wierz[i].kraw[k].waga)
				D[wierz[i].kraw[k].gdzie] = D[i] + wierz[i].kraw[k].waga;

	}
}

long najmniejszy()
{
	long val, num, result;
	val = niesk;
	for (long i = 0; i<np; i++)
	{
		if (D[N[i]] < val)
		{
			val = D[N[i]];
			num = i;
		}
	}
	result = N[num];
	np--;
	N[num] = N[np];
	return result;
}