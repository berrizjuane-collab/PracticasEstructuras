#include <iostream>
using namespace std;

struct Nodo;

struct arista {
    bool evaluado = false;
    int peso;
    Nodo  *extremo_izq          = nullptr;
    Nodo  *extremo_der          = nullptr;
    arista *arista_siguiente_lista  = nullptr;
    arista *arista_siguiente_arbol  = nullptr;
};

struct Nodo {
    int    valor;
    bool   visitado        = false;
    Nodo   *nodo_siguiente = nullptr;
    Nodo   *siguiente_en_ruta = nullptr;
    Nodo   *representante  = nullptr;
};

arista *lista_aristas = nullptr;
Nodo   *lista_nodos   = nullptr;
arista *Arbol         = nullptr;

void insertar_arista_ordenada(arista *nueva_arista) {
    // Caso 1: lista vacía
    if (lista_aristas == nullptr) {
        lista_aristas = nueva_arista;
        return;
    }
    // Caso 2: insertar al frente (peso mínimo)
    if (nueva_arista->peso <= lista_aristas->peso) {
        nueva_arista->arista_siguiente_lista = lista_aristas;
        lista_aristas = nueva_arista;
        return;
    }
    // Caso 3: buscar posición intermedia o al final (una sola pasada)
    arista *anterior = lista_aristas;
    while (anterior->arista_siguiente_lista != nullptr &&
           anterior->arista_siguiente_lista->peso < nueva_arista->peso) {
        anterior = anterior->arista_siguiente_lista;
    }
    nueva_arista->arista_siguiente_lista = anterior->arista_siguiente_lista;
    anterior->arista_siguiente_lista = nueva_arista;
}

void insertar_nodo(Nodo *insertar) {
    insertar->representante = insertar;
    insertar->nodo_siguiente = lista_nodos;
    lista_nodos = insertar;
}

void insertar_en_arbol(arista *insertar) {
    insertar->arista_siguiente_arbol = Arbol;
    Arbol = insertar;
}

void crear_arista(Nodo *A, Nodo *B, int peso) {
    arista *nueva    = new arista;
    nueva->extremo_der = A;
    nueva->extremo_izq = B;
    nueva->peso        = peso;
    insertar_arista_ordenada(nueva);
}

bool todas_aristas_evaluadas() {
    arista *r = lista_aristas;
    while (r != nullptr) {
        if (!r->evaluado) return false;
        r = r->arista_siguiente_lista;
    }
    return true;
}

Nodo *encontrar_representante(Nodo *buscar) {
    if (buscar->representante == buscar) return buscar;
    return encontrar_representante(buscar->representante);
}

void unir(Nodo *A, Nodo *B) {
    encontrar_representante(A)->representante = encontrar_representante(B);
}

bool mismo_grupo(Nodo *A, Nodo *B) {
    return encontrar_representante(A) == encontrar_representante(B);
}

arista *busqueda_de_minimo() {
    arista *r = lista_aristas;
    while (r) {
        if (!r->evaluado) return r;
        r = r->arista_siguiente_lista;
    }
    return nullptr;
}

void print_aristas_ordenadas() {
    cout << "\nAristas del grafo (ordenadas por peso):\n";
    arista *r = lista_aristas;
    while (r) {
        cout << "  " << r->extremo_izq->valor
             << " -- " << r->extremo_der->valor
             << "  peso: " << r->peso << "\n";
        r = r->arista_siguiente_lista;
    }
}

void print_arbol() {
    cout << "\n=== Arbol de Expansion Minima (Kruskal) ===\n";
    arista *r = Arbol;
    int total = 0;
    while (r) {
        cout << "  " << r->extremo_izq->valor
             << " -- " << r->extremo_der->valor
             << "  peso: " << r->peso << "\n";
        total += r->peso;
        r = r->arista_siguiente_arbol;
    }
    cout << "Peso total del MST: " << total << "\n";
}

void Kruskal() {
    while (!todas_aristas_evaluadas()) {
        arista *actual = busqueda_de_minimo();
        if (actual == nullptr) return;

        if (!mismo_grupo(actual->extremo_der, actual->extremo_izq)) {
            unir(actual->extremo_der, actual->extremo_izq);
            insertar_en_arbol(actual);
        }
        actual->evaluado = true;
    }
    print_arbol();
}

// ─────────────────────────────────────────────────────
//  Grafo de prueba:
//
//        4
//   A ────── B
//   |      / | \
//  2|    1/  |5  \6
//   |  /    |     \
//   C        D ─── E
//   |        |   2
//   └────────┘
//        8
//
//  Nodos: A=1, B=2, C=3, D=4, E=5
//  MST esperado: B-C(1), A-C(2), D-E(2), B-D(5)  → total=10
// ─────────────────────────────────────────────────────
int main() {
    Nodo *A = new Nodo; A->valor = 1;
    Nodo *B = new Nodo; B->valor = 2;
    Nodo *C = new Nodo; C->valor = 3;
    Nodo *D = new Nodo; D->valor = 4;
    Nodo *E = new Nodo; E->valor = 5;

    insertar_nodo(A);
    insertar_nodo(B);
    insertar_nodo(C);
    insertar_nodo(D);
    insertar_nodo(E);

    crear_arista(B, C, 1);   // B-C : 1
    crear_arista(A, C, 2);   // A-C : 2
    crear_arista(D, E, 2);   // D-E : 2
    crear_arista(A, B, 4);   // A-B : 4
    crear_arista(B, D, 5);   // B-D : 5
    crear_arista(B, E, 6);   // B-E : 6
    crear_arista(C, D, 8);   // C-D : 8

    print_aristas_ordenadas();
    Kruskal();

    return 0;
}