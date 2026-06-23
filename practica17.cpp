#include <iostream>
using namespace std;

struct vehiculo {
  int placa;
  string marca;
  int modelo;
  double precio;
  vehiculo *siguienteptr;
};

struct Concesionarios {
  string nombre_concesionario;
  string direccion_concesionario;
  vehiculo *Lista_vehiculos = NULL;
  Concesionarios *Lista_concesionarios = NULL;
};

Concesionarios *Lista_general = NULL;

bool vehiculos_esta_vacia(Concesionarios *concesionario_recibido) {
  if (concesionario_recibido->Lista_vehiculos == NULL) {
    return true; // Lista esta vacia
  }

  else {
    return false;
  }
}

bool concesionarios_esta_vacia() {
  if (Lista_general == NULL) {
    return true;
  }

  else {
    return false;
  }
}

void creacion_concesionario() {

  if (!concesionarios_esta_vacia()) {
    Concesionarios *nuevo_concesionario = new Concesionarios;
    cout << "Creacion de un nuevo concesionario" << endl;

    cout << "Ingrese el nombre del concesionario: ";
    cin >> nuevo_concesionario->nombre_concesionario;
    cout << "Ingrese la direccion del concesionario: ";
    cin >> nuevo_concesionario->direccion_concesionario;

    nuevo_concesionario->Lista_concesionarios = Lista_general;
    Lista_general = nuevo_concesionario;
  }

  else {
    Concesionarios *nuevo_concesionario = new Concesionarios;
    cout << "Creacion de un nuevo concesionario" << endl;

    cout << "Ingrese el nombre del concesionario: ";
    cin >> nuevo_concesionario->nombre_concesionario;
    cout << "Ingrese la direccion del concesionario: ";
    cin >> nuevo_concesionario->direccion_concesionario;

    Lista_general = nuevo_concesionario;
    nuevo_concesionario->Lista_concesionarios = NULL;
  }
}

Concesionarios *busqueda_concesionario(string concesionario_buscar) {

  if (concesionarios_esta_vacia()) {
    cout << "Lista vacia. No hay nada que hacer." << endl;
    return NULL;
  }

  else {

    Concesionarios *busqueda = Lista_general;

    while (busqueda != NULL &&
           busqueda->nombre_concesionario != concesionario_buscar) {
      busqueda = busqueda->Lista_concesionarios;
    }

    if (busqueda != NULL) {
      return busqueda;
    }

    else {
      return NULL;
    }
  }
}

// *

void insertar_vehiculo() {

  // tipo de orden: Insercion  al inicio

  string concesionario_elegir;

  cout << "Seleccione el concesionario en donde insertar: ";
  cin >> concesionario_elegir;

  Concesionarios *concesionario_recibido =
      busqueda_concesionario(concesionario_elegir);

  if (concesionario_recibido != NULL) {
    cout << "Insercion de vehiculo..." << endl;

    if (vehiculos_esta_vacia(concesionario_recibido)) {

      vehiculo *nuevo_vehiculo = new vehiculo;

      cout << "Ningun vehiculo en concesionario." << endl;
      cout << "Insertando el primero..." << endl;

      cout << "Inserte la placa del vehiculo: ";
      cin >> nuevo_vehiculo->placa;
      cout << "Inserte la marca del vehiculo: ";
      cin >> nuevo_vehiculo->marca;
      cout << "Inserte el modelo del vehiculo: ";
      cin >> nuevo_vehiculo->modelo;
      cout << "Inserte el precio del vehiculo: ";
      cin >> nuevo_vehiculo->precio;

      concesionario_recibido->Lista_vehiculos = nuevo_vehiculo;
      nuevo_vehiculo->siguienteptr = NULL;
    }

    else {
      vehiculo *nuevo_vehiculo = new vehiculo;

      cout << "Concesionario tiene vehiculos" << endl;
      cout << "Insertando el primero..." << endl;

      cout << "Inserte la placa del vehiculo: ";
      cin >> nuevo_vehiculo->placa;
      cout << "Inserte la marca del vehiculo: ";
      cin >> nuevo_vehiculo->marca;
      cout << "Inserte el modelo del vehiculo: ";
      cin >> nuevo_vehiculo->modelo;
      cout << "Inserte el precio del vehiculo: ";
      cin >> nuevo_vehiculo->precio;

      nuevo_vehiculo->siguienteptr = concesionario_recibido->Lista_vehiculos;
      concesionario_recibido->Lista_vehiculos = nuevo_vehiculo;
    }
  }

  else {
    cout << "Concesionario no encontrado" << endl;
  }
}

