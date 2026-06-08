#define _CRT_SECURE_NO_WARNINGS
#include "Gra.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;


struct RekordGracza {
    string nick;
    int wygrane = 0;
};

Gra::~Gra() {
    delete gracz1;
    delete gracz2;
}

void Gra::zmienGracza() {
    if (aktualnyGracz == gracz1) {
        aktualnyGracz = gracz2;
    }
    else {
        aktualnyGracz = gracz1;
    }
}

void Gra::zapiszGre() const {
    ofstream plikWy("pente_save.txt");
    if (!plikWy) {
        cout << "Blad zapisu pliku stanu gry\n";
        return;
    }
    plikWy << trybGry << "\n";
    plikWy << gracz1->pobierzNick() << "\n";
    plikWy << gracz2->pobierzNick() << "\n";
    plikWy << aktualnyGracz->pobierzKolor() << "\n";
    plikWy << licznikRuchow << "\n";
    plikWy << gracz1->pobierzZbitePiony() << "\n";
    plikWy << gracz2->pobierzZbitePiony() << "\n";

    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            plikWy << plansza.pobierzPole(i, j);
        }
        plikWy << "\n";
    }
    cout << "Gra zostala pomyslnie zapisana w pliku 'pente_save.txt'\n";
}

 
bool Gra::wczytajGre() {
    ifstream plikWe("pente_save.txt");
    if (!plikWe) {
        cout << "Brak zapisu\n";
        return false;
    }
    char obecnyKolor;
    int zbicia1, zbicia2;
    string n1, n2;
    int tymczasowyLicznik; 

    plikWe >> trybGry;
    plikWe >> n1;
    plikWe >> n2;
    plikWe >> obecnyKolor;
    plikWe >> tymczasowyLicznik; 
    plikWe >> zbicia1;
    plikWe >> zbicia2;

    ustawGre(trybGry, n1, n2); 

    licznikRuchow = tymczasowyLicznik; 

    gracz1->ustawZbitePiony(zbicia1);
    gracz2->ustawZbitePiony(zbicia2);
    if (gracz1->pobierzKolor() == obecnyKolor) {
        aktualnyGracz = gracz1;
    }
    else {
        aktualnyGracz = gracz2;
    }
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            char znak;
            plikWe >> znak;
            plansza.ustawPole(i, j, znak);
        }
    }
    return true;
}

void Gra::ustawGre(int tryb, string n1, string n2) {
    delete gracz1;
    delete gracz2;
    trybGry = tryb;
    czyTrybPro = (tryb == 2);
    licznikRuchow = 1;

    if (tryb == 1 || tryb == 2) {
        gracz1 = new GraczCzlowiek('C', n1);
        gracz2 = new GraczCzlowiek('B', n2);
    }
    else {
        gracz1 = new GraczCzlowiek('C', n1);
        gracz2 = new GraczAI('B');
    }
    aktualnyGracz = gracz1;
    plansza.wyczysc();
}

