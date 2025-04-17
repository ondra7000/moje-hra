#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

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

    if (nepritel.isMiniBoss) {
        int damage = nepritel.utok;
        cout << nepritel.name << " utoci a udeluje " << damage << " poskozeni!\n";
        hrac.currentZivoty -= damage;

        if (hrac.currentZivoty <= 0) {
            cout << "Hrac byl porazen! Hra konci.\n";
            exit(0);
        }
    }

    while (hrac.currentZivoty > 0 && nepritel.currentZivoty > 0) {
        cout << hrac.name << " se brani a vraci utok! Udeluje " << hrac.utok << " poskozeni.\n";
        nepritel.currentZivoty -= hrac.utok;

        if (nepritel.currentZivoty <= 0) {
            cout << "Souper byl porazen!\n";
            hrac.zkusenosti += 10;
            cout << "Ziskal jsi 10 zkusenosti! Aktualni zkusenosti: " << hrac.zkusenosti << endl;


            if (nepritel.isMiniBoss || (rand() % 2 == 0)) {
                hrac.zlato += 20;
                cout << "Ziskal jsi zlato! Aktualni zlato: " << hrac.zlato << endl;
            }

            if (nepritel.isMiniBoss) {
                hrac.currentZivoty += 1;
                cout << "Doplneni zivotu! Aktualni zivoty: " << hrac.currentZivoty << endl;
            } else {
                hrac.currentZivoty += 2;
                cout << "Doplneni zivotu! Aktualni zivoty: " << hrac.currentZivoty << endl;
            }


            if (hrac.zkusenosti >= 20) {
                hrac.level++;
                hrac.maxZivoty += 2;
                hrac.currentZivoty = hrac.maxZivoty;
                hrac.utok += 1;
                cout << "Novy level! Max zivot: " << hrac.maxZivoty << ", Utok: " << hrac.utok << endl;
            }

            if (nepritel.name == "Hlavni Boss") {
                cout << "Gratulace! Porazil jsi hlavniho bosse a hra konci vitezstvim!\n";
                exit(0);
            }

            return;
        }


        int damage = nepritel.utok;
        cout << nepritel.name << " utoci a udeluje " << damage << " poskozeni!\n";
        hrac.currentZivoty -= damage;

        if (hrac.currentZivoty <= 0) {
            cout << "Hrac byl porazen! Hra konci.\n";
            exit(0);
        }

        cout << "Hrac - Zivoty: " << hrac.currentZivoty << "/" << hrac.maxZivoty << endl;
        cout << "Souper - Zivoty: " << nepritel.currentZivoty << "/" << nepritel.maxZivoty << endl;
    }
}

Class vyberClass() {
    Class paladin = {"Frank", 10, 10, 3, 100, 1, 0};
    Class hunter = {"Hunter", 8, 8, 4, 80, 1, 0};
    Class mage = {"Maverick", 6, 6, 2, 70, 1, 0};
    Class warlock = {"Steve", 7, 7, 3, 60, 1, 0};

    cout << "\nVyber si classu:\n1. Frank\n2. Hunter\n3. Maverick\n4. Steve\n";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1: return paladin;
        case 2: return hunter;
        case 3: return mage;
        case 4: return warlock;
        default:
            cout << "Neplatna volba! Zkus to znovu.\n";
            return vyberClass();
    }
}

int main() {
    srand(time(0));
    cout << "Vitej ve hre!\n";
    Class hrac = vyberClass();

    Monster monster1 = {"Goblin", 8, 8, 2, false};
    Monster miniBoss = {"Mini Boss", 2, 2, 1, true};
    Monster boss = {"Hlavni Boss", 5, 5, 4, true};

    tahovyBoj(hrac, monster1);
    tahovyBoj(hrac, miniBoss);
    tahovyBoj(hrac, boss);

    return 0;
}
