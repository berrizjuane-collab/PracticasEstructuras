#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo *izquierda;
    Nodo *derecha;
};

Nodo *raiz= NULL;

Nodo *buscar_lugar(Nodo *actual, Nodo *recorrido) {

    if (recorrido == NULL) {
        return NULL;
    }
    if (recorrido->dato == actual->dato) {
        return NULL;
    }
    if (recorrido->izquierda == NULL && recorrido->dato > actual->dato) {
        return recorrido;
    }
    if (recorrido->derecha == NULL && recorrido->dato < actual->dato) {
        return recorrido;
    }
    if (actual->dato < recorrido->dato) {
        return buscar_lugar(actual, recorrido->izquierda);
    }
    else {
        return buscar_lugar(actual, recorrido->derecha);
    }
}

void insertar() {

    int entero;
    cout <<"Introduzca el dato" << endl;
    cin >> entero;

    Nodo *insertar = new Nodo;
    insertar->dato = entero;

    if (raiz == NULL) {
        raiz = insertar;
        insertar->derecha = NULL;
        insertar->izquierda = NULL;
    }

    else {
        Nodo *recorrido = raiz;
        Nodo *padre = buscar_lugar(insertar, recorrido);
        if (padre == NULL) {
            cout << "No ha sido posible insertar" << endl;
            delete insertar;
            return;
        }
        if (padre->dato > insertar->dato) {
            padre->izquierda = insertar;
            insertar->derecha = NULL;
            insertar->izquierda = NULL;
        }
        else {
            padre->derecha = insertar;
            insertar->derecha = NULL;
            insertar->izquierda = NULL;
        }
    }
}

bool buscar(int dato_buscar, Nodo *recorrido) {
    if (recorrido==NULL) {
        return false;
    }
    if (recorrido->dato == dato_buscar) {
        return true;
    }
    if (recorrido->dato > dato_buscar) {
        return buscar(dato_buscar, recorrido->izquierda);
    }
    else {
        return buscar(dato_buscar, recorrido->derecha);
    }
}

void busqueda_nodo() {
    int dato_buscar;
    cout << "Introduzca el dato que quiere buscar: "<< endl;
    cin >> dato_buscar;

    Nodo *recorrido = raiz;
    bool encontrado = buscar(dato_buscar, recorrido);
    if (encontrado) {
        cout << "Dato encontrado" << endl;
    }
    else {
        cout << "Dato no encontrado" << endl;
    }
}

void print_in_order(Nodo *recorrido) {
    if (recorrido == NULL) {
        return;
    }
    else {
        print_in_order(recorrido->izquierda);
        cout << recorrido->dato << endl;
        if (recorrido->derecha != NULL) {
            print_in_order(recorrido->derecha);
            cout << recorrido->dato << endl; }
    }

}

int main() {
    int opcion;
    cout << "1.Buscar, 2. Insertar, 3.Salir" << endl;
    cin >>opcion;

    switch(opcion) {
        case 1: {
            int dato_buscar;
            cin>>dato_buscar;
            Nodo *recorrido = raiz;
            buscar(dato_buscar, recorrido);
            break; }
        case 2:
        {
            insertar();
            break;
        }
        case 3:
            break;
        default:
            break;
   } while (opcion != 3);
}
