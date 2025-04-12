#include <iostream>
#include <string>
using namespace std;

struct Class {
    string name;
    int maxZivoty;
    int currentZivoty;
    int maxEnergie;
    int currentEnergie;
    int zlato;
    int level;
    int zkusenosti;
    int utok;
};
void ukazInformaceOClasse(Class classPostavy) {
    cout << "\nClass: " << classPostavy.name << endl;
    cout << "Statistiky:" << endl;
    cout << "  Zivot - " << classPostavy.currentZivoty << "/" << classPostavy.maxZivoty << endl;
    cout << "  Mana - " << classPostavy.currentEnergie << "/" << classPostavy.maxEnergie << endl;
    cout << "  Utok - " << classPostavy.utok << endl;
}

Class vyberClass() {
    Class paladin = {"Frank", 5, 5, 2, 0, 100, 1, 0, 3};
    Class hunter = {"Hunter", 4, 4, 3, 3, 80, 1, 0, 4};
    Class mage = {"Phoenix", 3, 3, 6, 6, 70, 1, 0, 2};
    Class warlock = {"Maverick", 4, 4, 5, 5, 60, 1, 0, 3};

    while (true) {
        cout << "\nVyber si classu:\n";
        cout << "1. Frank\n";
        cout << "2. Hunter\n";
        cout << "3. Phoenix\n";
        cout << "4. Maverick\n";
        cout << "5. Zobrazit informace o classach\n";
        cout << "6. Ukoncit vyber\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                return paladin;
            case 2:
                return hunter;
            case 3:
                return mage;
            case 4:
                return warlock;
            case 5:

                cout << "\nInformace o classach:\n";
                ukazInformaceOClasse(paladin);
                ukazInformaceOClasse(hunter);
                ukazInformaceOClasse(mage);
                ukazInformaceOClasse(warlock);
                break;
            case 6:
                cout << "Ukoncujete vyber...\n";
                exit(0);
            default:
                cout << "Neplatna volba! Zkus to znovu.\n";
        }
    }
}

int main() {
    cout << "Vitejte ve hre!\n";

    Class vybranaClass = vyberClass();

    cout << "\nZvolil jsi classu:\n";
    ukazInformaceOClasse(vybranaClass);

    cout << "Hodne stesti ve hre!" << endl;
    return 0;
}

