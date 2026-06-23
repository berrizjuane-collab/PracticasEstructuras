//grafos
#include <iostream>
using namespace std;

const int infinito = 10000;

struct Ciudad;

struct ady {
    Ciudad *salida;
    Ciudad *llegada;
    int distancia = infinito;
    int peaje = infinito;
    ady *sig_ciudad_llegada;
    ady *sig_ciudad_salida;
};

struct Ciudad {
    string nombre;
    int poblacion;
    string estado;
    ady *ady_1; //Cabeza de la lista de autopistas
    bool visitado = false;
    int distancia_acumulada = infinito;
    Ciudad *siguiente_en_lista;
    Ciudad *siguiente_en_ruta = NULL;
};

Ciudad *lista_de_ciudades = NULL;

void insertar_ciudad(Ciudad *A) {
    A->siguiente_en_lista = lista_de_ciudades;
    lista_de_ciudades = A;
}

void insertar_arista(Ciudad *A_llegada, Ciudad *B_salida, int distance, int costs) {
    ady *nueva_autopista = new ady;
    nueva_autopista->distancia = distance;
    nueva_autopista->peaje = costs;
    nueva_autopista->llegada = A_llegada;
    nueva_autopista->salida = B_salida;

    //enlazar las siguientes autopistas de A y B
    nueva_autopista->sig_ciudad_llegada = A_llegada->ady_1;
    A_llegada->ady_1 = nueva_autopista;

    nueva_autopista->sig_ciudad_salida = B_salida->ady_1;
    B_salida->ady_1 = nueva_autopista; 
}

void imprimir_ruta(Ciudad *llegada) {
   if (llegada->siguiente_en_ruta == NULL) {
    cout << llegada->nombre << "->";
    return;
   }
   imprimir_ruta(llegada->siguiente_en_ruta);
   cout << llegada->nombre << "->";
}

bool todos_descubiertos() {
    Ciudad *actual = lista_de_ciudades;
    while (actual != NULL) {
        if (!actual->visitado) {
            return false;
        }
        actual = actual->siguiente_en_lista;
    }
    return true;
}

Ciudad *minimo_no_visitado () {
    Ciudad *actual = lista_de_ciudades;
    Ciudad *minimo = NULL;
    while (actual != NULL) {
        if (!actual->visitado) {
            if (minimo == NULL) {
                minimo = actual;
            }
            else if (actual->distancia_acumulada < minimo->distancia_acumulada) {
                minimo = actual;
            }
        }
        actual = actual->siguiente_en_lista;
    }
    return minimo;
}

void resetteo_dijkstra() {
    Ciudad *c = lista_de_ciudades;
    while (c != NULL) {
        c->visitado = false;
        c->distancia_acumulada = infinito;
        c->siguiente_en_ruta = NULL;
        c = c->siguiente_en_lista;
    }
}

Ciudad *busqueda_de_vecino(Ciudad *actual, ady *camino) {
    if (camino->llegada == actual) {
        return camino->salida;
    }
    else {
        return camino->llegada;
    }
}

ady *autopista_siguiente(Ciudad *actual, ady *autopista_actual) {
    if (autopista_actual->llegada == actual) return autopista_actual->sig_ciudad_llegada;
    else {
        return autopista_actual->sig_ciudad_salida;
    }
}

void Dijkstra (Ciudad *salida, Ciudad *llegada) {
    resetteo_dijkstra();
    salida->distancia_acumulada = 0;

    cout << "Dijkstra desde " << salida->nombre;
    cout << " hasta " << llegada->nombre << endl;

    while (!todos_descubiertos()) {
        Ciudad *actual = minimo_no_visitado();
        if (actual == NULL || actual->distancia_acumulada == infinito) {
            cout << "No existe camino alcanzable" << endl;
            break;
        }
        actual->visitado = true;
        if (actual == llegada) break;
        ady *autopista = actual->ady_1;
        while (autopista != NULL) {
            ady *siguiente_autopista = autopista_siguiente(actual, autopista);
            Ciudad *vecino = busqueda_de_vecino(actual, autopista);
            if (!vecino->visitado) {
                int nueva_distancia = actual->distancia_acumulada + autopista->distancia;
                if (nueva_distancia < vecino->distancia_acumulada) {
                    vecino->distancia_acumulada = nueva_distancia;
                    vecino->siguiente_en_ruta = actual;
                }
            }
            autopista = siguiente_autopista;
        }
    }

    cout << "Ruta mas corta desde: " << salida->nombre << " hasta " << llegada->nombre << endl;
    imprimir_ruta(llegada);
    cout << endl;
    cout << "Con un total de: " << llegada->distancia_acumulada << "kms recorridos." << endl;
    cout << endl;
}

int main() {
    Ciudad *caracas     = new Ciudad{"Caracas",      2900000, "Distrito Capital"};
    Ciudad *maracay     = new Ciudad{"Maracay",       800000, "Aragua"};
    Ciudad *valencia    = new Ciudad{"Valencia",     1400000, "Carabobo"};
    Ciudad *bqto        = new Ciudad{"Barquisimeto",  900000, "Lara"};
    Ciudad *maracaibo   = new Ciudad{"Maracaibo",    1500000, "Zulia"};
    Ciudad *sanCristoba = new Ciudad{"San Cristobal", 650000, "Tachira"};

    insertar_ciudad(caracas);
    insertar_ciudad(maracay);
    insertar_ciudad(valencia);
    insertar_ciudad(bqto);
    insertar_ciudad(maracaibo);
    insertar_ciudad(sanCristoba);

    // Cada llamada crea UN SOLO nodo ady (no dos como antes)
    insertar_arista(caracas,  maracay,     105, 5);
    insertar_arista(caracas,  valencia,    169, 8);
    insertar_arista(maracay,  valencia,     64, 3);
    insertar_arista(valencia, bqto,        170, 7);
    insertar_arista(valencia, maracaibo,   510, 20);
    insertar_arista(bqto,     maracaibo,   235, 10);
    insertar_arista(valencia, sanCristoba, 570, 18);
    insertar_arista(bqto,     sanCristoba, 430, 15);

    Dijkstra(caracas, maracaibo);
    Dijkstra(caracas, sanCristoba);
    Dijkstra(bqto,    caracas);

    return 0;
}