void busqueda_vehiculos() {

  if (!concesionarios_esta_vacia()) {

    string concesionario_a_buscar;
    cout << "Introduzca el concesionario donde quiere buscar el vehiculo: ";
    cin >> concesionario_a_buscar;

    Concesionarios *concesionario_recibido =
        busqueda_concesionario(concesionario_a_buscar);

    if (concesionario_recibido != NULL) {

      if (!vehiculos_esta_vacia(concesionario_recibido)) {

        int placa_buscar;
        cout << "Introduzca la PLACA del vehiculo a buscar: ";
        cin >> placa_buscar;

        vehiculo *busqueda = concesionario_recibido->Lista_vehiculos;

        while (busqueda != NULL && busqueda->placa != placa_buscar) {
          busqueda = busqueda->siguienteptr;
        }

        if (busqueda != NULL) {
          cout << "Vehiculo encontrado" << endl;
          cout << "Datos del vehiculo: " << endl;
          cout << "Placa: " << busqueda->placa << endl;
          cout << "Marca: " << busqueda->marca << endl;
          cout << "Modelo: " << busqueda->modelo << endl;
          cout << "Precio: " << busqueda->precio << endl;
        }

        else {
          cout << "Vehiculo no encontrado" << endl;
        }
      }

      else {
        cout << "Lista de vehiculos vacia" << endl;
      }
    }

    else {
      cout << "Concesionario no encontrado" << endl;
    }
  }

  else {
    cout << "Lista de concesionarios vacia" << endl;
  }
}

void eliminar_vehiculos() {

  if (!concesionarios_esta_vacia()) {

    string concesionario_a_buscar;
    cout << "Introduzca el concesionario donde quiere eliminar el vehiculo: ";
    cin >> concesionario_a_buscar;

    Concesionarios *concesionario_recibido =
        busqueda_concesionario(concesionario_a_buscar);

    if (concesionario_recibido != NULL) {

      if (!vehiculos_esta_vacia(concesionario_recibido)) {
        int placa_eliminar;
        cout << "Introduzca la PLACA del vehiculo que desea eliminar: ";
        cin >> placa_eliminar;

        // Hay que tener mucho cuidado con esta logica, sobretodo si nos da por
        // eliminar el primer elemento de la lista

        vehiculo *busqueda = concesionario_recibido->Lista_vehiculos;
        vehiculo *anterior = NULL;

        while (busqueda != NULL && busqueda->placa != placa_eliminar) {
          anterior = busqueda;
          busqueda = busqueda->siguienteptr;
        }

        if (busqueda != NULL) {

          cout << "Vehiculo encontrado" << endl;
          cout << "Eliminando vehiculo..." << endl;

          // Primer condicional en caso de que anterior sea NULL
          // Hay que evaluar este caso ya que si anterior es NULL, estamos
          // hablando del primer elemento de la lista Y no se puede conectar
          // anterior con el siguiente a busqueda, ya que estariamos conectando
          // un null a "algo" Segmentation error inmediato
          if (anterior == NULL) {
            concesionario_recibido->Lista_vehiculos = busqueda->siguienteptr;
            delete busqueda;
          }

          else {
            anterior->siguienteptr = busqueda->siguienteptr;
            delete busqueda;
          }

          cout << "Vehiculo eliminado correctamente" << endl;

        }

        else {
          cout << "Vehiculo no encontrado" << endl;
        }
      }

      else {
        cout << "Lista de vehiculos vacia" << endl;
      }
    }

    else {
      cout << "Concesionario no encontrado" << endl;
    }
  }

  else {
    cout << "Lista de concesionarios vacia" << endl;
  }
}

