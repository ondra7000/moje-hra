#include <iostream>
#include <string>
#include <cstdlib> // pro  pr�ci s n�hodn�mi ��sly
#include <ctime>  // pro to aby generovan� ��sla byla ka�d� spu�t�n� odli�n�
#include <limits> // pro ignorov�n� neplatn�ho vstupu

using namespace std;

struct Class {
    string name;
    int maxZivoty;
    int currentZivoty;
    int utok;
    int zlato;
    int level;
    int zkusenosti;
};

struct Monster {
    string name;
    int maxZivoty;
    int currentZivoty;
    int utok;
    bool isMiniBoss;
};

void tahovyBoj(Class &hrac, Monster &nepritel) {
    cout << "\nSouboj zacina! Tvym souperem je " << nepritel.name << ".\n";

    bool obranaPouzita = false; // Sledov�n�, zda ji� byla obrana pou�ita

    while (hrac.currentZivoty > 0 && nepritel.currentZivoty > 0) {
        int volba;
        cout << "\nZvol svou akci:\n";
        cout << "1. Utok\n";
        cout << "2. Obrana (lze pouzit jen jednou za souboj)\n";
        cout << "3. Pouziti leciveho lektvaru (+5 zivotu, ale moznost otravy -2 zivoty)\n";
        cin >> volba;

        switch (volba) {
            case 1:
                cout << hrac.name << " utoci a udeluje " << hrac.utok << " poskozeni.\n";
                nepritel.currentZivoty -= hrac.utok;
                break;

            case 2:
                if (!obranaPouzita) {
                    obranaPouzita = true;
                    cout << hrac.name << " se brani a sniuje poskozeni z utoku souperu na polovinu v tomto kole.\n";
                    nepritel.utok /= 2; // Do�asn� sni�en� �toku nep��tele
                } else {
                    cout << "Obrana jiz byla pouzita! Ztracis tah.\n";
                }
                break;

            case 3: {
                int sanceNaOtravu = rand() % 2; // 50% �ance na otravu
                if (hrac.currentZivoty < hrac.maxZivoty) {
                    if (sanceNaOtravu == 0) {
                        hrac.currentZivoty += 5;
                        if (hrac.currentZivoty > hrac.maxZivoty)
                            hrac.currentZivoty = hrac.maxZivoty; // Zaji�t�n�, �e �ivoty nep�ekro�� maximum
                        cout << "Pouzil jsi lecivy lektvar! Aktualni zivoty: " << hrac.currentZivoty << endl;
                    } else {
                        hrac.currentZivoty -= 2;
                        cout << "Lektvar te otravil! Ztratil jsi 2 zivoty. Aktualni zivoty: " << hrac.currentZivoty << endl;
                    }
                } else {
                    cout << "Mas plne zivoty a nelze pouzit lektvar.\n";
                }
                break;
            }

            default:
                cout << "Neplatna volba! Ztracis tah.\n";
        }

        if (nepritel.currentZivoty <= 0) {
            cout << "Souper byl porazen!\n";
            hrac.zkusenosti += 10;
            cout << "Ziskal jsi 10 zkusenosti! Aktualni zkusenosti: " << hrac.zkusenosti << endl;
            return;
        }

        int damage = nepritel.utok;
        cout << nepritel.name << " utoci a udeluje " << damage << " poskozeni!\n";
        hrac.currentZivoty -= damage;

        if (hrac.currentZivoty <= 0) {
            cout << "Hrac byl porazen! Hra konci.\n";
            exit(0);
        }

        cout << "\nHrac - Zivoty: " << hrac.currentZivoty << "/" << hrac.maxZivoty << endl;
        cout << "Souper - Zivoty: " << nepritel.currentZivoty << "/" << nepritel.maxZivoty << endl;
    }
}

void navstivVesnici(Class &hrac) {
    int volba;

    cout << "\nNarazil jsi na vesnici! Aktualni zlato: " << hrac.zlato << ".\n";
    cout << "Chces ji navstivit?\n";
    cout << "1. Ano\n";
    cout << "2. Ne\n";
    cin >> volba;

    if (volba == 2) {
        cout << "Pokracujes ve sve ceste bez navstevy vesnice.\n";
        return;
    }

    while (true) {
        cout << "\nVitej ve vesnici! Co bys chtel udelat?\n";
        cout << "1. Zakoupit helmu (+1 zivot nad maximalni pocet zivotu za 30 zlata)\n";
        cout << "2. Doplnit zivoty na maximum (za 10 zlata)\n";
        cout << "3. Opustit vesnici\n";
        cin >> volba;

        switch (volba) {
            case 1: // N�kup helmy
                if (hrac.zlato >= 30) {
                    hrac.currentZivoty += 1; // P�id�n� 1 �ivota nad maximum
                    hrac.zlato -= 30;
                    cout << "Zakoupil jsi helmu! Aktualni zivoty: " << hrac.currentZivoty << ".\n";
                    cout << "Zbyvajici zlato: " << hrac.zlato << ".\n";
                } else {
                    cout << "Nemas dostatek zlata na zakoupeni helmy.\n";
                }
                break;

            case 2: // Dopln�n� �ivot�
                if (hrac.zlato >= 10) {
                    hrac.currentZivoty = hrac.maxZivoty;
                    hrac.zlato -= 10;
                    cout << "Tve zivoty byly doplneny na maximum. Aktualni zivoty: " << hrac.currentZivoty << ".\n";
                    cout << "Zbyvajici zlato: " << hrac.zlato << ".\n";
                } else {
                    cout << "Nem� dostatek zlata na dopln�n� �ivot�.\n";
                }
                break;

            case 3: // Opustit vesnici
                cout << "Opoustis vesnici. Hodne stesti na tve ceste!\n";
                return;

            default:
                cout << "Neplatna volba! Zkus to znovu.\n";
        }
    }
}

Class vyberClass() {
    Class paladin = {"Frank", 10, 10, 3, 100, 1, 0};
    Class hunter = {"Hunter", 8, 8, 4, 80, 1, 0};
    Class mage = {"Maverick", 6, 6, 2, 70, 1, 0};
    Class warlock = {"Steve", 7, 7, 3, 60, 1, 0};

    cout << "\nVyber si classu:\n1. Frank\n2. Hunter\n3. Maverick\n4. Steve\n";

    int choice;

    while (true) {
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear(); // Vy�ist� chybov� stav cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neplatna volba! Zadej cislo mezi 1 a 4.\n";
        } else {
            break;
        }
    }

    switch (choice) {
        case 1: return paladin;
        case 2: return hunter;
        case 3: return mage;
        case 4: return warlock;
        default:
            return paladin;
    }
}

int main() {
    srand(time(0));
    cout << "Vitej ve hre!\n";
    Class hrac = vyberClass();

    Monster monster1 = {"Goblin", 8, 8, 2, false};
    Monster miniBoss = {"Mini Boss", 12, 12, 4, true};
    Monster boss = {"Hlavni Boss", 20, 20, 8, true};

    tahovyBoj(hrac, monster1);
    navstivVesnici(hrac);
    tahovyBoj(hrac, miniBoss);
    navstivVesnici(hrac);
{

}

}
