#include "../include/Kromozom.hpp"
#include "../include/Populasyon.hpp"
#include <fstream>
#include <sstream>

using namespace std;


void otomatikIslemleriUygula(Populasyon& populasyon) {
    ifstream dosya("islemler.txt");
    if (!dosya) {
        cerr << "Dosya acilamadi: islemler.txt" << endl;
        return;
    }

    string satir;
    while (getline(dosya, satir)) {
        istringstream iss(satir);
        char islemTipi;
        int ilk, ikinci;

        iss >> islemTipi >> ilk >> ikinci;

        if (islemTipi == 'C') {
            if (ilk >= 0 && ilk < populasyon.getKromozomSayisi() &&
                ikinci >= 0 && ikinci < populasyon.getKromozomSayisi()) {
                
                auto [yeniKromozom1, yeniKromozom2] = populasyon.kromozomAl(ilk)->caprazla(populasyon.kromozomAl(ikinci));
                
                cout << "Olusan yeni kromozom 1: ";
                yeniKromozom1->yazdir();
                cout << "Olusan yeni kromozom 2: ";
                yeniKromozom2->yazdir();
                
                populasyon.kromozomEkle(yeniKromozom1);
                populasyon.kromozomEkle(yeniKromozom2);
            } else {
                cout << "Gecersiz kromozom numarasi." << endl;
            }
        } else if (islemTipi == 'M') {
            if (ilk >= 0 && ilk < populasyon.getKromozomSayisi()) {
                cout << "Orijinal kromozom: ";
                populasyon.kromozomAl(ilk)->yazdir();

                if (!populasyon.kromozomAl(ilk)->mutasyonYap(ikinci)) {
                    cout << "Gecersiz gen numarasi. Lutfen tekrar girin: ";
                    cin >> ikinci;
                    while (!populasyon.kromozomAl(ilk)->mutasyonYap(ikinci)) {
                        cout << "Gecersiz gen numarasi. Lutfen tekrar girin: ";
                        cin >> ikinci;
                    }
                }

                cout << "Mutasyona ugrayan kromozom: ";
                populasyon.kromozomAl(ilk)->yazdir();
            } else {
                cout << "Gecersiz kromozom numarasi." << endl;
            }
        } else {
            cout << "Gecersiz islem tipi: " << islemTipi << endl;
        }
    }

    dosya.close();
}


int main() {
    Populasyon populasyon;
    ifstream dosya("dna.txt"); 

    if (!dosya) {
        cerr << "Dosya acilamadi: dna.txt" << endl;
        return 1;
    }

    string satir;
    while (getline(dosya, satir)) {
        Kromozom* yeniKromozom = new Kromozom();
        for (char gen : satir) {
            if (gen != ' ') {
                yeniKromozom->genEkle(gen);
            }
        }
        populasyon.kromozomEkle(yeniKromozom);
    }
    dosya.close();

    // Menü işlemleri
    int secim;
    do {
        cout << "1. Caprazlama" << endl;
        cout << "2. Mutasyon" << endl;
        cout << "3. Otomatik Islemler" << endl;
        cout << "4. Ekrana Yaz" << endl;
        cout << "5. Cikis" << endl;
        cout << "Seciminizi girin: ";
        cin >> secim;

        switch (secim) {
            case 1: {
                int ilkKromozom, ikinciKromozom;
                cout << "Ilk kromozom numarasini girin: ";
                cin >> ilkKromozom;
                cout << "Ikinci kromozom numarasini girin: ";
                cin >> ikinciKromozom;

                if (ilkKromozom >= 0 && ilkKromozom < populasyon.getKromozomSayisi() &&
                    ikinciKromozom >= 0 && ikinciKromozom < populasyon.getKromozomSayisi()) {
                    
                    auto [yeniKromozom1, yeniKromozom2] = populasyon.kromozomAl(ilkKromozom)->caprazla(populasyon.kromozomAl(ikinciKromozom));
                    
                    cout << "Olusan yeni kromozom 1: ";
                    yeniKromozom1->yazdir();
                    cout << "Olusan yeni kromozom 2: ";
                    yeniKromozom2->yazdir();
                    
                    populasyon.kromozomEkle(yeniKromozom1);
                    populasyon.kromozomEkle(yeniKromozom2);
                } else {
                    cout << "Gecersiz kromozom numarasi." << endl;
                }
                break;
            }
            case 2: {
                int kromozomNo, genNo;
                cout << "Kromozom numarasini girin: ";
                cin >> kromozomNo;
                cout << "Gen numarasini girin: ";
                cin >> genNo;

                if (kromozomNo >= 0 && kromozomNo < populasyon.getKromozomSayisi()) {
                    cout << "Orijinal kromozom: ";
                    populasyon.kromozomAl(kromozomNo)->yazdir();

                    if (!populasyon.kromozomAl(kromozomNo)->mutasyonYap(genNo)) {
                        cout << "Gecersiz gen numarasi. Lutfen tekrar girin: ";
                        cin >> genNo;
                        while (!populasyon.kromozomAl(kromozomNo)->mutasyonYap(genNo)) {
                            cout << "Gecersiz gen numarasi. Lutfen tekrar girin: ";
                            cin >> genNo;
                        }
                    }

                    cout << "Mutasyona ugrayan kromozom: ";
                    populasyon.kromozomAl(kromozomNo)->yazdir();
                } else {
                    cout << "Gecersiz kromozom numarasi." << endl;
                }
                break;
            }
            case 3:
                otomatikIslemleriUygula(populasyon);
                break;
            case 4:
                populasyon.kromozomlariYazdir();
                break;
            case 5:
                cout << "Program sonlandiriliyor..." << endl;
                break;
            default:
                cout << "Gecersiz secim. Tekrar deneyin." << endl;
                break;
        }
    } while (secim != 5);

    populasyon.bellekTemizle();
    return 0;
}
