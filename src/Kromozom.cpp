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
    }
    genSayisi++;
}

pair<Kromozom*, Kromozom*> Kromozom::caprazla(Kromozom* diger) {
    int bolmeNoktasi1 = (genSayisi % 2 == 0) ? genSayisi / 2 : (genSayisi - 1) / 2;
    int bolmeNoktasi2 = (diger->genSayisi % 2 == 0) ? diger->genSayisi / 2 : (diger->genSayisi - 1) / 2;

    // İlk yeni kromozom
    Kromozom* yeniKromozom1 = new Kromozom();
    Dugum* mevcut1 = baslangic;
    for (int i = 0; i < bolmeNoktasi1; i++) {
        yeniKromozom1->genEkle(mevcut1->gen);
        mevcut1 = mevcut1->sonraki;
    }
    Dugum* mevcut2 = diger->baslangic;
    for (int i = 0; i < bolmeNoktasi2; i++) {
        mevcut2 = mevcut2->sonraki;
    }
    while (mevcut2) {
        yeniKromozom1->genEkle(mevcut2->gen);
        mevcut2 = mevcut2->sonraki;
    }

    // İkinci yeni kromozom
    Kromozom* yeniKromozom2 = new Kromozom();
    mevcut1 = baslangic;
    for (int i = 0; i < bolmeNoktasi1; i++) {
        mevcut1 = mevcut1->sonraki;
    }
    while (mevcut1) {
        yeniKromozom2->genEkle(mevcut1->gen);
        mevcut1 = mevcut1->sonraki;
    }
    mevcut2 = diger->baslangic;
    for (int i = 0; i < bolmeNoktasi2; i++) {
        yeniKromozom2->genEkle(mevcut2->gen);
        mevcut2 = mevcut2->sonraki;
    }

    return {yeniKromozom1, yeniKromozom2};
}

// Mutasyon: Belirtilen indisteki geni "X" ile değiştirir
bool Kromozom::mutasyonYap(int genIndeksi) {
    if (genIndeksi < 0 || genIndeksi >= genSayisi) {
        return false;
    }

    Dugum* mevcut = baslangic;
    for (int i = 0; i < genIndeksi && mevcut != nullptr; i++) {
        mevcut = mevcut->sonraki;
    }
    if (mevcut != nullptr) {
        mevcut->gen = 'X';
        return true;
    }
    return false;
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
    Dugum* mevcut = baslangic;
    char ilkGen = mevcut->gen;

    while (mevcut != nullptr) {
        if (mevcut->gen < ilkGen) {
            return mevcut->gen;
        }
        mevcut = mevcut->sonraki;
    }
    return ilkGen;
}
