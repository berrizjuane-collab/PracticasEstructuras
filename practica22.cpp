// COLAS

#include <iostream>
using namespace std;

struct Nodo_cola {
    int x;
    Nodo_cola *sig;
};

struct cola {
    Nodo_cola *frente;
    Nodo_cola *final;
};

void push(cola *recibido, Nodo_cola *nodo) {

    if (recibido->frente == NULL) {
        recibido->frente = nodo;
        recibido->final = nodo;
        nodo->sig = NULL;
    }

    else {
        recibido->final = nodo;  // El nodo FINAL apunta al nuevo, ya que entra por detras
        nodo->sig = NULL;
    }

}

Nodo_cola *pop(cola *recibido) {

    Nodo_cola *devolver = NULL;

    if (recibido->frente->sig == NULL) {
        devolver = recibido->frente;
        recibido->frente = NULL;
        recibido->final = NULL;
    }

    else {
        devolver = recibido->frente;
        recibido->frente = recibido->frente->sig;
    }

    return devolver;

}

Nodo_cola *buscar(cola *recibido, Nodo_cola *nodo, int info) {

    cola aux;
    aux.final = NULL;
    aux.frente = NULL;

    Nodo_cola *encontrado = NULL;

    while (recibido->frente != NULL) {
        Nodo_cola *actual = pop(recibido);

        if (actual->x == info) {
            encontrado = actual;
            push(&aux, actual);
            // sin break para que se traspase toda la cola
        }

        else {
            push(&aux, actual);
        }

    }

    while (aux.frente != NULL || aux.final != NULL) {
        Nodo_cola *restaurar = pop(&aux);
        push(recibido, restaurar);
    }

    return encontrado;

}

Nodo_cola *busqueda_recur (cola *recibido, int abuscar) {

    Nodo_cola *buscar = pop(recibido);

    if (buscar->x == abuscar) {
        return buscar;
    }

    else {
        busqueda_recur(recibido, abuscar);
    }
    
}

