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
    insertar->siguiente_en_lista = Arbol_MST;
    Arbol_MST = insertar; 
}

bool arista_es_adyacente(arista *arista , vertice *A) {
    return (arista->llegada == A || arista->salida == A);
}

arista *buscar_siguiente(vertice *A) { //dada la lista de aristas y un vertice A de inicio, yo debo buscar la siguiente arista con adyacencia a 
    //ese vertice A con menor peso (si tengo varias candidatas, elijo la menor)
    arista *recorrido = lista_aristas;
    arista *minima = NULL;
    while (recorrido) {
        if (!recorrido->evaluado) {
            if (minima == NULL && arista_es_adyacente(recorrido, A)) {
                minima = recorrido;
            }
            else if (recorrido->peso < minima->peso && arista_es_adyacente(recorrido, A)) {
                minima = recorrido;
            }
        }
        recorrido = recorrido->siguiente_en_lista;
    }
    return minima;
}

vertice *elegir_vertice() { //todos los vertices estaran en un inicio como no evaluados. Este helper elegira solo los evaluados
    //(que al inicio del algoritmo es el salida). Ya luego, en la funcion principal del prim, cuando se elija una arista, se marcara su otro
    //adyacente como evaluado en caso de no estarlo
    //Pero aqui surge la duda, y un error que tuve anteriormente. Luego de hacer la primera busqueda, no puedo ya sepultar a dicho vertice como evaluado
    //porque sus aristas pueden seguir siendo mejores candidatas que las aristas de otros vertices no evaluados
    //Mentira. No estoy sepultando a nadie. El bool alcanzado no los sepulta, los vuelve elegibles.

}