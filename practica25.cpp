#include <iostream>
using namespace std;

struct Nodo{
  int dato;
  Nodo *siguiente;  
};

struct Pila{
    Nodo *tope = NULL;
};

Pila *pila1 = new Pila();

void push(Nodo *recibido, Pila *pila1) {
    if (pila1 == NULL) {
        return;
    }

    if (pila1->tope == NULL) {
        pila1->tope = recibido;
        recibido->siguiente = NULL;
    }

    else {
        recibido->siguiente = pila1->tope;
        pila1->tope = recibido;
    }
}

Nodo *pop(Pila *pila1) {

    if (pila1 == NULL) {
        return NULL;
    }

    if (pila1->tope == NULL) {
        return NULL;
    }

    Nodo *devolver = pila1->tope;
    pila1->tope = pila1->tope->siguiente;

    devolver->siguiente = NULL;
    return devolver;
}

Nodo *buscar_especifico(Pila *pila1, int abuscar) {
    if (pila1 == NULL) {
        return NULL;
    }

    if (pila1->tope == NULL) {
        return NULL;
    }

    Pila aux;
    aux.tope = NULL;

    Nodo *encontrado = NULL;

    while (pila1->tope != NULL) {
        Nodo *actual = pop(pila1);

        if (actual->dato == abuscar) {
            encontrado = actual;
            push(actual, &aux);
        }
        

        else {
            push(actual, &aux);
        }
    }

    while (aux.tope != NULL) {
        Nodo *restaurar = pop(&aux);
        push(restaurar, pila1);
    }

    return encontrado;
}

void eliminar(Pila *&pila1) {

    if (pila1 == NULL) {
        return;
    }

    if (pila1->tope == NULL) {
        return;
    }

    while (pila1->tope != NULL) {
        Nodo *eliminar = pop(pila1);
        delete eliminar;
    }

    delete pila1;
    pila1 = NULL;

}