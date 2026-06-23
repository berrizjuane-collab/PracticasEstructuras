#include <iostream>
using namespace std;

struct nodo;

const int infinito = 10000;

struct arista {
    nodo *A;
    nodo *B;
    int peso;
    arista *sig_A;
    arista *sig_B;
};

struct nodo {
    int dato;
    bool evaluado;
    arista *lista_aristas;
    nodo *sig_lista;
    int distancia_acumulada = infinito;
    nodo *sig_en_ruta;
};

nodo *lista_nodos = NULL;

void insertar_en_lista(nodo *insertar) {
    insertar->sig_lista = lista_nodos;
    lista_nodos = insertar;
}

void crear_arista(nodo *A, nodo *B, int cost) {
    arista *nueva = new arista();
    nueva->A = A;
    nueva->B = B;
    nueva->peso = cost;
    
    nueva->sig_A = A->lista_aristas;
    A->lista_aristas = nueva;

    nueva->sig_B = B->lista_aristas;
    B->lista_aristas = nueva;
}

void print_ruta(nodo *llegada) {
    if (llegada == NULL) {
        return;
    }
    print_ruta(llegada->sig_en_ruta);
    cout << llegada->dato << "->";
}

nodo *busqueda_minimo() {
    nodo *recorrido = lista_nodos;
    nodo *minimo = NULL;
    while (recorrido) {
        if (!recorrido->evaluado) {
            if (minimo == NULL) {
                minimo = recorrido;
            }
            else if (recorrido->distancia_acumulada < minimo->distancia_acumulada) {
                minimo = recorrido;
            }
        }
        recorrido = recorrido->sig_lista;
    }
    return minimo;
}

void reset_dijkstra() {
    nodo *recorrido = lista_nodos;
    while (recorrido) {
        recorrido->evaluado = false;
        recorrido->distancia_acumulada = infinito;
        recorrido->sig_en_ruta = NULL;
        recorrido = recorrido->sig_lista;
    }
}

nodo *buscar_vecino(arista *recibido, nodo *actual) {
    if (recibido->A == actual) return recibido->B;
    else {
        return recibido->A;
    }
}

arista *buscar_sigarista(arista *recibido, nodo *actual) {
    if (recibido->A == actual) return recibido->sig_A;
    else {
        return recibido->sig_B;
    }
}

bool todos_visitados() {
    nodo *recorrido = lista_nodos;
    while (recorrido) {
        if (!recorrido->evaluado) return false;
        recorrido = recorrido->sig_lista;
    }
    return true;
}

void dijkstra(nodo *salida, nodo *llegada) {
    reset_dijkstra();
    salida->distancia_acumulada = 0;

    while (!todos_visitados()) {
        nodo *actual = busqueda_minimo(); //primera iteracion siempre devuelve el nodo salida
        if (actual==NULL || actual->distancia_acumulada == infinito) {
            cout << "Camino no realizable" << endl;
            return;
        }
        actual->evaluado = true;
        if (actual == llegada) break;
        arista *arista_1 = actual->lista_aristas;
        while (arista_1) {
            nodo *vecino = buscar_vecino(arista_1, actual);
            arista *siguiente_arista = buscar_sigarista(arista_1, actual);
            if (!vecino->evaluado) {
                int nueva_distancia = actual->distancia_acumulada + arista_1->peso;
                if (nueva_distancia < vecino->distancia_acumulada) {
                    vecino->distancia_acumulada = nueva_distancia;
                    vecino->sig_en_ruta = actual;
                }
            }
            arista_1 = siguiente_arista;
        }
    }

    cout << "El camino de " << salida->dato << "hasta " << llegada->dato << "es: " << endl;
    print_ruta(llegada);

    cout << "Distancia total acumulada: " << llegada->distancia_acumulada << endl;
}

int main() {
    return 0;
}