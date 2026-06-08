#ifndef GRACZ_H
#define GRACZ_H

#include <string>

using namespace std;

// struktura ze wspolrzednymi ruchu na planszy

struct Ruch {
    int wiersz;   
    int kolumna;
};

// klasa bazowa reprezentujaca abstrakcyjnego gracza
 
class Gracz {
protected:
    char kolor;         // znak pionka: 'C' -czarny , 'B' - biały
    string nick;        // nazwa gracza
    int zbitePiony;     // liczba zbitych pionkow przez gracza

public:
   
    Gracz(char k, string n) : kolor(k), nick(n), zbitePiony(0) {}

    virtual ~Gracz() {}
    //gettery
    char pobierzKolor() const { 
        return kolor; 
    }
    string pobierzNick() const {
        return nick; 
    }
    int pobierzZbitePiony() const {
        return zbitePiony; 
    }

  //zwieksza licznik zbitych pionków gracza
    
    void dodajZbicia(int ilosc) { 
        zbitePiony += ilosc; 
    }

    //setter
    int ustawZbitePiony(int ilosc) {
        if (ilosc >= 0) return zbitePiony = ilosc;
        else return zbitePiony;
    }

  
    virtual Ruch wykonajRuch(int licznikRuchow) = 0;
};

// klasa pochodna reprezentujaca gracza

class GraczCzlowiek : public Gracz {
public:
    GraczCzlowiek(char k, string n) : Gracz(k, n) {
    }

    Ruch wykonajRuch(int licznikRuchow) override;
};

//klasa pochodna reprezentujaca gracza AI
 
class GraczAI : public Gracz {
public:
    GraczAI(char k) : Gracz(k, "Komputer") {
        //bot ma nick Komputer
    }

    Ruch wykonajRuch(int licznikRuchow) override;
};

#endif
