#include <iostream>
using namespace std;

struct Nodo{
    int dato;
    Nodo *siguiente;
};

struct Lista_Enlazada{
    Nodo *cabeza;
};

Lista_Enlazada *lista1 = new Lista_Enlazada();

void meter(Nodo *recibido, Lista_Enlazada *lista){
    
    if (lista->cabeza == NULL) {
        lista->cabeza = recibido;
        recibido->siguiente = NULL;
    }

    else {
        recibido->siguiente = lista->cabeza;
        lista->cabeza = recibido;
    }
}

void eliminar(Lista_Enlazada *&lista) {

    Nodo *actual = lista->cabeza;
    Nodo *temporal = NULL;

    while (actual != NULL) {
        temporal = actual;
        actual = actual->siguiente;
        delete temporal;
    }

    delete lista;
    lista = NULL;

}

Nodo *buscar_especifico(Lista_Enlazada *lista, int dato_buscar) {

    Nodo *actual = lista->cabeza;

    while (actual != NULL && actual->dato != dato_buscar) {
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        return NULL;
    }

    else {
        return actual;
    }
}

void crear() {

    Nodo *nuevo = new Nodo;
    nuevo->dato = 5;
    
    meter(nuevo, lista1);

}
