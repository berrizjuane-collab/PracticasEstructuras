#include <iostream>
using namespace std;

typedef struct {
  string marca_auto;
  int modelo_auto;
  int ano_de_auto;
  string color;
  double precio;
} Auto;

Auto auto_a_comprar;

// se define un tipo punteros que sean apuntables a la estructura auto
typedef Auto *Punteros_Auto;
Punteros_Auto puntero_1 = &auto_a_comprar;

int cantidad_autos = 15;

int contador_array = 0;

Auto *lista_autos = new Auto[cantidad_autos];

void visualizar_autos() {

  cout << "Todos los autos en el concesionario y sus datos: " << endl;

  for (contador_array = 0; contador_array < cantidad_autos; contador_array++) {
    cout << "Datos: " << endl;
    cout << "Marca: " << lista_autos[contador_array].marca_auto << endl;
    cout << "Modelo: " << lista_autos[contador_array].modelo_auto << endl;
    cout << "Anno: " << lista_autos[contador_array].ano_de_auto << endl;
    cout << "Color: " << lista_autos[contador_array].color << endl;
    cout << "Precio: " << lista_autos[contador_array].precio << endl;
  }
}

void buscar() {

  int modelo_a_buscar;

  int contador = 0;

  bool encontrado = false;

  cout << "Introduzca el modelo del auto a buscar: ";
  cin >> modelo_a_buscar;

  while (lista_autos[contador_array].modelo_auto != modelo_a_buscar &&
         !encontrado) {
    for (contador_array = 0; contador_array < cantidad_autos;
         contador_array++) {
      if (lista_autos[contador_array].modelo_auto == modelo_a_buscar) {
        encontrado = true;
      }
    }
  }

  if (encontrado) {
    cout << "Modelo disponible" << endl;
  }

  else {
    cout << "Modelo no disponible" << endl;
  }
}

void introducir_auto() {
  cout << "Introduzca la marca del auto que desea: ";
  cin >> lista_autos[contador_array].marca_auto;
  cout << "Introduzca el modelo del auto que desea: ";
  cin >> lista_autos[contador_array].modelo_auto;
  cout << "Introduzca el anno del auto que desea: ";
  cin >> lista_autos[contador_array].ano_de_auto;
  cout << "Introduzca el color del auto que desea: ";
  cin >> lista_autos[contador_array].color;
  cout << "Introduzca el precio del auto que desea: ";
  cin >> lista_autos[contador_array].precio;
}

int main() {

  int opcion;

  cout << "Bienvenido al concesionario!" << endl;

  do {

    cout << "Menu: " << endl;
    cout << "1.Introducir Auto" << endl;
    cout << "2.Buscar Modelo" << endl;
    cout << "3.Visualizar concesionario" << endl;
    cout << "4.Salir" << endl;
    cin >> opcion;

    switch (opcion) {
    case 1:
      introducir_auto();
      break;
    case 2:
      buscar();
      break;
    case 3:
      visualizar_autos();
      break;
    }
  } while (opcion != 4);

  delete[] lista_autos;
  lista_autos = nullptr;
  return 0;
}
