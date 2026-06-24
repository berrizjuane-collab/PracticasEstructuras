//BFS intento
#include <iostream>
using namespace std;

struct vertice;

struct arista {
    vertice *llegada, *salida;
    arista *sig_llegada, *sig_salida;
};

struct vertice {
    int dato;
    int nivel = 0;
    bool procesado = false;
    vertice *sig_cola;
    arista *adyacentes = NULL;
    vertice *siguiente_lista = NULL;
    vertice *predecesor = NULL;
};

vertice *lista_vertices = NULL;
vertice *cola = NULL;

void insertar_vertice(vertice *insertar) {
    insertar->siguiente_lista = lista_vertices;
    lista_vertices = insertar;
}

void queue(vertice *insertar) {
    insertar->procesado = true;
    insertar->sig_cola = NULL;
    if (!cola) {
        cola = insertar;
        return;
    }
    vertice *recorrido = cola;
    while (recorrido->sig_cola) {
        recorrido = recorrido->sig_cola;
    }
    recorrido->sig_cola = insertar;
}

vertice *dequeue() {
    vertice *retornar = cola;
    cola = cola->sig_cola;
    return retornar;
}

void crear_arista(vertice *llegada, vertice *salida, bool nodirigido) {
    arista *nueva = new arista();
    nueva->llegada = llegada; nueva->salida = salida;
    if (nodirigido) {
        nueva->sig_llegada = llegada->adyacentes;
        llegada->adyacentes = nueva;

        nueva->sig_salida = salida->adyacentes;
        salida->adyacentes = nueva;
    }
    else {
        nueva->sig_salida = salida->adyacentes;
        salida->adyacentes = nueva;
    }   
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

bool cola_vacia() {
    return (cola == NULL);
}

void BFS(vertice *raiz) {
    queue(raiz);
    while (!cola_vacia()) {
        vertice *actual = dequeue();
        arista *inmediata = actual->adyacentes;
        while (inmediata) {
            vertice *vecino = buscar_vecino(actual, inmediata);
            arista *siguiente = siguiente_arista(actual, inmediata);
            if (!vecino->procesado) {
                vecino->nivel = actual->nivel + 1;
                vecino->predecesor = actual;
                queue(vecino);
            }
            inmediata = siguiente;
        }
    }
}

void imprimir_bfs() {
    vertice *recorrido = lista_vertices;
    while (recorrido) {
        cout << "Vertice " << recorrido->dato;
        if (!recorrido->procesado) {
            cout << " | no alcanzado" << endl;
        }
        else if (recorrido->predecesor == NULL) {
            cout << " | nivel: " << recorrido->nivel << " | raiz" << endl;
        }
        else {
            cout << " | nivel: " << recorrido->nivel
                 << " | predecesor: " << recorrido->predecesor->dato << endl;
        }
        recorrido = recorrido->siguiente_lista;
    }
}

//grafo de prueba
int main() {
    vertice *v1 = new vertice(); v1->dato = 1;
    vertice *v2 = new vertice(); v2->dato = 2;
    vertice *v3 = new vertice(); v3->dato = 3;
    vertice *v4 = new vertice(); v4->dato = 4;
    vertice *v5 = new vertice(); v5->dato = 5;
    vertice *v6 = new vertice(); v6->dato = 6;
    vertice *v7 = new vertice(); v7->dato = 7;

    insertar_vertice(v1);
    insertar_vertice(v2);
    insertar_vertice(v3);
    insertar_vertice(v4);
    insertar_vertice(v5);
    insertar_vertice(v6);
    insertar_vertice(v7);

    crear_arista(v1, v2, true);
    crear_arista(v1, v3, true);
    crear_arista(v2, v4, true);
    crear_arista(v3, v4, true);
    crear_arista(v3, v5, true);
    crear_arista(v4, v6, true);
    crear_arista(v5, v6, true);
    crear_arista(v6, v7, true);

    BFS(v1);
    imprimir_bfs();

    return 0;
}