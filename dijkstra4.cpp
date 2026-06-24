//otro enfoque de dijkstra
//tratare de hacerlo sin multilistas
#include <iostream>
using namespace std;

const int infinito = 10000;

struct vertice;

struct arista {
    int peso;
    bool evaluada = false;
    vertice *salida = NULL;
    vertice *llegada = NULL;
    arista *sig_lista_aristas = NULL;
};

struct vertice {
    int dato;
    bool evaluado = false;
    vertice *sig_lista_vertices = NULL;
    vertice *predecesor = NULL; 
    int distancia_acumulada = infinito;
};

vertice *lista_vertices = NULL;
arista *lista_aristas = NULL;

void insertar_arista(arista *insertar) {
    insertar->sig_lista_aristas = lista_aristas;
    lista_aristas = insertar;
}

void insertar_vertice(vertice *insertar) {
    insertar->sig_lista_vertices = lista_vertices;
    lista_vertices = insertar;
};

vertice *buscar_vecino(arista *A, vertice *actual) {
    if (A->llegada == actual) return A->salida;
    else {
        return A->llegada;
    }
}

arista *siguiente_arista(vertice *A) {
    arista *recorrido = lista_aristas;
    while (recorrido) {
        if (!recorrido->evaluada) {
            if (recorrido->llegada == A || recorrido->salida == A) {
                recorrido->evaluada = true;
                return recorrido;
            }
        }
        recorrido = recorrido->sig_lista_aristas;
    }
    return recorrido;
}

void imprimir_ruta(vertice *llegada) {
    if (llegada == NULL) return;

    imprimir_ruta(llegada->predecesor);
    cout << llegada->dato << " -> Distancia acumulada: " << llegada->distancia_acumulada << endl;
}

bool todos_evaluados() {
    arista *recorrido = lista_aristas;
    while (recorrido) {
        if (!recorrido->evaluada) return false;
        recorrido = recorrido->sig_lista_aristas;
    }
    return true;
}

vertice *buscar_menor() {
    vertice *recorrido = lista_vertices;
    vertice *menor = NULL;
    while (recorrido) {
        if (!recorrido->evaluado) {
            if (menor == NULL) {
                menor = recorrido;
            }
            else if (menor->distancia_acumulada > recorrido->distancia_acumulada) {
                menor = recorrido;
            }
        }
        recorrido = recorrido->sig_lista_vertices;
    }
    return menor;
}

void Dijkstra(vertice *salida, vertice *ruta) {
    salida->distancia_acumulada = 0;
    while (!todos_evaluados()) {
        vertice *actual = buscar_menor();
        if (actual == NULL || actual->distancia_acumulada == infinito) return;
        actual->evaluado = true;
        arista *inmediata = siguiente_arista(actual);
        while (inmediata) {
            vertice *vecino = buscar_vecino(inmediata, actual);
            arista *siguiente = siguiente_arista(actual);
            int nueva_distancia = actual->distancia_acumulada + inmediata->peso;
            if (nueva_distancia < vecino->distancia_acumulada) {
                vecino->distancia_acumulada = nueva_distancia;
                vecino->predecesor = actual;
            }
            inmediata = siguiente;
        }
    }
    imprimir_ruta(ruta);
}