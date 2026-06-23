#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int infinito = 100000;

struct Vertice;

struct Arista {
    Vertice *A;
    Vertice *B;
    int peso;
    Arista *siguiente_arista_A;
    Arista *siguiente_arista_B;
};

struct Vertice {
    int dato;
    int distancia_acumulada = infinito;
    bool visitado = false;
    Arista *lista_aristas = NULL;
    Vertice *siguiente_lista = NULL;
    Vertice *siguiente_en_ruta = NULL;
};

Vertice *lista_vertices = NULL;

void insertar_vertice(Vertice *insertar) {
    insertar->siguiente_lista = lista_vertices;
    lista_vertices = insertar;
}

Vertice *minimo_novisitado() {
    Vertice *actual = lista_vertices;
    Vertice *minimo = NULL;
    while (actual) {
        if (!actual->visitado) {
            if (minimo == NULL) {
                minimo = actual; //Primera iteracion. Aqui minimo agarra el primer nodo de la lista y se va actualizando
                //en futuras iteraciones
            }
            else if (actual->distancia_acumulada < minimo->distancia_acumulada) {
                minimo = actual; //aqui es las siguientes iteraciones. Actual va pasando de vertice en vertice y se va comparando con el minimo actual.
                //Si el minimo actual tiene mayor distancia acumulada que el nuevo actual, se actualiza el minimo. Asi hasta llegar al final de la lista
            }
        }
        actual = actual->siguiente_lista;
    }
    return minimo;
}

bool todos_visitados() {
    Vertice *actual = lista_vertices;
    while (actual) {
        if (!actual->visitado) {
            return false;
        }
        actual = actual->siguiente_lista;
    }
    return true; //devuelve true si el return false no se devuelve primero
}

void resetteo_dijkstra() {
    Vertice *actual = lista_vertices;
    while (actual) {
        actual->distancia_acumulada = infinito;
        actual->siguiente_en_ruta = NULL;
        actual->visitado = false;
        actual = actual->siguiente_lista;
    }
}

Vertice *busqueda_vecino(Vertice *actual, Arista *arista) {
    if (arista->A == actual) {
        return arista->B;
    }
    else {
        return arista->A;
    }
}

Arista *busqueda_sig_arista(Vertice *actual, Arista *arista_actual) {
    if (arista_actual->A == actual) {
        return arista_actual->siguiente_arista_A;
    }
    else {
        return arista_actual->siguiente_arista_B;
    }
}

void print_ruta(Vertice *actual) {
    if (actual->siguiente_en_ruta == NULL) {
        cout << "->" << actual->dato << endl;
        return;
    }
    print_ruta(actual->siguiente_en_ruta);
    cout << "->" << actual->dato << endl;
}

void Dijkstra (Vertice *salida, Vertice *llegada) {
    resetteo_dijkstra();
    salida->distancia_acumulada = 0;

    while (!todos_visitados()) {
        Vertice *actual = minimo_novisitado();
        if (actual == NULL || actual->distancia_acumulada == infinito) {
            cout << "Camino no alcanzable" << endl;
            return;
        }
        actual->visitado = true;
        if (actual == llegada) break;
        Arista *arista_1 = actual->lista_aristas;
        while (arista_1) {
            Arista *siguiente_arista = busqueda_sig_arista(actual, arista_1);
            Vertice *vecino = busqueda_vecino(actual, arista_1);
            if (!vecino->visitado) {
                int nueva_distancia = actual->distancia_acumulada + arista_1->peso;
                if (nueva_distancia < vecino->distancia_acumulada) {
                    vecino->distancia_acumulada = nueva_distancia;
                    vecino->siguiente_en_ruta = actual;
                }
            }            
            arista_1 = siguiente_arista;
        }
    }

    cout << "Ruta de: " << salida->dato << " a " << llegada->dato << endl;
    print_ruta(llegada);

    cout << "Distancia total acumulada: " << llegada->distancia_acumulada << endl;
}

int main() {
    srand(time(NULL));

    // Crear vertices
    int num_vertices = 7;
    Vertice *vertices[7];
    for (int i = 0; i < num_vertices; i++) {
        vertices[i] = new Vertice;
        vertices[i]->dato = i + 1; // Datos del 1 al 7
        vertices[i]->distancia_acumulada = infinito;
        vertices[i]->visitado = false;
        vertices[i]->lista_aristas = NULL;
        vertices[i]->siguiente_lista = NULL;
        vertices[i]->siguiente_en_ruta = NULL;
        insertar_vertice(vertices[i]);
    }

    cout << "--- Generando Grafo Conexo Aleatorio ---" << endl;
    
    // Para garantizar que el grafo sea conexo, conectamos los vertices consecutivamente
    for (int i = 0; i < num_vertices - 1; i++) {
        int peso = rand() % 15 + 1;
        Arista *nueva = new Arista;
        nueva->A = vertices[i];
        nueva->B = vertices[i+1];
        nueva->peso = peso;
        nueva->siguiente_arista_A = vertices[i]->lista_aristas;
        nueva->siguiente_arista_B = vertices[i+1]->lista_aristas;
        vertices[i]->lista_aristas = nueva;
        vertices[i+1]->lista_aristas = nueva;
        cout << "Conexion base: Vertice " << vertices[i]->dato << " <-> Vertice " << vertices[i+1]->dato << " (peso: " << peso << ")" << endl;
    }

    // Anadimos aristas adicionales de forma aleatoria para tener multiples rutas posibles
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i + 2; j < num_vertices; j++) {
            if (rand() % 2 == 0) { // 50% de probabilidad
                int peso = rand() % 15 + 1;
                Arista *nueva = new Arista;
                nueva->A = vertices[i];
                nueva->B = vertices[j];
                nueva->peso = peso;
                nueva->siguiente_arista_A = vertices[i]->lista_aristas;
                nueva->siguiente_arista_B = vertices[j]->lista_aristas;
                vertices[i]->lista_aristas = nueva;
                vertices[j]->lista_aristas = nueva;
                cout << "Conexion extra: Vertice " << vertices[i]->dato << " <-> Vertice " << vertices[j]->dato << " (peso: " << peso << ")" << endl;
            }
        }
    }
    cout << "----------------------------------------\n" << endl;

    // Seleccionar origen y destino aleatorios
    Vertice *salida = vertices[rand() % num_vertices];
    Vertice *llegada = vertices[rand() % num_vertices];
    
    // Asegurarse de que no sean el mismo vertice
    while (salida == llegada) {
        llegada = vertices[rand() % num_vertices];
    }

    Dijkstra(salida, llegada);

    return 0;
}