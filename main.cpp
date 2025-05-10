#include <iostream>
#include <string>
#include <cstdlib> // pro  práci s náhodnými čísly
#include <ctime> // pro to aby generovaná čísla byla každé spuštěně odlišná
#include <limits> // pro ignorování neplatného vstupu

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

void zobrazInfo() {
    cout << "\nInformace o classach:\n";
    cout << "1. Frank: Zivoty: 10, Utok: 3, Zlato: 100\n";
    cout << "2. Hunter: Zivoty: 8, Utok: 4, Zlato: 80\n";
    cout << "3. Maverick: Zivoty: 6, Utok: 5, Zlato: 50\n";
    cout << "4. Steve: Zivoty: 7, Utok: 3, Zlato: 70\n";
}

Class vyberClass() {
    Class paladin = {"Frank", 10, 10, 3, 100, 1, 0};
    Class hunter = {"Hunter", 8, 8, 4, 80, 1, 0};
    Class mage = {"Maverick", 6, 6, 5, 50, 1, 0};
    Class warlock = {"Steve", 7, 7, 3, 70, 1, 0};

    int choice;
    while (true) {
        cout << "\nVyber si classu:\n";
        cout << "1. Frank\n";
        cout << "2. Hunter\n";
        cout << "3. Maverick\n";
        cout << "4. Steve\n";
        cout << "5. Zobrazit informace o classach\n";
        cout << "Zadej cislo 1-5: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neplatna volba! Zadej cislo mezi 1 a 5.\n";
            continue;
        }

        if (choice == 5) {
            zobrazInfo();
        } else if (choice >= 1 && choice <= 4) {
            switch (choice) {
                case 1: return paladin;
                case 2: return hunter;
                case 3: return mage;
                case 4: return warlock;
            }
        } else {
            cout << "Neplatna volba! Zkus to znovu.\n";
        }
    }
}

void zkontrolujLevelUp(Class &hrac) {
    while (hrac.zkusenosti >= 20) {
        hrac.zkusenosti -= 20;
        hrac.level += 1;
        hrac.maxZivoty += 1;
        hrac.currentZivoty = hrac.maxZivoty;
        cout << "\nPostoupil jsi na level " << hrac.level << "! Zvyseny max zivoty na " << hrac.maxZivoty << ".\n";
    }
}