void actualizar_vehiculos() {

  if (!concesionarios_esta_vacia()) {

    string concesionario_a_buscar;
    cout << "Introduzca el concesionario donde quiere actualizar el vehiculo: ";
    cin >> concesionario_a_buscar;

    Concesionarios *concesionario_recibido =
        busqueda_concesionario(concesionario_a_buscar);

    if (concesionario_recibido != NULL) {

      if (!vehiculos_esta_vacia(concesionario_recibido)) {

        int placa_actualizar;

        cout << "Introduzca la placa del vehiculo a actualizar" << endl;
        cin >> placa_actualizar;

        vehiculo *busqueda = concesionario_recibido->Lista_vehiculos;

        while (busqueda != NULL && busqueda->placa != placa_actualizar) {
          busqueda = busqueda->siguienteptr;
        }

        if (busqueda != NULL) {

          int opcion_elegida;
          cout << "Vehiculo encontrado" << endl;
          cout << "Menu de opciones a actualizar: " << endl;

          cout << "1.Placa" << endl;
          cout << "2.Marca" << endl;
          cout << "3.Modelo" << endl;
          cout << "4.Precio" << endl;
          cout << "Elija una directriz: ";
          cin >> opcion_elegida;

          switch (opcion_elegida) {
          case 1:
            cout << "Introduzca la nueva placa: ";
            cin >> busqueda->placa;
            break;
          case 2:
            cout << "Introduzca la nueva marca: ";
            cin >> busqueda->marca;
            break;
          case 3:
            cout << "Introduzca el nuevo modelo: ";
            cin >> busqueda->modelo;
            break;
          case 4:
            cout << "Introduzca el nuevo precio: ";
            cin >> busqueda->precio;
            break;
          default:
            cout << "Opcion invalida" << endl;
            break;
          }

        }

        else {
          cout << "Vehiculo no encontrado" << endl;
        }

      }

      else {
        cout << "Lista de vehiculos vacia" << endl;
      }

    }

    else {
      cout << "Concesionario no encontrado" << endl;
    }

  }

  else {
    cout << "Lista de concesionarios vacia" << endl;
  }
}

void actualizar_concesionarios() {

  if (!concesionarios_esta_vacia()) {

    string concesionario_a_modificar;
    cout << "Introduzca el NOMBRE del concesionario a modificar: ";
    cin >> concesionario_a_modificar;

    Concesionarios *concesionario_recibido =
        busqueda_concesionario(concesionario_a_modificar);

    if (concesionario_recibido != NULL) {

      int opcion_elegida;
      cout << "Concesionario encontrado" << endl;
      cout << "Menu de datos a modificar: " << endl;

      cout << "1.Nombre" << endl;
      cout << "2.Direccion" << endl;
      cout << "Elija una directriz: ";
      cin >> opcion_elegida;

      switch (opcion_elegida) {
      case 1:
        cout << "Introduzca el nuevo nombre del concesionario: ";
        cin >> concesionario_recibido->nombre_concesionario;
        break;
      case 2:
        cout << "Introduzca la nueva direccion del concesionario: ";
        cin >> concesionario_recibido->direccion_concesionario;
        break;
      default:
        cout << "Opcion no valida" << endl;
        break;
      }

    }

    else {
      cout << "Concesionario no encontrado" << endl;
    }

  }

  else {
    cout << "Lista de concesionarios vacia" << endl;
  }
}

void eliminar_concesionarios() {

  if (!concesionarios_esta_vacia()) {

    string concesionario_a_eliminar;
    cout << "Introduzca el NOMBRE del concesionario a eliminar: ";
    cin >> concesionario_a_eliminar;

    Concesionarios *actual = Lista_general;
    Concesionarios *anterior = NULL;

    while (actual != NULL &&
           actual->nombre_concesionario != concesionario_a_eliminar) {
      anterior = actual;
      actual = actual->Lista_concesionarios;
    }

    if (actual != NULL) {

      cout << "Concesionario encontrado" << endl;
      cout << "Preparando para eliminar..." << endl;

      if (anterior == NULL) {
        Lista_general = actual->Lista_concesionarios;
        vehiculo *busqueda = actual->Lista_vehiculos;
        while (busqueda != NULL) {
          actual->Lista_vehiculos = busqueda->siguienteptr;
          delete busqueda;
          busqueda = actual->Lista_vehiculos;
        }
        delete actual;
      }

      else {
        anterior->Lista_concesionarios = actual->Lista_concesionarios;
        vehiculo *busqueda = actual->Lista_vehiculos;
        while (busqueda != NULL) {
          actual->Lista_vehiculos = busqueda->siguienteptr;
          delete busqueda;
          busqueda = actual->Lista_vehiculos;
        }
        delete actual;
      }

    }

    else {
      cout << "Concesionario no encontrado" << endl;
    }

  }

  else {
    cout << "Lista de concesionarios vacia" << endl;
  }
}

