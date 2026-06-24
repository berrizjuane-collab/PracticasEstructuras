//intento de bellman-ford
#include <iostream>
#include <cstdlib>
#include <ctime>
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

//grafo generado aleatoriamente
int main() {
    srand(time(NULL));

    vertice *v1 = new vertice(); v1->dato = 1;
    vertice *v2 = new vertice(); v2->dato = 2;
    vertice *v3 = new vertice(); v3->dato = 3;
    vertice *v4 = new vertice(); v4->dato = 4;
    vertice *v5 = new vertice(); v5->dato = 5;
    vertice *v6 = new vertice(); v6->dato = 6;

    insertar_vertice(v1);
    insertar_vertice(v2);
    insertar_vertice(v3);
    insertar_vertice(v4);
    insertar_vertice(v5);
    insertar_vertice(v6);

    crear_arista(v2, v1, rand() % 21 - 5);
    crear_arista(v3, v1, rand() % 21 - 5);
    crear_arista(v4, v1, rand() % 21 - 5);
    crear_arista(v3, v2, rand() % 21 - 5);
    crear_arista(v4, v2, rand() % 21 - 5);
    crear_arista(v4, v3, rand() % 21 - 5);
    crear_arista(v5, v3, rand() % 21 - 5);
    crear_arista(v5, v4, rand() % 21 - 5);
    crear_arista(v6, v4, rand() % 21 - 5);
    crear_arista(v6, v5, rand() % 21 - 5);

    bellman_ford(v1);

    return 0;
}