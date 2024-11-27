/**
* @file         kromozom.cpp
* @description  kromozom sınıfının metotlarının bulunduğu dosya.
* @course       2-C
* @assignment   1. Ödev
* @date         27.11.2024
* @author       Osman Can YILDIZ - osman.yildiz4@ogr.sakarya.edu.tr
*/ 
#include "../include/Kromozom.hpp"

// Kurucu: Başlangıç durumunda baslangic düğümünü nullptr olarak başlatıyoruz
Kromozom::Kromozom() : baslangic(nullptr), genSayisi(0) {}

// Yıkıcı: Bağlı listedeki tüm düğümleri serbest bırakır
Kromozom::~Kromozom() {
    Dugum* mevcut = baslangic;
    while (mevcut != nullptr) {
        Dugum* sonraki = mevcut->sonraki; // Bir sonraki düğüme geçişi sağla
        delete mevcut; // Mevcut düğümü serbest bırak
        mevcut = sonraki; // Sonraki düğüme ilerle
    }
}

// Gen Ekleme: Bağlı listenin sonuna yeni bir gen düğümü ekler
void Kromozom::genEkle(char gen) {
    Dugum* yeniDugum = new Dugum(gen);
    if (baslangic == nullptr) {
        baslangic = yeniDugum;
    } else {
        Dugum* gecici = baslangic;
        while (gecici->sonraki != nullptr) {
            gecici = gecici->sonraki;
        }
        gecici->sonraki = yeniDugum;
        yeniDugum->onceki = gecici;
    }
    genSayisi++;
}

pair<Kromozom*, Kromozom*> Kromozom::caprazla(Kromozom* diger) {
    int bolmeNoktasi1 = genSayisi / 2;
    int bolmeNoktasi2 = diger->genSayisi / 2;

    Kromozom* yeniKromozom1 = new Kromozom();
    Kromozom* yeniKromozom2 = new Kromozom();

    // Yeni Kromozom 1: ilk kromozomun sol yarısı + ikinci kromozomun sağ yarısı
    Dugum* mevcut1 = baslangic;
    for (int i = 0; i < bolmeNoktasi1; i++) {
        yeniKromozom1->genEkle(mevcut1->gen);
        mevcut1 = mevcut1->sonraki;
    }

    Dugum* mevcut2 = diger->baslangic;
    for (int i = 0; i < bolmeNoktasi2; i++) {
        mevcut2 = mevcut2->sonraki;
    }

    // Eğer ikinci kromozomun gen sayısı tekse, ortadaki geni atla
    if (diger->genSayisi % 2 != 0 && mevcut2 != nullptr) {
        mevcut2 = mevcut2->sonraki;
    }

    while (mevcut2) {
        yeniKromozom1->genEkle(mevcut2->gen);
        mevcut2 = mevcut2->sonraki;
    }

    // Yeni Kromozom 2: ilk kromozomun sağ yarısı + ikinci kromozomun sol yarısı
    mevcut1 = baslangic;
    for (int i = 0; i < bolmeNoktasi1; i++) {
        mevcut1 = mevcut1->sonraki;
    }

    // Eğer ilk kromozomun gen sayısı tekse, ortadaki geni atla
    if (genSayisi % 2 != 0 && mevcut1 != nullptr) {
        mevcut1 = mevcut1->sonraki;
    }

    while (mevcut1) {
        yeniKromozom2->genEkle(mevcut1->gen);
        mevcut1 = mevcut1->sonraki;
    }

    // İkinci kromozomun sol yarısını ekle
    mevcut2 = diger->baslangic;
    for (int i = 0; i < bolmeNoktasi2; i++) {
        yeniKromozom2->genEkle(mevcut2->gen);
        mevcut2 = mevcut2->sonraki;
    }

    return {yeniKromozom1, yeniKromozom2};
}


// Mutasyon: Belirtilen indisteki geni "X" ile değiştirir
void Kromozom::mutasyonYap(int genIndeksi) {
    Dugum* mevcut = baslangic;
    for (int i = 0; i < genIndeksi && mevcut != nullptr; i++) {
        mevcut = mevcut->sonraki;
    }
    if (mevcut != nullptr) {
        mevcut->gen = 'X';
    }
}

// Yazdır: Kromozomun genlerini sırayla yazdırır
void Kromozom::yazdir() const {
    Dugum* mevcut = baslangic;
    while (mevcut != nullptr) {
        cout << mevcut->gen << " ";
        mevcut = mevcut->sonraki;
    }
    cout << endl;
}

// Gen Sayısını Al: Kromozomun gen sayısını döndürür
int Kromozom::genSayisiniAl() const {
    return genSayisi;
}

// Küçük Gen Bul: Sağdan sola giderek ilk küçük geni bulur
char Kromozom::kucukGenBul() const {
    // Kromozom boşsa
    if (baslangic == nullptr) {
        cout << "Kromozom boş!" << endl;
        return '\0';
    }

    // İlk gen değerini al
    Dugum* mevcut = baslangic;
    char ilkGen = mevcut->gen;
    char kucukGen = ilkGen;  // Başlangıçta küçük gen ilk gen olarak kabul edilir.

    // Kromozomun sonuna git
    while (mevcut->sonraki != nullptr) {
        mevcut = mevcut->sonraki;
    }

    // Sağdan sola git, küçük gen bul
    while (mevcut != nullptr) {
        if (mevcut->gen < ilkGen) {  // Eğer sağdaki gen, ilk genden küçükse
            kucukGen = mevcut->gen;  // Küçük gen olarak ayarla
            break;  // Küçük gen bulundu, işlemi sonlandır
        }
        mevcut = mevcut->onceki;  // Bağlı listeyi tersten gez
    }

    // Küçük gen bulunduysa yazdır, yoksa ilk gen yazdırılacak
    return kucukGen;
}