void tahovyBoj(Class &hrac, Monster &nepritel) {
    cout << "\nSouboj zacina! Tvym souperem je " << nepritel.name << ".\n";

    bool obranaPouzita = false;

    while (hrac.currentZivoty > 0 && nepritel.currentZivoty > 0) {
        int volba;
        cout << "\nZvol svou akci:\n";
        cout << "1. Utok\n";
        cout << "2. Obrana (lze pouzit jen jednou za souboj)\n";
        cout << "3. Pouziti lektvaru (+5 zivotu, ale moznost otravy -2 zivoty)\n";
        cin >> volba;

        switch (volba) {
            case 1:
                cout << hrac.name << " utoci a udeluje " << hrac.utok << " poskozeni.\n";
                nepritel.currentZivoty -= hrac.utok;
                break;
            case 2:
                if (!obranaPouzita) {
                    obranaPouzita = true;
                    cout << hrac.name << " se brani a snizuje poskozeni z utoku souperu na polovinu v tomto kole.\n";
                    nepritel.utok /= 2;
                } else {
                    cout << "Obrana jiz byla pouzita! Ztracis tah.\n";
                }
                break;
            case 3: {
                int sanceNaOtravu = rand() % 2;
                if (hrac.currentZivoty < hrac.maxZivoty) {
                    if (sanceNaOtravu == 0) {
                        hrac.currentZivoty += 5;
                        if (hrac.currentZivoty > hrac.maxZivoty)
                            hrac.currentZivoty = hrac.maxZivoty;
                        cout << "Pouzil jsi lektvar! Aktualni zivoty: " << hrac.currentZivoty << endl;
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
            zkontrolujLevelUp(hrac);
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
        cout << "\nVesnice - Moznosti:\n";
        cout << "1. Zakoupit helmu (+1 zivot nad maximum za 50 zlata)\n";
        cout << "2. Doplnit zivoty na maximum (za 20 zlata)\n";
        cout << "3. Opustit vesnici\n";
        cin >> volba;

        switch (volba) {
            case 1:
                if (hrac.zlato >= 50) {
                    hrac.currentZivoty += 1;
                    hrac.zlato -= 50;
                    cout << "Zakoupil jsi helmu! Aktualni zivoty: " << hrac.currentZivoty << ".\n";
                    cout << "Zbyvajici zlato: " << hrac.zlato << ".\n";
                } else {
                    cout << "Nemas dostatek zlata.\n";
                }
                break;
            case 2:
                if (hrac.zlato >= 20) {
                    hrac.currentZivoty = hrac.maxZivoty;
                    hrac.zlato -= 20;
                    cout << "Zivoty doplneny. Aktualni zivoty: " << hrac.currentZivoty << ".\n";
                } else {
                    cout << "Nemas dostatek zlata.\n";
                }
                break;
            case 3:
                cout << "Opoustis vesnici.\n";
                return;
            default:
                cout << "Neplatna volba!\n";
        }
    }
}

void zahadnaJeskyne(Class &hrac) {
    int volba;
    cout << "\nNarazil jsi na zahadnou jeskyni. Chces do ni vstoupit?\n";
    cout << "1. Ano\n";
    cout << "2. Ne\n";
    cin >> volba;

    if (volba == 1) {
        int sance = rand() % 100;

        if (sance < 40) {
            // Starec s hadankou
            cout << "\nV jeskyni jsi potkal stareho starce. Podiva se na tebe a rekne:\n";
            cout << "\"Kdyz mi odpovis na mou hadanku, obdarim te zlatem a posilim tvou dusi.\"\n";
            cout << "Hadanka: Co ma jeden krk, ale zadnou hlavu?\n";
            cout << "1. Lampa\n";
            cout << "2. Triko\n";
            cout << "3. Strom\n";
            cout << "4. Hrib\n";
            int odpoved;
            cin >> odpoved;

            if (odpoved == 2) {
                cout << "Spravne! Starec se usmeje a rekne: \"Moudrost je tvou silou.\"\n";
                hrac.zlato += 50;
                hrac.zkusenosti += 20;
                zkontrolujLevelUp(hrac);
                cout << "Ziskal jsi 50 zlata a zkusenosti!\n";
            } else {
                cout << "Spatne! Starec zmizi v mlze a nezanecha po sobe nic...\n";
            }
        } else if (sance < 70) {
            cout << "Nasel jsi 20 zlata!\n";
            hrac.zlato += 20;
        } else {
            cout << "Potkal jsi jeskynni carodejnici! Otravi te a sebere vsechno zlato!\n";
            hrac.zlato = 0;
            hrac.currentZivoty -= 3;
            if (hrac.currentZivoty < 1) hrac.currentZivoty = 1;
        }
    } else {
        cout << "Rozhodl ses jeskyni vynechat.\n";
    }
}

int main() {
    srand(time(0));
    cout << "Vitej ve hre!\n";
    Class hrac = vyberClass();

    Monster monster1 = {"Monstrum", 8, 8, 1, false};
    Monster miniBoss = {"Mini Boss", 12, 12, 2, true};

    tahovyBoj(hrac, monster1);
    tahovyBoj(hrac, miniBoss);
    navstivVesnici(hrac);
    zahadnaJeskyne(hrac);

    cout << "\nDobrodruzstvi skoncilo! Zvladnes dalsi cestu?\n";
    cout << "Zivoty: " << hrac.currentZivoty << "/" << hrac.maxZivoty << ", Zlato: " << hrac.zlato << ", Level: " << hrac.level << endl;
    return 0;
}
