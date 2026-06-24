//Tratare de asimilarlo a un kruskal
//Mi idea es el mismo enfoque de kruskal: lista de aristas
//En base a eso tengo todo
//Voy eligiendo las aristas con el vertice de inicio (inicialmente) y en base a ellas busco
//adyacencias

#include <iostream>
using namespace std;

struct vertice;

const int infinito = 10000;

struct arista {
    vertice *llegada = NULL;
    vertice *salida = NULL;
    int peso = infinito;
    bool evaluado = false;
    arista *siguiente_en_lista = NULL;
    arista *siguiente_en_arbol = NULL;
};

struct vertice {
    //tambien debo tener una lista de vertices descubiertos
    bool descubierto = false;
    int dato;
    //a mi vertice no le importa quienes son sus aristas. De eso se encargan ellas
    vertice *siguiente_en_lista = NULL;
    //Representantes? Tampoco. No estoy haciendo una evaluacion global
};

arista *Arbol_MST = NULL;
arista *lista_aristas = NULL;
vertice *lista_vertices = NULL;

//Primitivas basicas de adicion a listas
//Aqui tampoco me interesa tener la lista ordenada de aristas ya que simplemente buscare por adyacencias

void insertar_arista(arista *insertar) {
    insertar->siguiente_en_lista = lista_aristas;
    lista_aristas = insertar;
}

void insertar_vertice(vertice *insertar) {
    insertar->siguiente_en_lista = lista_vertices;
    lista_vertices = insertar;
}

void insertar_en_arbol(arista *insertar) { //insercion en el MST
    insertar->siguiente_en_arbol = Arbol_MST;
    Arbol_MST = insertar; 
}

bool arista_es_elegible(arista *arista) {
    return (arista->llegada->descubierto || arista->salida->descubierto);
}

arista *buscar_siguiente() { //dada la lista de aristas, busco la arista de menor peso que este en la frontera visible del algoritmo
    //(ya no busco en base a un vertice, si no evaluo todas las aristas y busco la de menor peso que tenga en sus extremos algun vertice ya alcanzado)
    //no sucede el caso de elegir una con ambos vertices alcanzados y formar un bucle ya que al incio de la funcio  prim se llama a buscar_obsoletos()
    arista *recorrido = lista_aristas;
    arista *minima = NULL;
    while (recorrido) {
        if (!recorrido->evaluado) {
            if (minima == NULL && arista_es_elegible(recorrido)) {
                minima = recorrido;
            }
            else if (recorrido->peso < minima->peso && arista_es_elegible(recorrido)) {
                minima = recorrido;
            }
        }
        recorrido = recorrido->siguiente_en_lista;
    }
    return minima;
}

void buscar_obsoletos() {
    arista *recorrido = lista_aristas;
    while (recorrido) {
        if (recorrido->llegada->descubierto && recorrido->salida->descubierto && !recorrido->evaluado) {
            recorrido->evaluado = true; //Se descarta instantaneamente.
            //Aqui la pregunta es: Si mi nodo de llegada ya fue alcanzado y mi nodo de salida lo mismo, pero yo no he sido evaluado,
            //ya consiguieron mejor camino hacia mis nodos salida y llegada. Ya no sirvo
        }
        recorrido = recorrido->siguiente_en_lista;
    }
}

void imprimir_MST() {
    arista *recorrido = Arbol_MST;
    int total = 0;
    cout << "MST: " << endl;
    while (recorrido) {
        cout << recorrido->llegada << " -> " << recorrido->salida <<
        "; Peso: " << recorrido->peso;
        total = total + recorrido->peso;
    }
    cout << "Peso total del MST: " << total << endl;
}

bool todas_aristas_evaluadas() {
    arista *recorrido = lista_aristas;
    while (recorrido) {
        if (!recorrido->evaluado) {
            return false;
        }
        recorrido = recorrido->siguiente_en_lista;
    }
    return true;
}

vertice *buscar_vecino(arista *A, vertice *actual) {
    if (A->salida == actual) return A->llegada;
    else {
        return A->salida;
    }
}

vertice *buscar_descubierto(arista *A) {
    if (A->llegada->descubierto) return A->llegada;
    else {
        return A->salida;
    }
}

void Prim(vertice *salida) {
    salida->descubierto = true;
    while (!todas_aristas_evaluadas()) {
        //En teoria, adyacente deberia devolver SIEMPRE una arista con un solo descubierto en alguno de los extremos
        //ya que estoy llamando a buscar_obsoletos() al inicio de cada ciclo. Si no fuera asi, se crearian bucles infinitos
        buscar_obsoletos();
        arista *adyacente = buscar_siguiente();
        vertice *el_descubierto = buscar_descubierto(adyacente); //quien es el descubierto de la arista devuelta??
        vertice *vecino = buscar_vecino(adyacente, el_descubierto); //quien es el vecino no descubierto??
        vecino->descubierto = true;
        insertar_en_arbol(adyacente);
    }
    imprimir_MST();
}