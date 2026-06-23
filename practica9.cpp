#include <iostream>
using namespace std;

void intercambiar (int *a, int *b) {
    int temporal = *a;
    *a = *b;
    *b = temporal;
}

int main () {
    int lista[] = {1,2,3,4,5};
    int longitud_lista = 5;

    int *puntero_1 = &lista[0];
    int *puntero_2 = &lista[4];
    
    while (puntero_1 < puntero_2) {
        intercambiar(puntero_1,puntero_2);
        puntero_1++;
        puntero_2--;
    }

    int *puntero_impresion = lista;
    
    for (int i = 0; i < longitud_lista; i++) {
        cout << *puntero_impresion << endl;
        puntero_impresion++;
    }

    return 0;
}