void mostrar_concesionarios() {

  if (!concesionarios_esta_vacia()) {

    cout << "Mostrando concesionarios..." << endl;
    Concesionarios *actual = Lista_general;

    int contador = 1;

    while (actual != NULL) {
      cout << "Concesionario numero: " << contador << endl;
      cout << "Nombre: " << actual->nombre_concesionario << endl;
      cout << "Direccion: " << actual->direccion_concesionario << endl;
      actual = actual->Lista_concesionarios;
      contador++;
    }

  }

  else {
    cout << "Lista de concesionarios vacia" << endl;
  }
}

void mostrar_vehiculos() {

  if (!concesionarios_esta_vacia()) {

    string concesionario_buscar;
    cout << "Introduzca el concesionario del cual quiere mostrar los "
            "vehiculos: ";
    cin >> concesionario_buscar;

    Concesionarios *concesionario_recibido =
        busqueda_concesionario(concesionario_buscar);

    if (concesionario_recibido != NULL) {

      if (!vehiculos_esta_vacia(concesionario_recibido)) {
        cout << "Mostrando vehiculos..." << endl;
        vehiculo *actual = concesionario_recibido->Lista_vehiculos;
        int contador = 1;

        while (actual != NULL) {
          cout << "Vehiculo numero: " << contador << endl;
          cout << "Placa: " << actual->placa << endl;
          cout << "Marca: " << actual->marca << endl;
          cout << "Modelo: " << actual->modelo << endl;
          cout << "Precio: " << actual->precio << endl;
          actual = actual->siguienteptr;
          contador++;
        }

      }

      else {
        cout << "Lista de vehiculos vacia" << endl;
      }

    }

    else {
      cout << "Concesionario no encontrado" << endl;
    }

  }

  else {
    cout << "Lista de concesionarios vacia" << endl;
  }
}

void destruccion_total() {

  if (!concesionarios_esta_vacia()) {

    Concesionarios *actual = Lista_general;

    while (actual != NULL) {
      Lista_general = actual->Lista_concesionarios;
      if (!vehiculos_esta_vacia(actual)) {
        vehiculo *busqueda = actual->Lista_vehiculos;
        while (busqueda != NULL) {
          actual->Lista_vehiculos = busqueda->siguienteptr;
          delete busqueda;
          busqueda = actual->Lista_vehiculos;
        }

        delete actual;
        actual = Lista_general;
      }

      else {
        delete actual;
        actual = Lista_general;
      }
    }
  }
}

int main() {

  cout << "Bienvenido al concesionario!" << endl;

  int opcion_elegida;

  do {

    cout << "Menu de opciones: " << endl;
    cout << "1.Crear concesionario" << endl;
    cout << "2.Crear vehiculo dentro de concesionario" << endl;
    cout << "3.Buscar vehiculos dentro de concesionario" << endl;
    cout << "4.Eliminar vehiculos dentro de concesionario" << endl;
    cout << "5.Actualizar vehiculo" << endl;
    cout << "6.Actualizar concesionario" << endl;
    cout << "7.Eliminar concesionario" << endl;
    cout << "8.Mostrar vehiculos de concesionario" << endl;
    cout << "9.Mostrar concesionarios" << endl;
    cout << "10.Salir" << endl;
    cout << "Elija una directriz: ";
    cin >> opcion_elegida;

    switch (opcion_elegida) {
    case 1:
      creacion_concesionario();
      break;
    case 2:
      insertar_vehiculo();
      break;
    case 3:
      busqueda_vehiculos();
      break;
    case 4:
      eliminar_vehiculos();
      break;
    case 5:
      actualizar_vehiculos();
      break;
    case 6:
      actualizar_concesionarios();
      break;
    case 7:
      eliminar_concesionarios();
      break;
    case 8:
      mostrar_vehiculos();
      break;
    case 9:
      mostrar_concesionarios();
      break;
    case 10:
      cout << "Saliendo..." << endl;
      destruccion_total();
      break;
    default:
      cout << "Opcion no valida" << endl;
      break;
    }

  } while (opcion_elegida != 10);

  return 0;
}