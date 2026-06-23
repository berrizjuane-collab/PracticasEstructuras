#include <iostream>
using namespace std;

struct Nodo;

struct Aristas {
    Nodo *llegada;
    Nodo *salida;
    Aristas *siguiente_llegada;
    Aristas *siguiente_salida;
};

struct Nodo {
    string letra;
    string color;
    bool evaluado = false;
    Aristas *lista_adyacencias = NULL;
    Nodo *siguiente_en_lista;
    int numero_adyacencias = 0;
};

Nodo *lista_nodos = NULL;

string buscar_color_vecino(Nodo *evaluar, Aristas *arista) {
    if (arista->llegada == evaluar) return arista->salida->color;
    else {
        return arista->llegada->color;
    }
}

void insertar_en_lista(Nodo *insertar) {
    insertar->siguiente_en_lista = lista_nodos;
    lista_nodos = insertar;
}

Nodo *buscar_mas_adyacencias() {
    Nodo *recorrido = lista_nodos;
    Nodo *maximo = NULL;
    while (recorrido) {
        if (maximo->numero_adyacencias < recorrido->numero_adyacencias) {
            maximo = recorrido;
        }
        recorrido = recorrido->siguiente_en_lista;
    }
    return maximo;
}

int llenar_lista_colores(int numero_nodos) {
    int lista[numero_nodos] = 

}


