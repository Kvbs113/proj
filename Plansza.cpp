#include "Plansza.h"
#include <iostream>

using namespace std;

Plansza::Plansza() {
    wyczysc();
}

bool Plansza::czyPelna() const {
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            if (pola[i][j] == '.') {
                return false; 
            }
        }
    }
    return true; 
}

void Plansza::wyczysc() {
    for (int i = 0; i < 19; ++i)
        for (int j = 0; j < 19; ++j)
            pola[i][j] = '.';
}

char Plansza::pobierzPole(int w, int k) const {
    if (w >= 0 && w < 19 && k >= 0 && k < 19) {
        return pola[w][k];
    }
    return ' ';
}

char Plansza::ustawPole(int w, int k, char wartosc) {
    if (w >= 0 && w < 19 && k >= 0 && k < 19) {
        return pola[w][k] = wartosc;
    }
    else {
        return ' ';
    }
}

void Plansza::wyswietl() const {
    cout << "   ";
    for (int i = 1; i <= 19; ++i) cout << (i < 10 ? " " : "") << i << " ";
    cout << "\n";
    for (int i = 0; i < 19; ++i) {
        cout << (i + 1 < 10 ? " " : "") << i + 1 << " ";
        for (int j = 0; j < 19; ++j) {
            cout << " " << pola[i][j] << " ";
        }
        cout << "\n";
    }
}

//Sprawdza poprawnosc ruchow w PRO. Blokuje niedozwolone otwarcia dla gracza czarnego ('C').
bool Plansza::czyRuchPoprawny(int w, int k, int licznikRuchow, char kolorGracza, bool czyTrybPro) const {
    if (w < 0 || w >= 19 || k < 0 || k >= 19) {
        return false;
    }
    if (pola[w][k] != '.') {
        return false;
    }
    if (czyTrybPro) {
        if (licznikRuchow == 1 && kolorGracza == 'C') {
            return (w == 9 && k == 9);
        }
        if (licznikRuchow == 3 && kolorGracza == 'C') {
            if (w >= 7 && w <= 11 && k >= 7 && k <= 11) {
                return false;
            }
        }
    }
    return true;
}

// Przeszukuje w celu eliminacji par przeciwnika
int Plansza::sprawdzIzbierzPiony(int w, int k, char kolorGracza) {

    char przeciwnik = (kolorGracza == 'C') ? 'B' : 'C'; // Ustalenie koloru przeciwnika
    int sumaZbitych = 0;

    // Tablice przesuniec 
    int dw[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dk[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; ++i) {
        int w1 = w + dw[i], k1 = k + dk[i];
        int w2 = w + 2 * dw[i], k2 = k + 2 * dk[i];
        int w3 = w + 3 * dw[i], k3 = k + 3 * dk[i];
        
        if (pobierzPole(w1, k1) == przeciwnik && pobierzPole(w2, k2) == przeciwnik && pobierzPole(w3, k3) == kolorGracza) {
            ustawPole(w1, k1, '.'); // czyszczenie zbitych pionow
            ustawPole(w2, k2, '.');
            sumaZbitych += 2;
        }
    }
    return sumaZbitych;
}

// Algorytm sprawdzajacy ulozenie pieciu linii (pion, poziom, skosy)
bool Plansza::czyWygrana(int w, int k, char kolorGracza) const {
    // tablice do sprawdzenia linii
    int dw[] = { 1, 0, 1, 1 };
    int dk[] = { 0, 1, 1, -1 };

    for (int i = 0; i < 4; ++i) {
        int licznik = 1;

        // Krok w przod wzdluz danej osi
        int nw = w + dw[i], nk = k + dk[i];
        while (pobierzPole(nw, nk) == kolorGracza) {
            licznik++;
            nw += dw[i];
            nk += dk[i];
        }

        // Krok w tyl wzdluz danej osi
        nw = w - dw[i]; nk = k - dk[i];
        while (pobierzPole(nw, nk) == kolorGracza) {
            licznik++;
            nw -= dw[i];
            nk -= dk[i];
        }

        if (licznik >= 5)
        {
            return true;
        }
    }
    return false;
}
