#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo *siguiente;
};

Nodo *lista_enlazada = NULL;

void meter(Nodo *nodo) {

    if (lista_enlazada == NULL) {
        lista_enlazada = nodo;
        nodo->siguiente = NULL;
    }

    else {
        nodo->siguiente = lista_enlazada;
        lista_enlazada = nodo;
    }

}

bool esta_vacia() {
    if (lista_enlazada == NULL) {
        return true;
    }

    else {
        return false;
    }
}

Nodo *buscar(int abuscar) {
    if (esta_vacia()) {
        return NULL;
    }

    Nodo *actual = lista_enlazada;

    while (actual != NULL && actual->dato != abuscar) {
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        return NULL;
    }

    else {
        return actual;
    }

}

void destruir() {
    if (esta_vacia()) {
        return;
    }

    Nodo *actual = lista_enlazada;
    Nodo *anterior = NULL;

    while (actual != NULL) {
        anterior = actual;
        actual = actual->siguiente;
        delete anterior;
    }

    lista_enlazada = NULL;
}



