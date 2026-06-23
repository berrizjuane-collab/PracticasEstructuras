#include <iostream>
using namespace std;

struct NodoTree {
    int dato;
    NodoTree *izq;
    NodoTree *der;
    int altura;
};

NodoTree *raiz = NULL;

NodoTree* buscar_lugar(NodoTree *nuevo, NodoTree *recorrido) {
    if (recorrido == NULL) {
        return NULL;
    }

    if (recorrido->dato == nuevo->dato) {
        return NULL;
    }

    if (nuevo->dato < recorrido->dato && recorrido->izq == NULL) {
        return recorrido;
    }

    if (nuevo->dato > recorrido->dato && recorrido->der == NULL) {
        return recorrido;
    }

    if (nuevo->dato < recorrido->dato) {
        return buscar_lugar(nuevo, recorrido->izq);
    }

    if (nuevo->dato > recorrido->dato) {
        return buscar_lugar(nuevo, recorrido->der);
    }

}

bool es_hoja(NodoTree *nodo) {
    if (nodo->der == NULL && nodo->izq == NULL) {
        return true;
    }
    else{
        return false;
    }
}

int reajustar_altura() {

}



void insertar_en_arbol() {
    cout << "Introduzca el dato a insertar" << endl;
    int dato_insertar;
    cin >> dato_insertar;

    NodoTree *recorrido = raiz;
    NodoTree *nuevo = new NodoTree();
    nuevo->dato = dato_insertar;
    NodoTree *lugar = buscar_lugar(nuevo, recorrido);

    if (raiz == NULL) {
        raiz = nuevo;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        return;
    }

    if (lugar == NULL) {
        cout << "No ha sido posible ingresar" << endl;
        delete nuevo;
        return;
    }

    if (nuevo->dato < lugar->dato) {
        lugar->izq = nuevo;
        nuevo->izq = NULL;
        nuevo->der = NULL;
    }
    else {
        lugar->der = nuevo;
        nuevo->izq = NULL;
        nuevo->der = NULL;
    }

}

bool buscar(int dato_buscar, NodoTree *recorrido) {
    bool encontrado = false;
    if (recorrido == NULL) {
        return encontrado;
    }
    if (recorrido->dato == dato_buscar) {
        encontrado = true;
        return encontrado;;
    }
    if (dato_buscar < recorrido->dato && !encontrado){
        return buscar(dato_buscar, recorrido->izq);
    }
    if (dato_buscar > recorrido->dato && !encontrado) {
        return buscar(dato_buscar, recorrido->der);
    }
}

NodoTree *buscar_referencia(int dato_buscar, NodoTree *recorrido) {
    if (recorrido == NULL) {
        return NULL;
    }
    if (recorrido->dato == dato_buscar) {
        return recorrido;
    }
    if (dato_buscar < recorrido->dato) {
        return buscar_referencia(dato_buscar, recorrido->izq);
    }
    if (dato_buscar > recorrido->dato) {
        return buscar_referencia(dato_buscar, recorrido->der);
    }
}

void busqueda_de_dato() {
    cout << "Introduzca el dato a buscar" << endl;
    int dato_buscar;
    cin >> dato_buscar;

    NodoTree *recorrido = raiz;
    bool encontrado = buscar(dato_buscar, recorrido);
    if (encontrado) {
        cout << "Dato encontrado" << endl;
    }
    else {
        cout << "No encontrado" << endl;
    }
}

void print_in_order(NodoTree *recorrido) {
    if (recorrido == NULL) {
        return;
    }
    else {
        print_in_order(recorrido->izq);
        cout << recorrido->dato << endl;
        print_in_order(recorrido->der);
    }
}

NodoTree *buscar_padre(int dato_buscar, NodoTree *recorrido) {
    if (recorrido == NULL) {
        return NULL;
    }

    if (recorrido->dato == dato_buscar) {//es raiz
        return NULL;
    }
    
    if (recorrido->der != NULL) {
        if (recorrido->der->dato == dato_buscar) {
            return recorrido;
        }
    }
    if (recorrido->izq != NULL) {
        if (recorrido->izq->dato == dato_buscar) {
            return recorrido;
        }
    }
    if (dato_buscar < recorrido->dato) {
        return buscar_padre(dato_buscar, recorrido->izq);
    }
    if (dato_buscar > recorrido->dato) {
        return buscar_padre(dato_buscar, recorrido->der);
    }
    return NULL;
}