void Gra::aktualizujRanking(const string& nickZwyciezcy) {
    if (nickZwyciezcy == "Komputer") return;

    const int MAX_GRACZY = 100;
    RekordGracza ranking[MAX_GRACZY];
    int ileGraczy = 0;

    ifstream plikWe("pente_ranking.txt");
    string nick;
    int wygrane;
    bool znaleziono = false;

    if (plikWe) {
        while (plikWe >> nick >> wygrane && ileGraczy < MAX_GRACZY) {
            if (nick == nickZwyciezcy) {
                wygrane++;
                znaleziono = true;
            }
            ranking[ileGraczy].nick = nick;
            ranking[ileGraczy].wygrane = wygrane;
            ileGraczy++;
        }
        plikWe.close();
    }

    if (!znaleziono && ileGraczy < MAX_GRACZY) {
        ranking[ileGraczy].nick = nickZwyciezcy;
        ranking[ileGraczy].wygrane = 1;
        ileGraczy++;
    }

    for (int i = 0; i < ileGraczy - 1; i++) {
        for (int j = 0; j < ileGraczy - i - 1; j++) {
            if (ranking[j].wygrane < ranking[j + 1].wygrane) {
                RekordGracza temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    ofstream plikWy("pente_ranking.txt");
    for (int i = 0; i < ileGraczy; i++) {
        plikWy << ranking[i].nick << " " << ranking[i].wygrane << "\n";
    }
}

void Gra::wyswietlRanking() {
    ifstream plikWe("pente_ranking.txt");
    cout << "\nRanking graczy (liczba wygranych):\n";
    if (!plikWe) {
        cout << "Ranking jest obecnie pusty\n";
        return;
    }
    string nick;
    int wygrane;
    int pozycja = 1;
    while (plikWe >> nick >> wygrane) {
        cout << pozycja << ". " << nick << " - Wygrane: " << wygrane << "\n";
        pozycja++;
    }
    plikWe.close();
}

 
void Gra::uruchomGre() {
    bool trwaRozgrywka = true;
    while (trwaRozgrywka) {
        plansza.wyswietl();
        cout << "Ruch nr: " << licznikRuchow << " | Zbicia " << gracz1->pobierzNick() << ": " << gracz1->pobierzZbitePiony()
            << " / " << gracz2->pobierzNick() << ": " << gracz2->pobierzZbitePiony() << "\n";

        Ruch ruch = aktualnyGracz->wykonajRuch(licznikRuchow);

        if (ruch.wiersz == -1 && ruch.kolumna == -1) {
            zapiszGre();
            break;
        }

        if (!plansza.czyRuchPoprawny(ruch.wiersz, ruch.kolumna, licznikRuchow, aktualnyGracz->pobierzKolor(), czyTrybPro)) {
            if (dynamic_cast<GraczCzlowiek*>(aktualnyGracz)) {
                cout << "Niedozwolony ruch sprobuj ponownie\n";
            }
            continue;
        }

        plansza.ustawPole(ruch.wiersz, ruch.kolumna, aktualnyGracz->pobierzKolor());

        int zbite = plansza.sprawdzIzbierzPiony(ruch.wiersz, ruch.kolumna, aktualnyGracz->pobierzKolor());
        if (zbite > 0) {
            aktualnyGracz->dodajZbicia(zbite);
            cout << "Zbito " << zbite << " pionki przeciwnika\n";
        }

        if (plansza.czyWygrana(ruch.wiersz, ruch.kolumna, aktualnyGracz->pobierzKolor()) || aktualnyGracz->pobierzZbitePiony() >= 10) {
            plansza.wyswietl();
            cout << "Koniec gry zwycieza: " << aktualnyGracz->pobierzNick() << " (" << aktualnyGracz->pobierzKolor() << ")\n";

            aktualizujRanking(aktualnyGracz->pobierzNick());
            trwaRozgrywka = false;
            break;
        }

        if (plansza.czyPelna()) {
            plansza.wyswietl();
            cout << "Remis cala plansza zostala zapelniona\n";
            trwaRozgrywka = false;
            break;
        }

        zmienGracza();
        licznikRuchow++;
    }
}

void Gra::menuGlowne() {
    int wybor = 0; 
    while (wybor != 6) {
        cout << "\nMENU\n";
        cout << "1 - Nowa gra (Gracz vs Gracz - Standard)\n";
        cout << "2 - Nowa gra (Gracz vs Gracz - PRO)\n";
        cout << "3 - Nowa gra (Gracz vs AI)\n";
        cout << "4 - Wczytaj gre z pliku\n";
        cout << "5 - Pokaz ranking\n";
        cout << "6 - Wyjscie\n";
        cout << "Wybierz opcje: ";
        cin >> wybor;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Niepoprawny wybor\n";
            continue;
        }

        if (wybor >= 1 && wybor <= 3) {
            string nick1, nick2;
            cout << "Podaj nick dla Gracza 1 (C): ";
            cin >> nick1;

            if (wybor == 1 || wybor == 2) {
                cout << "Podaj nick dla Gracza 2 (B): "; 
                cin >> nick2;
                ustawGre(wybor, nick1, nick2);
            }
            else {
                ustawGre(wybor, nick1);
            }
            uruchomGre();
        }
        else if (wybor == 4) {
            if (wczytajGre()) {
                uruchomGre();
            }
        }
        else if (wybor == 5) {
            wyswietlRanking();
        }
    }
}
