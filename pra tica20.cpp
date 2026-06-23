#include <iostream>
using namespace std;


struct Nodo_pila {
    int x;
    Nodo_pila *sig;
};

struct pila1 {
    Nodo_pila *tope;
};

Nodo_pila *busqueda_nodo(int nodo_buscar, pila1 *recibido) {

    Nodo_pila *nodo_encontrado = NULL;
    pila1 aux;
    aux.tope = NULL;

    while (recibido->tope != NULL) {
        Nodo_pila *actual = recibido->tope;
        recibido->tope = recibido->tope->sig;

        actual->sig = aux.tope;
        aux.tope = actual;

        if (actual->x == nodo_buscar) {
            nodo_encontrado = actual;
            break;
        }
        
    }

    while (aux.tope != NULL) {
        Nodo_pila *nodo_restaurar = aux.tope;
        aux.tope = aux.tope->sig;
        
        nodo_restaurar->sig = recibido->tope;
        recibido->tope = nodo_restaurar;
    }

    return nodo_encontrado;
}

pila1* push(Nodo_pila *nodo, pila1 *recibido) {

    if (recibido->tope == NULL) {
        recibido->tope = nodo;
        nodo->sig = NULL;
    }

    else {
        nodo->sig = recibido->tope;
        recibido->tope = nodo;
    }

    return recibido;
}

Nodo_pila *pop(pila1 *recibido) {

    if (recibido->tope == NULL) {
        return;
    }

    Nodo_pila *actual = recibido->tope;
    recibido->tope = recibido->tope->sig;

    return actual;

}

Nodo_pila *nodo_especifico(pila1 *recibido, int nodo_buscar) {

    Nodo_pila *nodo_devolver = NULL;
    pila1 aux;
    
    aux.tope = NULL;

    Nodo_pila *nodo_encontrado = NULL;

    while (nodo_devolver->x != nodo_buscar) {

        nodo_devolver = pop(recibido);
        aux = push(nodo_devolver,aux);

        if (nodo_devolver->x == nodo_buscar) {
        nodo_encontrado = nodo_devolver;
        break;
        }

    }

    while (aux.tope != NULL) {
        Nodo_pila *apuntador = aux.tope;
        Nodo_pila *nodo_restaurar = pop(apuntador)
    }

}