bool tiene_un_hijo(NodoTree *nodo) {
    return (nodo->izq == NULL) != (nodo->der == NULL);
}

bool tiene_dos_hijos(NodoTree *nodo) {
    return (nodo->der != NULL) && (nodo->izq != NULL);
}

NodoTree *buscar_sucesor(NodoTree *nodo) {
    if (nodo->izq == NULL) {
        return nodo;
    }
    return buscar_sucesor(nodo->izq);
}

void eliminar_nodo() {

    cout << "Introduzca el dato a eliminar" << endl;
    int dato_eliminar;
    cin >> dato_eliminar;

    NodoTree *recorrido = raiz;
    NodoTree *nodo_eliminar = buscar_referencia(dato_eliminar, raiz);

    if (nodo_eliminar == NULL) {
        cout << "Nodo inexistente" << endl;
        return;
    }

    //caso 1: el nodo es hoja, solo lo elimino

    if (es_hoja(nodo_eliminar)) {
        NodoTree *padre = buscar_padre(dato_eliminar, recorrido);
        if (padre != NULL) {
            if (nodo_eliminar->dato < padre->dato) {
                padre->izq = NULL;
                delete nodo_eliminar;
            }
            else {
                padre->der = NULL;
                delete nodo_eliminar;
            }
        }
        else {
            raiz = NULL;
            delete nodo_eliminar;
        }
    }

    //caso 2: Nodo tiene al menos 1 hijo

    else if (tiene_un_hijo(nodo_eliminar)) {
        NodoTree *padre = buscar_padre(dato_eliminar, recorrido);
        if (padre==NULL) {
            //verifico si no existe o si es por ser raiz
            if (nodo_eliminar == raiz) {
                // es raiz, se hace reasignacion
                // hijo pasa a tomar puesto del padre
                if (nodo_eliminar->izq == NULL) {
                    raiz = nodo_eliminar->der;
                    delete nodo_eliminar;
                }
                else {
                    raiz = nodo_eliminar->izq;
                    delete nodo_eliminar;
                }
            }
            else {
                return;
            }
        }
        //No es raiz y existe, simplemente reasigno
        else {
            if (nodo_eliminar->dato < padre->dato) {
                if (nodo_eliminar->izq == NULL) {
                    padre->izq = nodo_eliminar->der;
                    delete nodo_eliminar;
                    }
                else {
                    padre->izq = nodo_eliminar->izq;
                    delete nodo_eliminar;
                    }
            }
            else {
                if (nodo_eliminar->izq == NULL) {
                    padre->der = nodo_eliminar->der;
                    delete nodo_eliminar;
                    }
                else {
                    padre->der = nodo_eliminar->izq;
                    delete nodo_eliminar;
                    }
            }
        }
    }

    // caso 3, tiene 2 hijos
    else if (tiene_dos_hijos(nodo_eliminar)) {
        //Busco es sucesor: Hijo derecho->bajo todo lo que pueda a la izquierda
        NodoTree *sucesor = buscar_sucesor(nodo_eliminar->der);
        NodoTree *padre = buscar_padre(sucesor->dato, recorrido);
        if (es_hoja(sucesor)) {
            // reasigno
            nodo_eliminar->dato = sucesor->dato;
            if (nodo_eliminar->der == sucesor) {
                nodo_eliminar->der = NULL;
            }
            else {
                padre->izq = NULL;
            }
            delete sucesor;
        }
        else if (tiene_un_hijo(sucesor)) {
            // ya sabemos que por definicion, es el derecho
            if (nodo_eliminar->der == sucesor) { //IMPORTANTISIMO contemplar este caso. El sucesor es directamente
                // el hijo derecho, por ende su hijo (derecho tambien) iria a la derecha del nodo a eliminar
                nodo_eliminar->der = sucesor->der;
                nodo_eliminar->dato = sucesor->dato;
                delete sucesor;
            }
            else {
                // descartamos el caso padre raiz (no hay sentido logico en eso)
                // descartamos padre inexistente (tampoco hay sentido logico en eso)
                padre->izq = sucesor->der;
                nodo_eliminar->dato = sucesor->dato;
                delete sucesor; 
            }
        }
        // No hay caso de que tenga dos hijos, ya que no seria sucesor (contradiccion)
    }
}

void balanceo_derecha() {
    //busco el nodo conflictivo
    
}