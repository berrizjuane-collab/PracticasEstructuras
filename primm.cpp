// prim
#include <iostream>
using namespace std;

const int infinito = 10000;

struct vertice;

struct Arista {
    vertice *ext_izq;
    vertice *ext_der;
    int peso;
    Arista *siguiente_en_listaA;
    Arista *siguiente_en_listaB;
};

struct vertice {
    int dato;
    int peso_guardado = infinito;
    vertice *siguiente_en_lista = NULL;
    bool evaluado = false;
    Arista *lista_aristas = NULL;
    vertice *siguiente_ruta = NULL;
};

vertice *lista_vertices = NULL;

vertice *nuevo_vertice(int dato) {
    vertice *nuevo = new vertice();
    nuevo->dato = dato;
    nuevo->siguiente_en_lista = lista_vertices;
    lista_vertices = nuevo;
    return nuevo;
}

void crear_arista(vertice *A, vertice *B, int cost) {
    Arista *nueva = new Arista();
    nueva->ext_der = A;
    nueva->ext_izq = B;
    nueva->peso = cost;
    nueva->siguiente_en_listaA = A->lista_aristas;
    A->lista_aristas = nueva;
    nueva->siguiente_en_listaB = B->lista_aristas;
    B->lista_aristas = nueva;
}

Arista *buscar_sig_arista(vertice *A, Arista *arista) {
    if (arista->ext_der == A) return arista->siguiente_en_listaA;
    else {
        return arista->siguiente_en_listaB;
    }
}

vertice *vecino_a_evaluar(Arista *minimo, vertice *actual) {
    if (minimo->ext_der == actual) return minimo->ext_izq;
    else {
        return minimo->ext_der;
    }
}

bool todos_evaluados() {
    vertice *recorrido = lista_vertices;
    while (recorrido) {
        if (!recorrido->evaluado) {
            return false;
        }
        recorrido = recorrido->siguiente_en_lista;
    }
    return true;
}

vertice *buscar_minimo() {
    vertice *recorrido = lista_vertices;
    vertice *minimo = NULL;
    while (recorrido) {
        if (!recorrido->evaluado) {
            if (minimo == NULL) {
                minimo = recorrido;
            }
            else if (recorrido->peso_guardado < minimo->peso_guardado) {
                minimo = recorrido;
            }
        }
        recorrido = recorrido->siguiente_en_lista;
    }
    return minimo;
}

void imprimir_MST(vertice *salida) {
    cout << "MST con salida en: " << salida->dato << endl;
    int total = 0;
    vertice *recorrido = lista_vertices;
    while (recorrido) {
        if (recorrido->siguiente_ruta != NULL) {
            cout << "  " << recorrido->siguiente_ruta->dato << " -> " << recorrido->dato
                 << "   peso: " << recorrido->peso_guardado << endl;
            total += recorrido->peso_guardado;
        }
        recorrido = recorrido->siguiente_en_lista;
    }
    cout << "Total: " << total << endl;
}

void Prim(vertice *salida) {
    salida->peso_guardado = 0;
    while (!todos_evaluados()) {
        vertice *actual = buscar_minimo();
        if (actual == NULL || actual->peso_guardado == infinito) {
            break;
        }
        actual->evaluado = true;
        Arista *arista_inmediata = actual->lista_aristas;
        while (arista_inmediata) {
            Arista *siguiente = buscar_sig_arista(actual, arista_inmediata);
            vertice *vecino = vecino_a_evaluar(arista_inmediata, actual);
            if (!vecino->evaluado) {
                int nuevo_peso = arista_inmediata->peso;   
                if (nuevo_peso < vecino->peso_guardado) {
                    vecino->peso_guardado = nuevo_peso;
                    vecino->siguiente_ruta = actual;
                }
            }
            arista_inmediata = siguiente;
        }
    }
    imprimir_MST(salida);
}

int main() {
    // Grafo de ciudades venezolanas (distancias aproximadas en km).
    //   0 = Caracas        4 = Maracaibo
    //   1 = Maracay        5 = San Cristobal
    //   2 = Valencia       6 = Merida
    //   3 = Barquisimeto   7 = Barcelona
    cout << "Leyenda de ciudades:" << endl;
    cout << "  0=Caracas  1=Maracay  2=Valencia  3=Barquisimeto" << endl;
    cout << "  4=Maracaibo  5=San Cristobal  6=Merida  7=Barcelona" << endl << endl;

    vertice *caracas      = nuevo_vertice(0);
    vertice *maracay      = nuevo_vertice(1);
    vertice *valencia     = nuevo_vertice(2);
    vertice *barquisimeto = nuevo_vertice(3);
    vertice *maracaibo    = nuevo_vertice(4);
    vertice *san_cristobal= nuevo_vertice(5);
    vertice *merida       = nuevo_vertice(6);
    vertice *barcelona    = nuevo_vertice(7);

    crear_arista(caracas, maracay, 110);
    crear_arista(maracay, valencia, 50);
    crear_arista(caracas, valencia, 160);
    crear_arista(valencia, barquisimeto, 220);
    crear_arista(barquisimeto, maracaibo, 320);
    crear_arista(barquisimeto, merida, 300);
    crear_arista(merida, san_cristobal, 230);
    crear_arista(maracaibo, san_cristobal, 400);
    crear_arista(caracas, barcelona, 310);
    crear_arista(valencia, barcelona, 380);

    Prim(caracas);

    return 0;
}





