#include "stdafx.h"
#include "baza.h"

void Pole::dodanie_sasiada(Pole *x)
{
	Sasiad *n = new Sasiad;
	n->wskazywany = x;

	if ((g_s == NULL) && (o_s == NULL))
	{
		g_s = n;
		o_s = n;
	}

	else
	{
		o_s->nastepny = n;
		o_s = n;
		n->nastepny = NULL;
	}
}

void Pole::okreslenie_pola()
{
	std::cin >> wysokosc;
}

Pole::Pole(bool t, bool kal, int w, Pole *s, Sasiad *gs, Sasiad *ts, bool odw, int poz)
{
	obok_trawy = t;
	wysokosc = w;
	kaluza = kal;
	poziom = poz;

	odwiedzony = odw;
	g_s = gs;
	o_s = ts;
}

Pole::~Pole()
{
}

void Plac::dodanie_sasiada2(Pole *x)
{
	Sasiad *n = new Sasiad;
	n->wskazywany = x;

	if ((g_k == NULL) && (o_k == NULL))
	{
		g_k = n;
		o_k = n;
	}

	else
	{
		o_k->nastepny = n;
		o_k = n;
		n->nastepny = NULL;
	}
}

void Plac::wprowadzanie()
{
	Pole *x1, *x2, *x3, *x4;
	std::cin >> szerokosc >> wysokosc;

	if ((szerokosc > 1) && (wysokosc > 1))
	{
		Pole **x = new Pole *[szerokosc];

		for (int i = 0; i < szerokosc; ++i)
		{
			x[i] = new Pole[wysokosc];
			for (int j = 0; j < wysokosc; ++j)
			{
				if ((i != 0) && (i != szerokosc - 1) && (j != 0) && (j != wysokosc - 1)) x[i][j].obok_trawy = 0;
				else
				{
					x[i][j].obok_trawy = 1;
					x[i][j].kaluza = 0;
				}
			}
		}

		for (int j = 0; j < wysokosc; ++j)
		{
			for (int i = 0; i < szerokosc; ++i)
			{

				x[i][j].okreslenie_pola();

				x1 = &x[i - 1][j];
				x2 = &x[i + 1][j];
				x3 = &x[i][j - 1];
				x4 = &x[i][j + 1];


				if (i > 0)				x[i][j].dodanie_sasiada(x1);	//x[i][j].sasiad[0] = &x[i - 1][j];
				if (i<szerokosc - 1)	x[i][j].dodanie_sasiada(x2);	//x[i][j].sasiad[1] = &x[i + 1][j];
				if (j>0)				x[i][j].dodanie_sasiada(x3);	//x[i][j].sasiad[2] = &x[i][j - 1];
				if (j < wysokosc - 1)	x[i][j].dodanie_sasiada(x4);	//x[i][j].sasiad[3] = &x[1][j + 1];
			}
		}
		tablica_pol = x;
	}
}

void Plac::otwarcie_wszystkich()
{
	for (int i = 0; i < wysokosc; i++)
	{
		for (int j = 0; j < szerokosc; j++)
		{
			tablica_pol[i][j].odwiedzony = 0;
		}
	}
}

bool Plac::sprawdzenie_dostepu(Pole *x)
{
	if (x->obok_trawy == 1) return 0;

	int poz1 = 1000000001;

	Kolejka *k = new Kolejka;
	Kolejka *do_otwarcia = new Kolejka;
	k->push(x);
	x->odwiedzony = 1;
	do_otwarcia->push(x);

	Pole *s;
	Sasiad *p1;

	while (!k->empty())
	{
		s = k->front();
		k->pop();
		p1 = s->g_s;
		do_otwarcia->push(s);

		while (1)
		{
			if ((p1->wskazywany->obok_trawy == 1) && (p1->wskazywany->wysokosc <= x->wysokosc) || (x->obok_trawy == 1) || ((p1->wskazywany->kaluza == 0) && (p1->wskazywany->wysokosc <= x->wysokosc)))
			{
				do_otwarcia->otwieranie_kolejki();
				return 0;
			}
			if (p1->nastepny != NULL)
			{

				if ((p1->wskazywany->odwiedzony == 1) || (p1->wskazywany->wysokosc > x->wysokosc))
				{
					if ((p1->wskazywany->wysokosc < poz1) && (p1->wskazywany->wysokosc>x->wysokosc)) poz1 = p1->wskazywany->wysokosc;
					p1 = p1->nastepny;
					continue;
				}
				else
				{
					k->push(p1->wskazywany);
					p1->wskazywany->odwiedzony = 1;
					do_otwarcia->push(p1->wskazywany);
					p1 = p1->nastepny;
				}
			}
			else
			{
				if ((p1->wskazywany->odwiedzony == 1) || (p1->wskazywany->wysokosc > x->wysokosc))
				{
					if ((p1->wskazywany->wysokosc < poz1) && (p1->wskazywany->wysokosc>x->wysokosc)) poz1 = p1->wskazywany->wysokosc;
					break;
				}
				else
				{
					k->push(p1->wskazywany);
					p1->wskazywany->odwiedzony = 1;
					do_otwarcia->push(p1->wskazywany);
					break;
				}
			}

		}
	}

	if (poz1 == 0) x->poziom = 1;
	else x->poziom = poz1;
	do_otwarcia->otwieranie_kolejki();
	delete k;
	delete do_otwarcia;
	dodanie_sasiada2(x);
	return 1;
}

