// ============================================================
//  Dijkstra con Multilista VERDADERA - Ciudades de Venezuela
//  Cada arista (autopista) existe como UN SOLO nodo ady
//  compartido entre ambas ciudades simultáneamente.
// ============================================================

#include <iostream>
#include <string>
using namespace std;

const int INF = 10000;

struct Ciudad;

// -----------------------------------------------------------------------
//  NODO DE AUTOPISTA (arista no dirigida)
//
//  En lugar de apuntar solo al destino, ahora conoce AMBOS extremos.
//  Y en vez de un solo "sig", tiene dos:
//    sig_u → siguiente autopista en la lista de ciudad_u
//    sig_v → siguiente autopista en la lista de ciudad_v
//
//  Un mismo nodo ady vive en las listas de DOS ciudades a la vez.
// -----------------------------------------------------------------------
struct ady {
    Ciudad *ciudad_u  = nullptr;  // extremo A de la autopista
    Ciudad *ciudad_v  = nullptr;  // extremo B de la autopista
    int     distancia = INF;
    int     peaje     = INF;
    ady    *sig_u     = nullptr;  // siguiente en la lista de ciudad_u
    ady    *sig_v     = nullptr;  // siguiente en la lista de ciudad_v
};

// -----------------------------------------------------------------------
//  NODO DE CIUDAD
//  Solo necesita ady_1: la cabeza de su lista de autopistas.
//  ady_2 ya no es necesario — la multilista lo hace innecesario.
// -----------------------------------------------------------------------
struct Ciudad {
    string  nombre;
    int     poblacion;
    string  estado;
    ady    *ady_1          = nullptr;  // primera autopista de esta ciudad
    int     dist_acumulada = INF;
    bool    visitado       = false;
    Ciudad *predecesor     = nullptr;
    Ciudad *sig            = nullptr;
};

Ciudad *lista_ciudades = nullptr;

void insertar_ciudad(Ciudad *c) {
    c->sig         = lista_ciudades;
    lista_ciudades = c;
}

// =====================================================================
//  insertar_arista  — Multilista verdadera
//
//  Se crea UN SOLO nodo ady para representar la autopista a<->b.
//  Ese nodo se inserta como cabeza de la lista de 'a' (via sig_u)
//  Y al mismo tiempo como cabeza de la lista de 'b' (via sig_v).
//
//  Analogia: un contrato firmado entre dos partes.
//  El papel es uno solo, pero aparece en la carpeta de ambos.
// =====================================================================
void insertar_arista(Ciudad *a, Ciudad *b, int distancia, int peaje) {
    ady *nueva   = new ady();
    nueva->ciudad_u  = a;
    nueva->ciudad_v  = b;
    nueva->distancia = distancia;
    nueva->peaje     = peaje;

    // Insertar al frente de la lista de 'a'
    // Como a = ciudad_u, usamos sig_u para encadenar la lista de a
    nueva->sig_u = a->ady_1;
    a->ady_1     = nueva;

    // Insertar al frente de la lista de 'b'
    // Como b = ciudad_v, usamos sig_v para encadenar la lista de b
    nueva->sig_v = b->ady_1;
    b->ady_1     = nueva;

    // ¡"nueva" ahora vive en ambas listas simultaneamente!
}

// =====================================================================
//  vecino_de  y  siguiente_enlace
//
//  Cuando recorremos la lista de una ciudad "yo", cada nodo ady
//  puede tener a "yo" como ciudad_u O como ciudad_v.
//  Estas funciones resuelven el ambigüedad en O(1).
// =====================================================================
Ciudad* vecino_de(ady *enlace, Ciudad *yo) {
    return (enlace->ciudad_u == yo) ? enlace->ciudad_v
                                    : enlace->ciudad_u;
}

ady* siguiente_enlace(ady *enlace, Ciudad *yo) {
    return (enlace->ciudad_u == yo) ? enlace->sig_u
                                    : enlace->sig_v;
}

// =====================================================================
//  Funciones auxiliares de Dijkstra (igual que antes)
// =====================================================================
bool todos_descubiertos() {
    Ciudad *c = lista_ciudades;
    while (c) { if (!c->visitado) return false; c = c->sig; }
    return true;
}

Ciudad* minimo_no_visitado() {
    Ciudad *actual = lista_ciudades, *minimo = nullptr;
    while (actual) {
        if (!actual->visitado && (!minimo || actual->dist_acumulada < minimo->dist_acumulada))
            minimo = actual;
        actual = actual->sig;
    }
    return minimo;
}

void imprimir_ruta(Ciudad *n) {
    if (n->predecesor) { imprimir_ruta(n->predecesor); cout << " -> "; }
    cout << n->nombre;
}

void resetear_dijkstra() {
    Ciudad *c = lista_ciudades;
    while (c) {
        c->dist_acumulada = INF;
        c->visitado       = false;
        c->predecesor     = nullptr;
        c = c->sig;
    }
}

// =====================================================================
//  Dijkstra — solo cambia el loop de relajacion de vecinos
// =====================================================================
void Dijkstra(Ciudad *salida, Ciudad *llegada) {
    resetear_dijkstra();
    salida->dist_acumulada = 0;

    cout << "\n============================================" << endl;
    cout << " DIJKSTRA: " << salida->nombre
         << "  -->  " << llegada->nombre << endl;
    cout << "============================================" << endl;

    while (!todos_descubiertos()) {
        Ciudad *actual = minimo_no_visitado();
        if (!actual || actual->dist_acumulada == INF) {
            cout << "[!] No hay mas ciudades alcanzables." << endl;
            break;
        }
        actual->visitado = true;
        cout << "  Visitando: " << actual->nombre
             << "  (dist: " << actual->dist_acumulada << " km)" << endl;
        if (actual == llegada) break;

        // Recorrer vecinos via multilista
        // La misma ady puede tener a "actual" como u o como v:
        // vecino_de() y siguiente_enlace() lo resuelven automaticamente.
        ady *enlace = actual->ady_1;
        while (enlace) {
            Ciudad *vecino    = vecino_de(enlace, actual);
            ady    *siguiente = siguiente_enlace(enlace, actual);

            if (!vecino->visitado) {
                int nueva_dist = actual->dist_acumulada + enlace->distancia;
                if (nueva_dist < vecino->dist_acumulada) {
                    vecino->dist_acumulada = nueva_dist;
                    vecino->predecesor     = actual;
                }
            }
            enlace = siguiente;
        }
    }

    cout << "--------------------------------------------" << endl;
    if (llegada->dist_acumulada == INF)
        cout << "  No existe ruta entre estas ciudades." << endl;
    else {
        cout << "  Distancia minima : " << llegada->dist_acumulada << " km" << endl;
        cout << "  Ruta             : ";
        imprimir_ruta(llegada);
        cout << endl;
    }
    cout << "============================================\n" << endl;
}

// =====================================================================
//  MAIN
// =====================================================================
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