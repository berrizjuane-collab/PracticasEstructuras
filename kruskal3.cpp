//tercer modelo de kruskal
//igual a los anteriores
//unicamente para refrescarlo

#include <iostream>
using namespace std;

struct vertice;

struct arista {
    vertice *llegada = NULL;
    vertice *salida = NULL;
    arista *sig_lista_aristas;
    arista *sig_MST;
    int peso;
};

struct vertice {
    int dato;
    vertice *sig_lista_vertices = NULL;
    vertice *representante = NULL;
};

vertice *lista_vertices = NULL;
arista *lista_aristas = NULL;
arista *Arbol_MST = NULL;

void insertar_arista_ordenada(arista *insertar) {
    if (!lista_aristas || insertar->peso < lista_aristas->peso) {
        insertar->sig_lista_aristas = Arbol_MST;
        Arbol_MST = insertar;
        return;
    }
    arista *recorrido = Arbol_MST;
    while (recorrido->sig_lista_aristas && recorrido->sig_lista_aristas->peso < insertar->peso) {
        recorrido = recorrido->sig_lista_aristas;
    }

    insertar->sig_lista_aristas = recorrido->sig_lista_aristas;
    recorrido->sig_lista_aristas = insertar;
}

void insertar_vertice(vertice *insertar) {
    insertar->representante = insertar;
    insertar->sig_lista_vertices = lista_vertices;
    lista_vertices = insertar;
}

void insertar_MST(arista *insertar) {
    insertar->sig_MST = Arbol_MST;
    Arbol_MST = insertar;
}

//Union-Find

vertice *encontrar_representante(vertice *A) {
    if (A->representante == A) return A;
    return encontrar_representante(A->representante);
}

bool mismo_grupo(vertice *A, vertice *B) {
    return encontrar_representante(A) == encontrar_representante(B);
}

void unir_grupo(vertice *A, vertice *B) {
    encontrar_representante(A)->representante = encontrar_representante(B);
}

//

void imprimir_MST() {
    arista *recorrido = Arbol_MST;
    int total = 0;
    while (recorrido) {
        cout << recorrido->salida->dato << " -> " << recorrido->llegada->dato << "; Peso: " << recorrido->peso << endl;
        total = total + recorrido->peso;
        recorrido = recorrido->sig_MST;
    }
    cout << "Peso MST final: " << total << endl;
}

void Kruskal() {
    arista *recorrido = lista_aristas;
    if (recorrido == NULL) return;

    while (recorrido) {
        if (!mismo_grupo(recorrido->salida, recorrido->llegada)) {
            unir_grupo(recorrido->salida, recorrido->llegada);
            insertar_MST(recorrido);
        }
        recorrido = recorrido->sig_lista_aristas;
    }

    imprimir_MST();
}