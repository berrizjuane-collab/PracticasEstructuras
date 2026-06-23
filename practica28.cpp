#include <iostream>
using namespace std;

struct Nodo {
    int valor;
    Nodo *siguiente;
};

struct Lista_Enlazada {
    Nodo *cabeza = NULL;
};

Lista_Enlazada *lista1 = new Lista_Enlazada();

void push(Nodo *nodo) {
    if (lista1 == NULL) {
        return;
    }

    if (lista1->cabeza == NULL) {
        lista1->cabeza = nodo;
        nodo->siguiente = NULL;
    }

    else {
        nodo->siguiente = lista1->cabeza;
        lista1->cabeza = lista1->cabeza->siguiente;
    }
}

bool esta_vacia() {
    if (lista1->cabeza == NULL) {
        return true;
    }

    else {
        return false;
    }
}

bool no_existe() {
    if (lista1 == NULL) {
        return true;
    }

    else {
        return false;
    }
    
}

Nodo *pop(int abuscar) {

    if (esta_vacia()) {
        return NULL;
    }

    if (no_existe()) {
        return NULL;
    }

    Nodo *actual = lista1->cabeza;

    while (actual != NULL && actual->valor != abuscar) {
        actual = actual->siguiente;
    }

    return actual;

}

void destruir() {

    if (esta_vacia() || no_existe()) {
        return;
    }

    Nodo *actual = lista1->cabeza;
    Nodo *anterior = NULL;

    while(actual != NULL) {
        anterior = actual;
        actual = actual->siguiente;
        delete anterior;
    }

    delete lista1;
    lista1 = NULL;
}