/**
* @file         Populasyon.hpp
* @description  populasyon sınıfının başlık dosyası.
* @course       2-C
* @assignment   1. Ödev
* @date         27.11.2024
* @author       Osman Can YILDIZ - osman.yildiz4@ogr.sakarya.edu.tr
*/ 
#ifndef POPULASYON_HPP
#define POPULASYON_HPP

#include "Kromozom.hpp"
#include <iostream>
using namespace std;

class Populasyon {
private:
    struct KromozomDugumu {
        Kromozom* kromozom;
        KromozomDugumu* sonraki;
        KromozomDugumu(Kromozom* k) : kromozom(k), sonraki(nullptr) {}
    };

    KromozomDugumu* baslangic;
    int kromozomSayisi;

public:
    Populasyon();
    ~Populasyon();

    void kromozomEkle(Kromozom* yeniKromozom);
    Kromozom* kromozomAl(int indeks);
    void bellekTemizle();
    int getKromozomSayisi() const;

    // Kromozomların küçük genlerini ekrana yazdırır
    void kromozomlariYazdir() const;
};

#endif
