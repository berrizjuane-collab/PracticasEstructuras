#include <iostream>
using namespace std;

typedef struct {
    int placa_numerica;
    string marca_auto;
    int precio;
} vehiculo;

const int cantidad_vehiculos = 15;

typedef vehiculo *puntero_vehiculo;

typedef puntero_vehiculo array_1[cantidad_vehiculos];

typedef struct {
    array_1 registro_vehiculo;
    int contador_vehiculos = 0;
} tLista;

tLista registro;

void registrar_vehiculo () {

    if (registro.contador_vehiculos == cantidad_vehiculos) {
        cout << "Lista llena" << endl;
    }

    else {

    registro.registro_vehiculo[registro.contador_vehiculos] = new vehiculo;

    cout << "Introduzca la placa numerica: ";  
    cin >> registro.registro_vehiculo[registro.contador_vehiculos]->placa_numerica;
    cout << "Introduzca la marca del auto: ";
    cin >> registro.registro_vehiculo[registro.contador_vehiculos]->marca_auto;
    cout << "Introduzca el precio del auto: ";
    cin >> registro.registro_vehiculo[registro.contador_vehiculos]->precio;
    registro.contador_vehiculos++; }
}

void visualizar_lista () {
    for (int i=0; i < registro.contador_vehiculos; i++) {
        cout << "Vehiculo en posicion: " << i << endl;
        cout << "Placa: " << registro.registro_vehiculo[i]->placa_numerica << endl;
        cout << "Marca: " << registro.registro_vehiculo[i]->marca_auto << endl;
        cout << "Precio: " << registro.registro_vehiculo[i]->precio << endl;
    }
}

void destruir_lista() {
    for (int i = 0; i < registro.contador_vehiculos; i++) {
        delete registro.registro_vehiculo[i];
        registro.registro_vehiculo[i] = nullptr;
    }
}

void eliminar_elemento() {

    int elemento_a_eliminar;

    cout << "Introduzca la placa del elemento a eliminar: ";
    cin >> elemento_a_eliminar;

    for (int i = 0; i < registro.contador_vehiculos; i++) {
        if (registro.registro_vehiculo[i]->placa_numerica == elemento_a_eliminar) {
            delete registro.registro_vehiculo[i];
            registro.registro_vehiculo[i] = registro.registro_vehiculo[registro.contador_vehiculos - 1];
            registro.registro_vehiculo[registro.contador_vehiculos - 1] = nullptr;
            registro.contador_vehiculos--;
        }

        else {
            cout << "Elemento no encontrado" << endl;
        }
    }
}

void buscar_vehiculo () {
    int elemento_buscar;

    cout << "Introduzca la placa del vehiculo a buscar: ";
    cin >> elemento_buscar;

    bool encontrado = false;

    for (int i = 0; i < registro.contador_vehiculos; i++) {
        if (registro.registro_vehiculo[i]->placa_numerica == elemento_buscar) {
            encontrado = true;
            cout << "Vehiculo encontrado";
            cout << "Posicion: " << i << endl;
            cout << "Placa: " << registro.registro_vehiculo[i]->placa_numerica << endl;
            cout << "Marca: " << registro.registro_vehiculo[i]->marca_auto << endl;
            cout << "Precio: " << registro.registro_vehiculo[i]->precio << endl;
        }

    if (!encontrado) {
            cout << "Vehiculo no encontrado" << endl;
        }
    }
}

int main() {

    int opcion;

    cout << "Bienvenido al concesionario" << endl;

    do {
        cout << "Menu: " << endl;
        cout << "1.Registrar Vehiculo" << endl;
        cout << "2.Visualizar Lista" << endl;
        cout << "3.Eliminar Elemento" << endl;
        cout << "4.Buscar Vehiculo" << endl;
        cout << "5.Salir" << endl;
        cin >> opcion;
        switch (opcion) {
            case 1:
                registrar_vehiculo();
                break;
            case 2:
                visualizar_lista();
                break;
            case 3:
                eliminar_elemento();
                break;
            case 4:
                buscar_vehiculo();
                break;
            case 5:
                cout << "Hasta luego" << endl;
                destruir_lista();
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    } while (opcion != 5);
    return 0;
}