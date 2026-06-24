//intento de bellman-ford
#include <iostream>
using namespace std;

const int infinito = 10000;

struct vertice;

struct arista {
    vertice *llegada = NULL;
    vertice *salida = NULL;
    int peso;
    arista *sig_llegada = NULL;
    arista *sig_salida = NULL; //enfoque similar al dijkstra
};

struct vertice {
    int dato;
    int distancia_acumulada = infinito;
    arista *lista_aristas = NULL;
    vertice *sig_lista_vertices = NULL;
    vertice *predecesor = NULL;
};

vertice *lista_vertices = NULL;

void insertar_vertice(vertice *insertar) {
    insertar->sig_lista_vertices = lista_vertices;
    lista_vertices = insertar;
}

void crear_arista (vertice *A, vertice *B, int peso) { //La idea de bellman ford es que sea estrictamente dirigido
    arista *nueva = new arista();
    nueva->peso = peso;
    nueva->llegada = A;
    nueva->salida = B;

    nueva->sig_salida = B->lista_aristas;
    B->lista_aristas = nueva;
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

void imprimir_ruta(vertice *llegada) {
    if (llegada == NULL) return;

    imprimir_ruta(llegada->predecesor);
    cout << llegada->dato << "-> Distancia acumulada: " << llegada->distancia_acumulada << endl;
}

int cantidad_vertices() {
    vertice *recorrido = lista_vertices;
    int total = 0;
    while (recorrido) {
        total++;
        recorrido = recorrido->sig_lista_vertices;
    }
    return total;
}

void bellman_ford(vertice *salida) {
    salida->distancia_acumulada = 0;
    int cantidad = cantidad_vertices();
    if (cantidad == 0) return;
    for (int i = 0; i < cantidad; i++) {
        bool hubo_relajacion = false;
        vertice *recorrido = lista_vertices;
        while (recorrido) {
            if (recorrido->distancia_acumulada != infinito) {
                arista *inmediata = recorrido->lista_aristas;
                while (inmediata) {
                    vertice *vecino = buscar_vecino(recorrido, inmediata);
                    arista *siguiente = siguiente_arista(recorrido, inmediata);
                    int nueva_distancia = inmediata->peso + recorrido->distancia_acumulada;
                    if (nueva_distancia < vecino->distancia_acumulada) {
                        vecino->distancia_acumulada = nueva_distancia;
                        vecino->predecesor = recorrido;
                        hubo_relajacion = true;
                    }
                    inmediata = siguiente;
                }
            }
            recorrido = recorrido->sig_lista_vertices;
        }
        if (i == cantidad-1 && hubo_relajacion) {
            cout << "Ciclo negativo detectado. No existe solucion para el grafo" << endl;
            return;
        }
    }
    vertice *actual = lista_vertices;
    while (actual) {
        imprimir_ruta(actual);
        actual = actual->sig_lista_vertices;
    }
}