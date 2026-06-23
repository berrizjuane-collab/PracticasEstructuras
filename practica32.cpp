#include <iostream>
using namespace std;

struct NodoBTree {
    int dato;
    int contador;
    int ocupantes[2 + 1]; //Slots extra para manejar reboses
    NodoBTree *hijos[3 + 1];
};

struct factor_balanceo {
    bool hubo_split = false;
    int dato_a_subir;
    NodoBTree *nuevo_hijo_derecho;
};

NodoBTree *Arbol = NULL;

NodoBTree *creacion_de_nodo() {
    NodoBTree *nueva_estacion = new NodoBTree;
    for (int i=0; i < 4; i++) {
        nueva_estacion->hijos[i] = NULL;
    }
    nueva_estacion->contador = 0;
    return nueva_estacion;
}

int indice_de_descenso(NodoBTree *nodo, int dato) {
    int i = 0;
    // Posicion relativa
    while (i < nodo->contador && nodo->ocupantes[i] < dato) {
        i++;
    }
    return i;
}

factor_balanceo split(NodoBTree *nodo) {
    factor_balanceo promocion;
    promocion.hubo_split = true;
    promocion.dato_a_subir = nodo->ocupantes[1]; //La posicion 1 es el dato del medio

    NodoBTree *nuevo_nodo = creacion_de_nodo();
    nuevo_nodo->ocupantes[0] = nodo->ocupantes[2];
    nuevo_nodo->hijos[0] = nodo->hijos[2];
    nuevo_nodo->hijos[1] = nodo->hijos[3];
    nuevo_nodo->contador = 1;

    nodo->hijos[2] = NULL;
    nodo->hijos[3] = NULL;
    nodo->ocupantes[2] = 0;

    nodo->contador= 1;
    promocion.nuevo_hijo_derecho = nuevo_nodo;
    return promocion;
}

void insertar_en_nodo(NodoBTree *nodo, int dato_insertar, NodoBTree *hijo_derecho) {//Maneja ambos casos de una

    int i = nodo->contador - 1;
    while (i>=0 && nodo->ocupantes[i] > dato_insertar) {
        nodo->ocupantes[i+1] = nodo->ocupantes[i];
        nodo->hijos[i+2] = nodo->hijos[i+1];
        i--;
    }
    
    nodo->ocupantes[i+1] = dato_insertar;
    nodo->hijos[i+2] = hijo_derecho;
    nodo->contador++;
}

bool es_hoja(NodoBTree *nodo) {
    return (nodo->hijos[0]==NULL) && (nodo->hijos[1]==NULL) && (nodo->hijos[2]==NULL) && (nodo->hijos[3]==NULL);
}

bool buscar_dato(NodoBTree *nodo, int dato_buscar) {
    if (es_hoja(nodo)) {
        int i = 0;
        while (i < nodo->contador && nodo->ocupantes[i] != dato_buscar) {
            i++;
        }
        if (i >= nodo->contador) {
            return false;
        }
        else {
            return true;
        }
    }
    //Coincidencia en nodo actual
    for (int i = 0; i < nodo->contador; i++) {
        if (nodo->ocupantes[i] == dato_buscar) {
            return true;
        }
    }
    //Busqueda relativa
    int i = 0;
    while (i < nodo->contador && nodo->ocupantes[i] < dato_buscar) {
        i++;
    }
    return buscar_dato(nodo->hijos[i], dato_buscar);
}


factor_balanceo insercion_recursiva(NodoBTree *nodo,int dato_insertar) {
    factor_balanceo resultado;
    
    if (es_hoja(nodo)) {
        insertar_en_nodo(nodo, dato_insertar, NULL); // No tiene hijos
    }
    else {
        //Se busca la hoja correcta
        int i = indice_de_descenso(nodo, dato_insertar);
        factor_balanceo resultado_abajo = insercion_recursiva(nodo->hijos[i], dato_insertar);

        //verificamos si se rompio algo
        if (resultado_abajo.hubo_split) {
            insertar_en_nodo(nodo, resultado_abajo.dato_a_subir, resultado_abajo.nuevo_hijo_derecho);
        }
    }
    // verifico si yo mismo rebose
    if (nodo->contador > 2) {
        resultado = split(nodo);
    }
    return resultado;
}

void insercion(int dato) {
    if (Arbol == NULL) { //Arbol vacio
        Arbol = creacion_de_nodo();
        Arbol->ocupantes[0] = dato;
        Arbol->contador++;
        return;
    }

    //Arbol tiene nodos
    if (buscar_dato(Arbol, dato)) {
        cout << "Dato ya existente" << endl;
        return;
    }

    factor_balanceo nuevo_piso = insercion_recursiva(Arbol, dato);

    if (nuevo_piso.hubo_split) {
        NodoBTree *nueva_raiz = creacion_de_nodo();
        nueva_raiz->ocupantes[0] = nuevo_piso.dato_a_subir;
        nueva_raiz->hijos[0] = Arbol; //Antigua raiz: Hijo izquierdo
        nueva_raiz->hijos[1] = nuevo_piso.nuevo_hijo_derecho;
        nueva_raiz->contador++;
        Arbol = nueva_raiz;
    }
}