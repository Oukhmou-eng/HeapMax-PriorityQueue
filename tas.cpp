#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

class TasMax {
    priority_queue<int> tas;
    mt19937 gen{random_device{}()};
    uniform_int_distribution<int> dist{0, 1000000};

public:
    void ajouter(int nombre) {
        // Valeurs générées avant le chronomètre
        vector<int> valeurs(nombre);
        


        // Tri pour simuler un scénario d'insertion plus réaliste
        sort(valeurs.begin(), valeurs.end());

        for (int& x : valeurs) x = dist(gen);

        auto debut = chrono::high_resolution_clock::now();

        if (tas.empty()) {
            // Construction d'un coup en O(n)
            tas = priority_queue<int>(less<int>(), move(valeurs));
        } else {
            for (int v : valeurs) tas.push(v);
        }

        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duree = fin - debut;
        cout << "Temps d'insertion pour " << nombre << " elements : "
             << duree.count() << " millisecondes.\n";
    }

    void supprimer() {
        if (tas.empty()) {
            cout << "Le tas est vide.\n";
            return;
        }
        auto debut = chrono::high_resolution_clock::now();
        tas.pop();
        auto fin = chrono::high_resolution_clock::now();

        chrono::duration<double, micro> duree = fin - debut;
        cout << "Temps de suppression : " << duree.count() << " microsecondes.\n";
    }

    void afficher() const {
        auto copie = tas;
        while (!copie.empty()) {
            cout << copie.top() << " ";
            copie.pop();
        }
        cout << "\n";
    }
};








int main() {
    TasMax tasMax;
    int choix, nombre;

    do {
        cout << "\n1. Ajouter\n2. Supprimer\n3. Afficher\n0. Quitter\nChoix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                cout << "Nombre de valeurs a ajouter : ";
                cin >> nombre;
                tasMax.ajouter(nombre);
                break;
            case 2:
                tasMax.supprimer();
                break;
            case 3:
                tasMax.afficher();
                break;
        }
    } while (choix != 0);
}