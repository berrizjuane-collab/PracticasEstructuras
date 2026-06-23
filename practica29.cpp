#include <iostream>
using namespace std;

// Se tiene una lista simplemente enlazada A y una doblemente enlazada B, se desea mover todos los nodos de B con valores pares al final de A. Solo quedaran
// los nodos con valores impar en B. Se puede usar una sola estructura auxiliar.

struct Nodo {
    int dato;
    Nodo *sig = NULL;
    Nodo *anterior = NULL;
};

Nodo *pop(Nodo *&cabeza) {
    Nodo *actual = cabeza;
    if (actual == NULL) {
        return NULL;
    }
    else {
        cabeza = actual->sig;
        actual->sig = NULL;
        return actual;
    }
}

void push(Nodo *nuevo, Nodo *&cabeza) {
    if (cabeza == NULL) {
        cabeza = nuevo;
        nuevo->sig = NULL;
    }
    else {
        nuevo->sig = cabeza;
        cabeza = nuevo;
    }
}

void mover_nodos(Nodo *&cabezaA, Nodo *&cabezaB) {

    if (cabezaA == NULL || cabezaB == NULL) {
        return;
    }

    Nodo *recorrido = cabezaB;
    Nodo *cabeza_aux = NULL;

    // Busqueda de vecinos 
    while (recorrido != NULL) {
        Nodo *siguiente = recorrido->sig;
        if (recorrido->dato % 2 == 0) {
            if (recorrido->anterior == NULL) {
                // estoy en cabeza
                if (recorrido->sig != NULL) {
                    recorrido->sig->anterior = NULL;
                    cabezaB = recorrido->sig;
                    recorrido->sig = NULL; }
                else {
                    cabezaB = NULL;
                    recorrido->sig = NULL;
                }
            }

            else if (recorrido->sig == NULL) {
                // estoy en final
                recorrido->anterior->sig = NULL;
                recorrido->sig = NULL;
                recorrido->anterior = NULL;
            }

            else {
                // estoy en medio
                recorrido->anterior->sig = recorrido->sig;
                recorrido->sig->anterior = recorrido->anterior;
                recorrido->anterior = NULL;
                recorrido->sig = NULL;
            }

            // integracion a aux

            if (cabeza_aux == NULL) {
                cabeza_aux = recorrido;
            }

            else {
                recorrido->sig = cabeza_aux;
                cabeza_aux = recorrido;
                // dejo anteriores en NULL ya que comienzo a tratarlos como lista simplemente enlazada
            }
            
        }

        else {
            //no se hace nada
        }

        recorrido = siguiente;
    }

    //Ahora tengo que buscar la referencia al ultimo nodo de A

    Nodo *ultimo = cabezaA;
    while (ultimo->sig != NULL) {
        ultimo = ultimo->sig;
    }

    // integramos a A

    while (cabeza_aux != NULL) {

        Nodo *reintegrar = pop(cabeza_aux);

        if (reintegrar == NULL) {
            break;
        }

        if (ultimo->sig == NULL) {
            // primera insercion
            ultimo->sig = reintegrar;
            reintegrar->sig = NULL;
        }

        else {
            reintegrar->sig = ultimo->sig;
            ultimo->sig = reintegrar;
        }
    }
}