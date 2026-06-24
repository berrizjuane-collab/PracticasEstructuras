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

bool todos_vertices_evaluados() {
    vertice *recorrido = lista_vertices;
    while (recorrido) {
        if (!recorrido->evaluado) return false;
        recorrido = recorrido->sig_lista_vertices;
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

void Dijkstra(vertice *salida, vertice *destino) {
    salida->distancia_acumulada = 0;
    while (!todos_vertices_evaluados()) {
        vertice *actual = buscar_menor();
        if (actual == NULL || actual->distancia_acumulada == infinito) break;
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
    imprimir_ruta(destino);
}

//grafo generado aleatoriamente
int main() {
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

    arista *a1 = new arista(); a1->llegada = v1; a1->salida = v2; a1->peso = 5;
    arista *a2 = new arista(); a2->llegada = v1; a2->salida = v3; a2->peso = 3;
    arista *a3 = new arista(); a3->llegada = v2; a3->salida = v4; a3->peso = 7;
    arista *a4 = new arista(); a4->llegada = v2; a4->salida = v5; a4->peso = 2;
    arista *a5 = new arista(); a5->llegada = v3; a5->salida = v4; a5->peso = 4;
    arista *a6 = new arista(); a6->llegada = v3; a6->salida = v5; a6->peso = 6;
    arista *a7 = new arista(); a7->llegada = v4; a7->salida = v6; a7->peso = 1;
    arista *a8 = new arista(); a8->llegada = v5; a8->salida = v6; a8->peso = 3;

    insertar_arista(a1);
    insertar_arista(a2);
    insertar_arista(a3);
    insertar_arista(a4);
    insertar_arista(a5);
    insertar_arista(a6);
    insertar_arista(a7);
    insertar_arista(a8);

    Dijkstra(v1, v6);

    return 0;
}