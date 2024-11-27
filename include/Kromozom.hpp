/**
* @file         Kromozom.hpp
* @description  krormozom sınıfının başlık dosyası.
* @course       2-C
* @assignment   1. Ödev
* @date         27.11.2024
* @author       Osman Can YILDIZ - osman.yildiz4@ogr.sakarya.edu.tr
*/ 
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
        Dugum* onceki;
        Dugum(char g) : gen(g), sonraki(nullptr), onceki(nullptr) {}
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
