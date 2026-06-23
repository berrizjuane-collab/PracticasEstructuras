#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Vertice;

struct Arista {
    Vertice *A;
    Vertice *B;
    int peso;
    Arista *siguiente_en_lista;
    Arista *siguiente_en_arbol;
};
                                                                                  
struct Vertice {
    int dato;
    Vertice *siguiente_lista = NULL;
    Vertice *representante = NULL;
};

Vertice *lista_vertices = NULL;
Arista *lista_aristas = NULL;
Arista *Arbol = NULL;

void insertar_arbol(Arista *insertar) {
    insertar->siguiente_en_arbol = Arbol;
    Arbol = insertar;
}

void insertar_aristas_ordenado(Arista *insertar) {
    // Caso 1: lista vacia o el nuevo es el menor de todos
    if (lista_aristas == NULL || insertar->peso < lista_aristas->peso) {
        insertar->siguiente_en_lista = lista_aristas;
        lista_aristas =  insertar;
        return;
    }
    // Caso 2: buscar posicion correcta en el medio o al final
    Arista *recorrido = lista_aristas;
    while (recorrido->siguiente_en_lista && recorrido->siguiente_en_lista->peso < insertar->peso) {
        recorrido = recorrido->siguiente_en_lista;
    }
    insertar->siguiente_en_lista = recorrido->siguiente_en_lista;
    recorrido->siguiente_en_lista = insertar;
}

void insertar_vertice(Vertice *insertar) {
    insertar->representante = insertar;
    insertar->siguiente_lista = lista_vertices;
    lista_vertices = insertar;
}

void crear_arista(Vertice *A, Vertice *B, int peso) {
    Arista *nueva = new Arista();
    nueva->peso = peso;
    nueva->A = A;
    nueva->B = B;
    insertar_aristas_ordenado(nueva);
}

Vertice *encontrar_representante(Vertice *A) {
    if (A->representante == A) return A;
    return encontrar_representante(A->representante);
}

bool mismo_grupo(Vertice *A, Vertice *B) {
    return encontrar_representante(A) == encontrar_representante(B);
}

void unir(Vertice *A, Vertice *B) {
    encontrar_representante(A)->representante = encontrar_representante(B);
}

void print_aristas_por_peso() {
    Arista *r = lista_aristas;
    cout << "Grafo ordenado por pesos de arista" << endl;
    while (r) {
        cout << "Extremo izquierdo: " << r->A->dato << " " << "extremo derecho: " << r->B->dato << endl;
        cout << "Peso: " << r->peso << endl;
        r = r->siguiente_en_lista;
    }
}

void print_arbol_expansion() {
    cout << "Arbol de expansion Kruskal: " << endl;
    Arista *r = Arbol;
    int total = 0;
    while (r) {
        cout << "  " << r->A->dato
         << " -- " << r->B->dato
         << "  peso: " << r->peso << "\n";
        total += r->peso;
        r = r->siguiente_en_arbol;
    }
    cout << "Peso total de ruta: " << total << endl;
}

void Kruskal() {
    Arista *actual = lista_aristas;
    if (actual == NULL) return;

    while (actual) {
        if (!mismo_grupo(actual->A, actual->B)) {
            unir(actual->A, actual->B);
            insertar_arbol(actual);
        }
        actual = actual->siguiente_en_lista;
    }
    print_arbol_expansion();
}
