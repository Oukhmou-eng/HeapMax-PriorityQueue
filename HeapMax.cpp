#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class MaxHeap {
    vector<int> heap;

    int parent(int i) const { return (i - 1) / 2; }
    int fg(int i) const { return 2 * i + 1; }

public:
   void insert(int nombre) {
    auto debut = chrono::high_resolution_clock::now();

    for (int j = 0; j < nombre; j++) {
        heap.push_back(j);
        int i = heap.size() - 1;
        while (i > 0 && heap[i] > heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    auto fin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();
    cout << "Temps d'insertion pour " << nombre << " elements : "
         << duree / 1000000.0 << " millisecondes." << endl;
}



    void remove() {
        if (heap.empty()) {
            cout << "Le tas est vide.\n";
            return;
        }

        auto debut = chrono::high_resolution_clock::now();

        int v = heap.back();   // valeur à replacer depuis la racine
        heap.pop_back();
        int n = heap.size();

        if (n > 0) {
            int i = 0;
            while (fg(i) < n) {
                int f = fg(i);
                if (f + 1 < n && heap[f + 1] > heap[f]) f++;  // plus grand fils
                if (heap[f] <= v) break;
                heap[i] = heap[f];   // le fils monte (pas de swap)
                i = f;
            }
            heap[i] = v;
        }

        auto fin = chrono::high_resolution_clock::now();
        auto duree = chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();
        cout << "Temps de suppression de racine : " << duree / 1000.0
             << " microsecondes." << endl;
    }

    void afficher() const {
        for (int v : heap) cout << v << " ";
        cout << "\n";
    }
};











int main() {
    MaxHeap maxHeap;
    int choix, valeur;

    do {
        cout << "\n1. Ajouter\n2. Supprimer\n3. Afficher\n0. Quitter\nChoix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                cout << "Nombres d elements : ";
                cin >> valeur;
                maxHeap.insert(valeur);
                break;
            case 2:
                maxHeap.remove();
                break;
            case 3:
                maxHeap.afficher();
                break;
        }
    } while (choix != 0);
}