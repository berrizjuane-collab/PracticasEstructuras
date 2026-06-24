//tercer modelo de kruskal
//igual a los anteriores
//unicamente para refrescarlo

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct vertice;

struct arista {
    vertice *llegada = NULL;
    vertice *salida = NULL;
    arista *sig_lista_aristas = NULL;
    arista *sig_MST = NULL;
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
        insertar->sig_lista_aristas = lista_aristas;
        lista_aristas = insertar;
        return;
    }
    arista *recorrido = lista_aristas;
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

void crear_arista(vertice *A, vertice *B, int peso) {
    arista *nueva = new arista();
    nueva->salida = A;
    nueva->llegada = B;
    nueva->peso = peso;
    insertar_arista_ordenada(nueva);
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

    crear_arista(v1, v2, rand() % 20 + 1);
    crear_arista(v1, v3, rand() % 20 + 1);
    crear_arista(v2, v3, rand() % 20 + 1);
    crear_arista(v2, v4, rand() % 20 + 1);
    crear_arista(v3, v4, rand() % 20 + 1);
    crear_arista(v3, v5, rand() % 20 + 1);
    crear_arista(v4, v5, rand() % 20 + 1);
    crear_arista(v4, v6, rand() % 20 + 1);
    crear_arista(v5, v6, rand() % 20 + 1);

    Kruskal();

    return 0;
}