void Plac::usrednienie(Pole *x)
{
	int poz1 = 0;

	Kolejka *k = new Kolejka;
	Kolejka *do_otwarcia = new Kolejka;
	k->push(x);
	x->odwiedzony = 1;
	do_otwarcia->push(x);

	Pole *s;
	Sasiad *p1;

	while (!k->empty())
	{
		s = k->front();
		k->pop();
		p1 = s->g_s;
		do_otwarcia->push(s);

		while (1)
		{
			if (p1->wskazywany->poziom > x->poziom) x->poziom = p1->wskazywany->poziom;
			if (p1->nastepny != NULL)
			{

				if ((p1->wskazywany->odwiedzony == 1) || (p1->wskazywany->kaluza == 0))
				{
					p1 = p1->nastepny;
					do_otwarcia->push(p1->wskazywany);
					continue;
				}
				else
				{
					k->push(p1->wskazywany);
					p1->wskazywany->odwiedzony = 1;
					do_otwarcia->push(p1->wskazywany);
					if (x->poziom > p1->wskazywany->poziom) p1->wskazywany->poziom = x->poziom;
					p1 = p1->nastepny;
				}
			}
			else
			{
				if ((p1->wskazywany->odwiedzony == 1) || (p1->wskazywany->kaluza == 0))
				{
					do_otwarcia->push(p1->wskazywany);
					break;
				}
				else
				{
					k->push(p1->wskazywany);
					do_otwarcia->push(p1->wskazywany);
					p1->wskazywany->odwiedzony = 1;
					if (x->poziom > p1->wskazywany->poziom) p1->wskazywany->poziom = x->poziom;
					break;
				}
			}
		}
	}

	do_otwarcia->otwieranie_kolejki();
	delete do_otwarcia;
	delete k;
}

void Plac::ustalenie_poziomu()
{
	if (g_k != NULL)
	{
		Sasiad *pomocniczy;
		pomocniczy = g_k;

		while (pomocniczy != o_k)
		{
			usrednienie(pomocniczy->wskazywany);
			pomocniczy = pomocniczy->nastepny;
		}

		usrednienie(pomocniczy->wskazywany);
	}
}


void Plac::przejrzenie()
{
	Pole *x;
	for (int j = 0; j < szerokosc; j++)
	{
		for (int i = 0; i < wysokosc; i++)
		{
			x = &tablica_pol[i][j];
			tablica_pol[i][j].kaluza = sprawdzenie_dostepu(x);
		}
	}
}

void Plac::wyswietlenie_kaluz()
{
	for (int j = 0; j < wysokosc; j++)
	{
		std::cout << "\n";
		for (int i = 0; i < szerokosc; i++)
		{
			if (tablica_pol[i][j].kaluza == 1) std::cout << "#";
			else std::cout << ".";
		}
	}
}

int Plac::suma_obj()
{
	if (g_k != NULL)
	{
		int suma = 0;

		Sasiad *pomocniczy;
		pomocniczy = g_k;

		while (pomocniczy != o_k)
		{
			suma += (pomocniczy->wskazywany->poziom - pomocniczy->wskazywany->wysokosc);
			pomocniczy = pomocniczy->nastepny;
		}
		suma += (pomocniczy->wskazywany->poziom - pomocniczy->wskazywany->wysokosc);

		return suma;
	}
	else return 0;
}

Plac::Plac(bool t, bool odp, int w, Pole *s, Sasiad *g, Sasiad *o)
	:Pole(t, odp, w, s)
{
	g_k = g;
	o_k = o;
	wprowadzanie();
	if (szerokosc > 1)
	{
		przejrzenie();
		ustalenie_poziomu();
		std::cout << suma_obj() << "\n";
		wyswietlenie_kaluz();
	}
	else
	{
		std::cout << "0" << "\n";
		std::cout << ".";
	}
}

Plac::~Plac()
{}

PozKolejki::PozKolejki()
{
	wskazywane = NULL;
	nastepna = NULL;
}

PozKolejki::~PozKolejki()
{}

void Kolejka::push(Pole *x)
{

	PozKolejki *p = new PozKolejki;
	p->wskazywane = x;

	if (!empty())
	{
		tail->nastepna = p;
		tail = p;
		tail->nastepna = NULL;
	}
	else
	{
		head = p;
		tail = p;
	}
}

bool Kolejka::empty()
{
	if ((head == NULL) && (tail == NULL)) return 1;
	else return 0;
}

void Kolejka::pop()
{
	PozKolejki *pom;

	if (!empty())
	{
		if (head != tail)
		{
			pom = head;
			head = head->nastepna;
			delete pom;
		}
		else
		{
			delete head;
			head = NULL;
			tail = NULL;
		}
	}
}

Pole *Kolejka::front()
{
	return head->wskazywane;
}

void Kolejka::zerowanie_kolejki()
{
	while (!empty())
	{
		pop();
	}
}

void Kolejka::otwieranie_kolejki()
{
	while (!empty())
	{
		front()->odwiedzony = 0;
		pop();
	}
}

Kolejka::Kolejka(PozKolejki* h, PozKolejki* t)
{
	head = h;
	tail = t;
}

Kolejka::~Kolejka()
{}
