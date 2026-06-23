//Ahora con punteros puros
#include <iostream>
using namespace std;

struct Nodo {
    int dato1 = 0;
    int dato2 = 0;
    int dato_rebose = 0;
    Nodo *menores;
    Nodo *intermedio;
    Nodo *mayores;
    Nodo *ptr_rebose;
    int contador;
};

struct factor_balanceo {
    bool hubo_split = false;
    int dato_a_subir;
    Nodo *hijo_derecha;
};

Nodo *Arbol = NULL;

bool es_hoja(Nodo *nodo) {
    return (nodo->menores == NULL) && (nodo->intermedio == NULL) && (nodo->mayores == NULL) && (nodo->ptr_rebose == NULL);
}

Nodo *creacion_de_nodo() {
    Nodo *nuevo = new Nodo;
    nuevo->menores = NULL, nuevo->intermedio = NULL, nuevo->mayores = NULL, nuevo->ptr_rebose = NULL;
    nuevo->contador = 0;
    return nuevo;
}

Nodo *posicion_relativa(Nodo *estacion_actual, int dato) { //Para saber por donde bajar
    if (dato == estacion_actual->dato1 || dato == estacion_actual->dato2) {
        return estacion_actual; //Caso de coincidencia. No es conflictivo con buscar ya que al momento
        // de ser devuelta a buscar, buscar se da cuenta de la existencia del dato. (creo)
    }
    if (dato < estacion_actual->dato1) {
        return estacion_actual->menores;
    }
    else if (dato > estacion_actual->dato1 && dato < estacion_actual->dato2) {
        return estacion_actual->intermedio;
    }
    else {
        return estacion_actual->mayores;
    }
}

bool buscar(int dato_buscar, Nodo *recorrido) {
    if (es_hoja(recorrido)) {
        return false;
    }
    if (recorrido->dato1 == dato_buscar || recorrido->dato2 == dato_buscar) {
        return true;
    }
    else {
        Nodo *bajar = posicion_relativa(recorrido, dato_buscar);
        return buscar(dato_buscar, bajar);
    }
}

factor_balanceo split(Nodo *estacion) {

    factor_balanceo devolver;
    devolver.hubo_split = true;

    Nodo *estacion_nueva = creacion_de_nodo();
    estacion_nueva->dato1 = estacion->dato_rebose;
    devolver.dato_a_subir = estacion->dato2;
    devolver.hijo_derecha = estacion_nueva;
    estacion->dato_rebose = 0;
    estacion->dato2 = 0;
    estacion_nueva->menores = estacion->mayores;
    estacion_nueva->intermedio = estacion->ptr_rebose;
    estacion->mayores = NULL;
    estacion->ptr_rebose = NULL;
    estacion->contador = 1;
    estacion_nueva->contador = 1;

    return devolver;
}

void insertar_en_nodo(Nodo *estacion, int dato_insertar, Nodo *hijo_derecho) { //Maneja de una ambos casos
    if (dato_insertar > estacion->dato1 && dato_insertar > estacion->dato2) {
        estacion->dato_rebose = dato_insertar;
        estacion->ptr_rebose = hijo_derecho;
    }
    else if (dato_insertar > estacion->dato1 && dato_insertar < estacion->dato2) {
        estacion->dato_rebose = estacion->dato2;
        estacion->dato2 = dato_insertar;
        estacion->mayores = hijo_derecho;
    }
    else {
        estacion->dato_rebose = estacion->dato2;
        estacion->dato2 = estacion->dato1;
        estacion->dato1 = dato_insertar;
        estacion->intermedio = hijo_derecho;
    }
    estacion->contador++;
}

factor_balanceo insercion_recursiva(Nodo *nodo, int dato_insertar) {
    factor_balanceo resultado;

    if (es_hoja(nodo)) { // Primer case base. Es la primera insercion al fondo del Btree. Luego de completarse esta condicion salta a verificar la 
        // otra para ver si el empaquetado desbordo al nodo
        //insertamos aca
        insertar_en_nodo(nodo, dato_insertar, NULL);
    }
    else {
        Nodo *bajar = posicion_relativa(nodo, dato_insertar); // Aqui no importa si se encontro un dato igual, ya que ese caso se cubre
        // directamente en la insercion
        factor_balanceo explorador = insercion_recursiva(bajar, dato_insertar);

        if (explorador.hubo_split) { //Aqui explorador recibe la respuesta de resultado, y si hubo split en la llamada anterior, empaqueta 
            // todos los datos recibidos en el nodo de la llamada actual
            insertar_en_nodo(nodo, explorador.dato_a_subir, explorador.hijo_derecha);
        }
    } // Como no hay return, la llamada naturalmente sigue hasta las ultimas lineas, revisando desborde en cada llamada
    // De esta forma se revisa recursivamente en cada llamada si el nodo que acabamos de empaquetar se desbordo

    if (nodo->contador > 2) { //Chequeo REAL. De aqui sale la verificacion de desborde, y devuelve el hubo split a las llamadas anteriores
        resultado = split(nodo);
    }
    return resultado;
}

void insercion(int dato) {
    if (Arbol == NULL) {
        Arbol = creacion_de_nodo();
        insertar_en_nodo(Arbol, dato, NULL);
        return;
    }

    if (buscar(dato, Arbol)) {
        cout << "Dato existente" << endl;
        return;
    }

    factor_balanceo nueva_raiz = insercion_recursiva(Arbol, dato);

    if (nueva_raiz.hubo_split) {
        Nodo *raiz = creacion_de_nodo();
        insertar_en_nodo(raiz, nueva_raiz.dato_a_subir, nueva_raiz.hijo_derecha);
        raiz->menores = Arbol;
        Arbol = raiz;
    }
}