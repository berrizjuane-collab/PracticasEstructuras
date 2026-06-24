//BFS intento
#include <iostream>
using namespace std;

struct vertice;

struct arista {
    vertice *llegada, *salida;
    arista *sig_llegada, *sig_salida;
};

struct vertice {
    int dato;
    bool evaluado = false;
    bool alcanzado = false;
    arista *adyacentes = NULL;
    vertice *siguiente_lista = NULL;
};

vertice *lista_vertices = NULL;

void crear_arista(vertice *llegada, vertice *salida, bool nodirigido) {
    arista *nueva = new arista();
    nueva->llegada = llegada; nueva->salida = salida;
    if (nodirigido) {
        nueva->sig_llegada = llegada->adyacentes;
        llegada->adyacentes = nueva;

        nueva->sig_salida = salida->adyacentes;
        salida->adyacentes = nueva;
    }
    else {
        nueva->sig_salida = salida->adyacentes;
        salida->adyacentes = nueva;
    }   
}

vertice *buscar_vecino(vertice *A, arista *actual) {
    if (actual->llegada == A) return actual->salida;
    else {
        return actual->llegada;
    }
}

arista *siguiente_arista(vertice *A, arista *actual) {
    if (actual->llegada == A) return actual->sig_llegada;
    else {
        return actual->sig_salida;
    }
}

vertice *buscar_siguiente() {
    vertice *recorrido = lista_vertices;
    while (recorrido) {
        if (recorrido->alcanzado && !recorrido->evaluado) return recorrido;
        recorrido = recorrido->siguiente_lista;
    }
    return recorrido;
}

bool todos_evaluados() {
    vertice *recorrido = lista_vertices;
    while (recorrido) {
        if (!recorrido->evaluado) return false;
        recorrido = recorrido->siguiente_lista;
    }
    return true;
}

void BFS(vertice *raiz) {
    raiz->alcanzado = true;
    while (!todos_evaluados()) {
        vertice *actual = buscar_siguiente();
        if (actual == NULL) return;
        actual->evaluado = true;
        arista *adyacente = actual->adyacentes;
        while (adyacente) {
            vertice *vecino = buscar_vecino(actual, adyacente);
            arista *siguiente = siguiente_arista(actual, adyacente);
            vecino->alcanzado = true;
            adyacente = siguiente;
        }
    }
}