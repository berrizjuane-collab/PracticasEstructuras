#include <iostream>
using namespace std;

struct nodo {
    int x;
    nodo *sig;
};

struct pila {
    nodo *tope;
};

void push(pila *recibido, nodo *nod) {

    if (recibido->tope == NULL) {
        recibido->tope = nod;
        nod->sig = NULL;
    }

    else {
        nod->sig = recibido->tope;
        recibido->tope = nod;
    }

}

nodo *pop(pila *recibido) {

    if (recibido->tope == NULL) {
        return NULL;
    }

    else {
        nodo *devolver = recibido->tope;
        recibido->tope = recibido->tope->sig;
        return devolver;
    }

}

nodo *busqueda(pila *recibido, int abuscar) {

    nodo *encontrado = NULL;
    pila aux;
    aux.tope = NULL;

    while (recibido->tope != NULL) {

        nodo *actual = pop(recibido);

        if (actual->x == abuscar) {
            encontrado = actual;
            push(&aux, actual);
            break;
        }

        else {
            push(&aux, actual);
        }

    }

    while (aux.tope != NULL) {
        nodo *recuperar = pop(&aux);
        push(recibido, recuperar);
    }

    return encontrado;

}

nodo *busqueda_recur(pila *recibido, int abuscar) {

    nodo *actual = pop(recibido);

    nodo *encontrado;

    if (actual == NULL) {
        return NULL;
    }

    if (actual->x == abuscar) {
        encontrado = actual;
    }

    else {
        encontrado = busqueda_recur(recibido, abuscar);
    }

    push(recibido, actual);

    return encontrado;

}