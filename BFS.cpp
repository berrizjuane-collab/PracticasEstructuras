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
    int nivel = 0;
    bool procesado = false;
    vertice *sig_cola;
    arista *adyacentes = NULL;
    vertice *siguiente_lista = NULL;
    vertice *predecesor = NULL;
};

vertice *lista_vertices = NULL;
vertice *cola = NULL;

void queue(vertice *insertar) {
    insertar->procesado = true;
    vertice *recorrido = cola;
    if (!cola) {
        insertar->sig_cola = cola;
        cola = insertar;
    }
    while (recorrido->sig_cola) {
        recorrido = recorrido->sig_cola;
    }
    insertar->sig_cola = recorrido->sig_cola; //con respecto a insertar->sig_cola = NULL, esta linea ya lo hace (recorrido->sig_cola es NULL)
    recorrido->sig_cola = insertar;
}

vertice *dequeue() {
    vertice *retornar = cola;
    cola = cola->sig_cola;
    return retornar;
}

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

bool cola_vacia() {
    return (cola == NULL);
}

void BFS(vertice *raiz) {
    queue(raiz);
    while (!cola_vacia()) {
        vertice *actual = dequeue();
        arista *inmediata = actual->adyacentes;
        while (inmediata) {
            vertice *vecino = buscar_vecino(actual, inmediata);
            arista *siguiente = siguiente_arista(actual, inmediata);
            if (!vecino->procesado) {
                vecino->nivel = actual->nivel + 1;
                vecino->predecesor = actual;
                queue(vecino);
            }
            inmediata = siguiente;
        }
    }
}