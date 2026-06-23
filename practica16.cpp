#include <iostream>
using namespace std;

struct vehiculo {
  int placa;
  string marca;
  int modelo;
  double precio;
  vehiculo *siguienteptr;
};

vehiculo *lista_vehiculos = nullptr;

bool esta_vacia() {
  if (lista_vehiculos == nullptr) {
    return true; // Lista esta vacia
  }

  else {
    return false;
  }
}

void insertar_nodo() {

  // tipo de orden: Insercion  al inicio

  if (esta_vacia()) {
    cout << "Lista vacia. Insertando primer vehiculo..." << endl;
    vehiculo *nuevo_nodo = new vehiculo;
    lista_vehiculos = nuevo_nodo;
    nuevo_nodo->siguienteptr = nullptr;

    cout << "Introduzca los siguientes datos del vehiculo: " << endl;

    cout << "Placa: ";
    cin >> nuevo_nodo->placa;
    cout << "Marca: ";
    cin >> nuevo_nodo->marca;
    cout << "Modelo: ";
    cin >> nuevo_nodo->modelo;
    cout << "Precio: ";
    cin >> nuevo_nodo->precio;

    cout << "Datos ingresados correctamente" << endl;
  }

  else {
    cout << "Lista no vacia. Insertando vehiculo al inicio..." << endl;
    vehiculo *nuevo_nodo = new vehiculo;
    nuevo_nodo->siguienteptr = lista_vehiculos;
    lista_vehiculos = nuevo_nodo;

    cout << "Introduzca los siguientes datos: " << endl;

    cout << "Placa: ";
    cin >> nuevo_nodo->placa;
    cout << "Marca: ";
    cin >> nuevo_nodo->marca;
    cout << "Modelo: ";
    cin >> nuevo_nodo->modelo;
    cout << "Precio: ";
    cin >> nuevo_nodo->precio;

    cout << "Datos ingresados correctamente" << endl;
  }
}

void mostrar_autos() {

  if (esta_vacia()) {
    cout << "No hay autos en el concesionario" << endl;
  }

  else {

    cout << "Los autos en el concesionario son: " << endl;

    vehiculo *actual = lista_vehiculos;

    while (actual != nullptr) {
      cout << "Placa: " << actual->placa << endl;
      cout << "Marca: " << actual->marca << endl;
      cout << "Modelo: " << actual->modelo << endl;
      cout << "Precio: " << actual->precio << endl;
      actual = actual->siguienteptr;
    }
  }
}

void actualizar_auto() {

  if (esta_vacia()) {
    cout << "Lista vacia. No hay nada que hacer." << endl;
  }

  else {

    int placa_actualizar;

    int opcion;

    int nueva_placa;
    string nueva_marca;
    int nuevo_modelo;
    int nuevo_precio;

    cout << "Introduzca la placa del auto a modificar/actualizar: ";
    cin >> placa_actualizar;

    // Hay que hacer un recorrido, pero ahora en base a la placa

    vehiculo *actual = lista_vehiculos;

    while (actual != nullptr && actual->placa != placa_actualizar) {
      actual = actual->siguienteptr;
    }

    if (actual == nullptr) {
      cout << "Carro no encontrado" << endl;
    }

    else {

      cout << "Decida el dato a modificar: " << endl;
      cout << "1.Placa" << endl;
      cout << "2.Marca" << endl;
      cout << "3.Modelo" << endl;
      cout << "4.Precio" << endl;
      cin >> opcion;

      switch (opcion) {
      case 1: {
        cout << "Introduzca la nueva placa: ";
        cin >> nueva_placa;
        actual->placa = nueva_placa;
        break;
      }
      case 2: {
        cout << "Introduzca la nueva marca: ";
        cin >> nueva_marca;
        actual->marca = nueva_marca;
        break;
      }
      case 3: {
        cout << "Introduzca el nuevo modelo: ";
        cin >> nuevo_modelo;
        actual->modelo = nuevo_modelo;
        break;
      }
      case 4: {
        cout << "Introduzca el nuevo precio: ";
        cin >> nuevo_precio;
        actual->precio = nuevo_precio;
        break;
      }
      default:
        cout << "Opcion invalida" << endl;
      }
    }
  }
}

void eliminar_auto() {

  if (esta_vacia()) {
    cout << "Lista vacia. No hay nada que hacer." << endl;
  }

  else {

    int placa_eliminar;

    vehiculo *actual = lista_vehiculos;
    vehiculo *anterior = nullptr;

    cout << "Introduzca la placa del vehiculo a eliminar: ";
    cin >> placa_eliminar;

    // Recorrido nuevamente de la lista

    while (actual != nullptr && actual->placa != placa_eliminar) {
      anterior = actual;
      actual = actual->siguienteptr;
    }

    // cuando se encuentre el elemento o se llegue al fin de la lista

    if (actual == nullptr) {
      cout << "Vehiculo no encontrado. No se puede eliminar" << endl;
    }

    else {
      cout << "Eliminando el vehiculo de placa: " << actual->placa << endl;
      anterior->siguienteptr =
          actual
              ->siguienteptr; // importantisimo esto. Se enganchan los punteros
                              // directamente, no el nodo con el puntero
      delete actual;

      cout << "Vehiculo eliminado correctamente." << endl;
    }
  }
}

void limpiar_concesionario() {

  if (esta_vacia()) {
    cout << "Lista vacia, no hay nada que hacer." << endl;
  }

  else {

    vehiculo *actual = lista_vehiculos;

    while (actual != nullptr) {
      lista_vehiculos = actual->siguienteptr;
      delete actual;
      actual =
          lista_vehiculos; // como este es un ciclo iterativo hasta el final de
                           // la lista, se tiene que OBLIGATORIAMENTE rasignar
                           // actual al dato que habiamos salvado
      // lista_vehiculos
    }

    cout << "Lista eliminada." << endl;
  }
}

void mostrar_menu() {

  cout << "Menu: " << endl;
  cout << "1.Insertar vehiculo" << endl;
  cout << "2.Mostrar vehiculos" << endl;
  cout << "3.Actualizar vehiculos" << endl;
  cout << "4.Eliminar vehiculo" << endl;
  cout << "5.Salir" << endl;
  cout << "Introduzca una directiva: ";
}

int main() {

  cout << "Bienvenido al concesionario!" << endl;

  int opcion;

  do {

    mostrar_menu();
    cin >> opcion;

    switch (opcion) {

    case 1:
      insertar_nodo();
      break;

    case 2:
      mostrar_autos();
      break;

    case 3:
      actualizar_auto();
      break;

    case 4:
      eliminar_auto();
      break;

    case 5:
      limpiar_concesionario();
      break;

    default:
      cout << "Opcion invalida" << endl;
    }
  } while (opcion != 5);

  return 0;
}
