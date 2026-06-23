#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo *siguiente;
};

struct Cola {
    Nodo *frente = NULL;
    Nodo *final = NULL;
};

Cola *cola1 = new Cola();

void push(Nodo *recibido, Cola *cola) {
    if (cola == NULL) {
        return;
    }

    if (recibido == NULL) {
        return;
    }

    if (cola->frente == NULL) {
        cola->frente = recibido;
        cola->final = recibido;
        recibido->dato = NULL;
    }

    else {
        cola->final->siguiente = recibido;
        cola->final = recibido;
        recibido->siguiente = NULL;
    }
}

Nodo *pop(Cola *cola) {
    if (cola == NULL) {
        return NULL;
    }

    if (cola->frente == NULL) {
        return NULL;
    }

    Nodo *devolver = cola->frente;
    cola->frente = cola->frente->siguiente;

    devolver->siguiente = NULL;
    return devolver;

}

Nodo *busqueda_especifica(Cola *cola, int abuscar) {

    if (cola == NULL) {
        return NULL;
    }

    if (cola->frente == NULL) {
        return NULL;
    }

    Cola aux;
    aux.frente = NULL;
    aux.final = NULL;

    Nodo *encontrado = NULL;

    while (cola->frente != NULL || cola->final != NULL) {
        Nodo *actual = pop(cola);

        if (actual->dato == abuscar) {
            encontrado = actual;
            push(actual, &aux);
        }

        else {
            push(actual, &aux);
        }
    }

    while (aux.frente != NULL) {
        Nodo *restaurar = pop(&aux);
        push(restaurar, cola);
    }

    return encontrado;
}

void eliminar(Cola *&cola) {
    if (cola == NULL) {
        return;
    }

    if (cola->frente == NULL) {
        return;
    }

    while (cola->frente != NULL) {
        Nodo *eliminar = pop(cola);
        delete eliminar;
    }

    delete cola;
    cola = NULL;
}