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
        cout << recorrido->llegada->dato << " -> " << recorrido->salida->dato <<
        "; Peso: " << recorrido->peso << endl;
        total = total + recorrido->peso;
        recorrido = recorrido->siguiente_en_arbol;
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
        buscar_obsoletos();
        arista *adyacente = buscar_siguiente();
        if (adyacente == NULL) break;
        vertice *el_descubierto = buscar_descubierto(adyacente);
        vertice *vecino = buscar_vecino(adyacente, el_descubierto);
        vecino->descubierto = true;
        insertar_en_arbol(adyacente);
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
    vertice *v7 = new vertice(); v7->dato = 7;

    insertar_vertice(v1);
    insertar_vertice(v2);
    insertar_vertice(v3);
    insertar_vertice(v4);
    insertar_vertice(v5);
    insertar_vertice(v6);
    insertar_vertice(v7);

    arista *a1 = new arista(); a1->salida = v1; a1->llegada = v2; a1->peso = rand() % 20 + 1;
    arista *a2 = new arista(); a2->salida = v2; a2->llegada = v3; a2->peso = rand() % 20 + 1;
    arista *a3 = new arista(); a3->salida = v1; a3->llegada = v3; a3->peso = rand() % 20 + 1;
    arista *a4 = new arista(); a4->salida = v2; a4->llegada = v4; a4->peso = rand() % 20 + 1;
    arista *a5 = new arista(); a5->salida = v3; a5->llegada = v5; a5->peso = rand() % 20 + 1;
    arista *a6 = new arista(); a6->salida = v4; a6->llegada = v6; a6->peso = rand() % 20 + 1;
    arista *a7 = new arista(); a7->salida = v5; a7->llegada = v7; a7->peso = rand() % 20 + 1;
    arista *a8 = new arista(); a8->salida = v3; a8->llegada = v4; a8->peso = rand() % 20 + 1;
    arista *a9 = new arista(); a9->salida = v4; a9->llegada = v5; a9->peso = rand() % 20 + 1;
    arista *a10 = new arista(); a10->salida = v6; a10->llegada = v7; a10->peso = rand() % 20 + 1;

    insertar_arista(a1);
    insertar_arista(a2);
    insertar_arista(a3);
    insertar_arista(a4);
    insertar_arista(a5);
    insertar_arista(a6);
    insertar_arista(a7);
    insertar_arista(a8);
    insertar_arista(a9);
    insertar_arista(a10);

    Prim(v1);

    return 0;
}