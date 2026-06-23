//inversor de palabras con punteros
#include <iostream>
using namespace std;

void intercambiar (char *a, char *b) {
    char temporal = *a;
    *a = *b;
    *b = temporal;
}

int main() {
    cout << "Introduzca la palabra letra por letra, maximo 4 letras" << endl;

    char letra_1;
    char letra_2;
    char letra_3;
    char letra_4;

    char lista_letras[4];

    cin >> letra_1;
    cin >> letra_2;
    cin >> letra_3;
    cin >> letra_4;

    lista_letras[0] = letra_1;
    lista_letras[1] = letra_2;
    lista_letras[2] = letra_3;
    lista_letras[3] = letra_4;

    char *puntero_1 = &lista_letras[0];
    char *puntero_2 = &lista_letras[3];

    while (puntero_1 < puntero_2) {
        intercambiar(puntero_1,puntero_2);
        puntero_1++;
        puntero_2--;
    }

    char *puntero_impresion = lista_letras;

    int capacidad_lista = 4;

    for (int i = 0; i < capacidad_lista; i++) {
        cout << *puntero_impresion << endl;
        puntero_impresion++;
    }

    return 0;
}