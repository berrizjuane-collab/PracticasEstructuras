#include <iostream>
using namespace std;

//inversor de palabras con memoria dinamica

void inversor_palabra (char *a, char *b) {
    char temporal;
    temporal = *a;
    *a = *b;
    *b = temporal;
}

int main () {

    int cantidad_letras;

    cout << "Bienvenido al inversor de palabras!" << endl;
    cout << "Introduzca la cantidad de letras que tiene su palabra: ";
    cin >> cantidad_letras;

    //aqui se crea una lista o arreglo con memoria dinamica

    char *lista_letras = new char[cantidad_letras];

    cout << "introduzca las letras" << endl;

    for (int i = 0; i < cantidad_letras; i++) {
        cout << ": " << endl;
        cin >> lista_letras[i];
    }

    char *puntero_1 = &lista_letras[0];
    char *puntero_2 = &lista_letras[cantidad_letras - 1];

    while (puntero_1 < puntero_2) {
        inversor_palabra(puntero_1,puntero_2);
        puntero_1++;
        puntero_2--;
    }

    char *puntero_impresion = lista_letras;

    for (int i = 0; i < cantidad_letras; i++) {
        cout << *puntero_impresion;
        puntero_impresion++;
    }

    delete[] lista_letras;

    return 0;

}