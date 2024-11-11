// include/Kromozom.hpp

#ifndef KROMOZOM_HPP
#define KROMOZOM_HPP

#include <iostream>
#include <utility>
using namespace std;

class Kromozom {
private:
    struct Dugum {
        char gen;
        Dugum* sonraki;
        Dugum(char g) : gen(g), sonraki(nullptr) {}
    };

    Dugum* baslangic;
    int genSayisi;

public:
    Kromozom();
    ~Kromozom();

    void genEkle(char gen);
    pair<Kromozom*, Kromozom*> caprazla(Kromozom* diger);
    void mutasyonYap(int genIndeksi);
    void yazdir() const;
    int genSayisiniAl() const;
    char kucukGenBul() const;
};

#endif
