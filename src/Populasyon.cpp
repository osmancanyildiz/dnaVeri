/**
* @file         Populasyon.cpp
* @description  Populasyon sınıfının metotlarının bulunduğu dosya.
* @course       2-C
* @assignment   1. Ödev
* @date         27.11.2024
* @author       Osman Can YILDIZ - osman.yildiz4@ogr.sakarya.edu.tr
*/ 

#include "../include/Populasyon.hpp"

Populasyon::Populasyon() : baslangic(nullptr), kromozomSayisi(0) {}

Populasyon::~Populasyon() {
    bellekTemizle();
}

void Populasyon::kromozomEkle(Kromozom* yeniKromozom) {
    KromozomDugumu* yeniDugum = new KromozomDugumu(yeniKromozom);
    if (!baslangic) {
        baslangic = yeniDugum;
    } else {
        KromozomDugumu* mevcut = baslangic;
        while (mevcut->sonraki) {
            mevcut = mevcut->sonraki;
        }
        mevcut->sonraki = yeniDugum;
    }
    kromozomSayisi++;
}

Kromozom* Populasyon::kromozomAl(int indeks) {
    if (indeks < 0 || indeks >= kromozomSayisi) return nullptr;

    KromozomDugumu* mevcut = baslangic;
    for (int i = 0; i < indeks; i++) {
        mevcut = mevcut->sonraki;
    }
    return mevcut->kromozom;
}

void Populasyon::bellekTemizle() {
    KromozomDugumu* mevcut = baslangic;
    while (mevcut) {
        KromozomDugumu* sonraki = mevcut->sonraki;
        delete mevcut->kromozom;
        delete mevcut;
        mevcut = sonraki;
    }
    baslangic = nullptr;
    kromozomSayisi = 0;
}

int Populasyon::getKromozomSayisi() const {
    return kromozomSayisi;
}

// Tüm kromozomların küçük genini ekrana yazdırır
void Populasyon::kromozomlariYazdir() const {
    KromozomDugumu* mevcut = baslangic;
    while (mevcut) {
        cout << mevcut->kromozom->kucukGenBul() << " ";
        mevcut = mevcut->sonraki;
    }
    cout << endl;
}
