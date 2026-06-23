#include <iostream>
using namespace std;

struct Nodo_pila {
    int x;
    Nodo_pila *sig;
};

struct pila1 {
    Nodo_pila *tope;
};

void push(Nodo_pila *nodo, pila1 *pila) {
    if (pila->tope == NULL) {
        pila->tope = nodo;
        nodo->sig = NULL;
    }

    else {
        nodo->sig = pila->tope;
        pila->tope = nodo;
    }
}

Nodo_pila *pop(pila1 *pila) {

    Nodo_pila *nodo_devolver = pila->tope;
    pila->tope = pila->tope->sig;

    return nodo_devolver;

}

Nodo_pila *busqueda (pila1 *pila, Nodo_pila *nodo, int nodo_mod) {

    pila1 aux;
    aux.tope = NULL;
    Nodo_pila *nodo_encontrado = NULL;

    while (pila->tope != NULL) {

        Nodo_pila *actual = pop(pila);

        if (actual->x == nodo_mod) {
            nodo_encontrado = actual;
            push(actual, &aux);
            break;
        }
    }

    while (aux.tope != NULL) {
        Nodo_pila *restaurar = pop(&aux);
        push(restaurar, pila);
    }

    return nodo_encontrado;

}

Nodo_pila *busqueda_recur(pila1 *pila, int abuscar) {

    Nodo_pila *buscar = pop(pila);

    Nodo_pila *encontrado = NULL;

    if (buscar == NULL) {
        return NULL;
    }

    if (buscar->x == abuscar) {
        encontrado = buscar;
    }

    else {
        encontrado = busqueda_recur(pila,abuscar);
    }

    push(buscar, pila);

    return encontrado;
}