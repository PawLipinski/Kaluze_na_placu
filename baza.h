#include "stdafx.h"
#include <iostream>

class Sasiad;

class Pole
{
public:
	bool obok_trawy;
	bool kaluza;
	int wysokosc;
	int odwiedzony;
	int poziom;
	Sasiad *g_s;
	Sasiad *o_s;

	void okreslenie_pola();
	void dodanie_sasiada(Pole *x);
	Pole(bool t = 0, bool kal = 1, int w = 0, Pole *s = NULL, Sasiad *gs = NULL, Sasiad *ts = NULL, bool odw = 0, int poz = 0);
	~Pole();
};

class Sasiad
{
public:
	Pole *wskazywany;
	Sasiad *nastepny;
};

class Plac :public Pole
{
public:
	int szerokosc;
	int wysokosc;
	Pole **tablica_pol;
	Sasiad *g_k;
	Sasiad *o_k;

	void wprowadzanie();
	void otwarcie_wszystkich();
	bool sprawdzenie_dostepu(Pole *x);
	void przejrzenie();
	void wyswietlenie_kaluz();
	void ustalenie_poziomu();
	void usrednienie(Pole *x);
	int suma_obj();
	void dodanie_sasiada2(Pole *x);
	Plac(bool t = 0, bool odp = 0, int w = 0, Pole *s = NULL, Sasiad *g = NULL, Sasiad *o = NULL);
	~Plac();
};

class PozKolejki
{
public:
	Pole *wskazywane;
	PozKolejki *nastepna;

	PozKolejki();
	~PozKolejki();
};

class Kolejka
{
public:
	PozKolejki *head;
	PozKolejki *tail;

	void push(Pole *x);
	void pop();
	bool empty();
	Pole* front();
	void zerowanie_kolejki();
	void otwieranie_kolejki();

	Kolejka(PozKolejki* h = NULL, PozKolejki* t = NULL);
	~Kolejka();
};