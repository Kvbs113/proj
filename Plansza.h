#ifndef PLANSZA_H
#define PLANSZA_H

// Klasa rysujaca cala plansze oraz odpowiadajaca za logike

class Plansza {
private:
    char pola[19][19]; 

public:
    Plansza();

    // Resetuje wszystkie pola planszy do stanu pustego - znak '.'
   
    void wyczysc();

    //Pobiera zawartosc konkretnego pola z uwzglednieniem granic macierzy
     
    char pobierzPole(int w, int k) const;
    //sprawdza czy pelna
    bool czyPelna() const;
 //setter
    char ustawPole(int w, int k, char wartosc);

    // rysuje aktualny stan planszy w oknie konsoli tekstowej wraz z indeksami
    void wyswietl() const;

    // wweryfikuje poprawnosc ruchu wedlug ogolnych zasad PRO
   
    bool czyRuchPoprawny(int w, int k, int licznikRuchow, char kolorGracza, bool czyTrybPro) const;

    //analizuje 8 kierunkow wokol postawionego pionka i wykonuje zbicie par
  
    int sprawdzIzbierzPiony(int w, int k, char kolorGracza);

    // sprwadza czy zostal ulozony 5 lub wiecej
    bool czyWygrana(int w, int k, char kolorGracza) const;
};

#endif
