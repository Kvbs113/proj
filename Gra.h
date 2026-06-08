#ifndef GRA_H
#define GRA_H

#include "Plansza.h"
#include "Gracz.h"
#include <string>

using namespace std;

//Glowna klasa sterujaca cala gra 
class Gra {
private:
    Plansza plansza;           
    Gracz* gracz1;             
    Gracz* gracz2;              
    Gracz* aktualnyGracz;       
    int licznikRuchow;          
    int trybGry;                
    bool czyTrybPro;           
    void zmienGracza();         // zmienia wskaznik na kolejnego gracza
    void zapiszGre() const;     // zapis stanu gry w pliku tekstowym

    //zapisuje punkt zwyciestwa gracza w rankingu
     
    void aktualizujRanking(const string& nickZwyciezcy);

    //Odczytuje i formatuje baze danych rankingu z pliku tekstowego
     
    void wyswietlRanking();

public:
    Gra() : gracz1(nullptr), gracz2(nullptr), aktualnyGracz(nullptr), licznikRuchow(1), trybGry(1), czyTrybPro(false) {}
    ~Gra(); 

    void menuGlowne();          // wyswietla i obsluguje interfejs (menu)

    // konfiguruje obiektu graczy na podstawie wybranego trybu i nickow
    
    void ustawGre(int tryb, string n1 = "Gracz 1", string n2 = "Gracz 2");

    void uruchomGre();          // uruchamia gre w pente
    bool wczytajGre();          // odtwarza przerwany stan gry z pliku tekstowego
};

#endif
