#define _CRT_SECURE_NO_WARNINGS
#include "Gracz.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

// pobiera wspolrzedne ruchu od uzytkownika poprzez konsole,pelny mechanizm poprawnosci wprowadzanych danych
 
Ruch GraczCzlowiek::wykonajRuch(int licznikRuchow) {
    int w, k;
    while (true) {
        cout << nick << " (" << kolor << "), podaj ruch (Wiersz[1-19] Kolumna[1-19]) lub -1 aby zapisac i wyjsc: ";
        cin >> w;

        // obsluga zapisu i wyjscia z gry
        if (w == -1) {
            Ruch r; r.wiersz = -1; r.kolumna = -1;
            return r;
        }
        cin >> k;
    //sprawdzenie
        if (cin.fail()) {
            cin.clear(); // czyszczenie flagi bledu strumienia
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Oproznienie bufora wejsciowego
            cout << "Blad Podaj poprawne liczby\n";
            continue;
        }

        Ruch r;
        r.wiersz = w - 1;
        r.kolumna = k - 1;
        return r;
    }
}

// generuje pseudolosowy ruch bota na planszy

Ruch GraczAI::wykonajRuch(int licznikRuchow) {
    Ruch r;
    r.wiersz = rand() % 19;
    r.kolumna = rand() % 19;
    return r;
}
