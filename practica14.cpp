#include <iostream>
using namespace std;

//Practica de arrays de datos dinamicos con estructuras de datos
//Juan Berrizbeitia

typedef struct {
  int codigo;
  string nombre;
  double sueldo;
} registro_empleado;

typedef registro_empleado *puntero_empleado;

const int cantidad_registros = 15;

typedef puntero_empleado lista_empleados[cantidad_registros];

typedef struct {
  lista_empleados registros;
  int contador_registro = 0;
} tLista;

tLista Regis_Empleado;

void registrar_empleado() {

  if (Regis_Empleado.contador_registro == cantidad_registros) {
    cout << "Lista llena" << endl;
  }

  else {

    cout << "Registro de empleado" << endl;
    Regis_Empleado.registros[Regis_Empleado.contador_registro] =
        new registro_empleado;

    cout << "Introduzca el codigo del empleado: ";
    cin >> Regis_Empleado.registros[Regis_Empleado.contador_registro]->codigo;
    cout << "Introduzca el nombre del empleado: ";
    cin >> Regis_Empleado.registros[Regis_Empleado.contador_registro]->nombre;
    cout << "Introduzca el sueldo del empleado: ";
    cin >> Regis_Empleado.registros[Regis_Empleado.contador_registro]->sueldo;

    Regis_Empleado.contador_registro++;
  }
}

void visualizar_lista() {

  cout << "Lista de empleados: " << endl;
  for (int i = 0; i < Regis_Empleado.contador_registro; i++) {
    cout << "Empleado en posicion: " << i << endl;
    cout << "Codigo: " << Regis_Empleado.registros[i]->codigo << endl;
    cout << "Nombre: " << Regis_Empleado.registros[i]->nombre << endl;
    cout << "Sueldo: " << Regis_Empleado.registros[i]->sueldo << endl;
  }
}

void buscar_empleado() {

  int codigo_a_buscar;

  cout << "Introduzca el codigo del empleado a buscar: ";
  cin >> codigo_a_buscar;

  bool encontrado = false;

  for (int i = 0; i < Regis_Empleado.contador_registro;
       i++) { // Notese como en la iteracion del for pido que i itere hasta
              // la cantidad exacta de empleados registrados (contador), de lo
              // contrario el programa buscaria en posiciones de memoria que no
              // han sido asignadas y por lo tanto no contienen ningun dato, lo
              // que provocaria un error en el programa
    if (Regis_Empleado.registros[i]->codigo == codigo_a_buscar) {
      encontrado = true;
      cout << "Empleado encontrado" << endl;
      cout << "Posicion en lista: " << i << endl;
      cout << "Codigo: " << Regis_Empleado.registros[i]->codigo << endl;
      cout << "Nombre: " << Regis_Empleado.registros[i]->nombre << endl;
      cout << "Sueldo: " << Regis_Empleado.registros[i]->sueldo << endl;
    }
  }

  if (!encontrado) {
    cout << "Empleado no encontrado" << endl;
  }
}

void destruir_lista() { //Aqui lo mismo. Como los demas punteros son nulos que no apuntan a nada (c++ los crea asi automaticamente)
                        //Es mejor practica iterar hasta el numero de registros exactos creados
  for (int i = 0; i < Regis_Empleado.contador_registro; i++) {
    delete Regis_Empleado.registros[i];
    Regis_Empleado.registros[i] = nullptr;
  }
}

int main() {

  int opcion;

  cout << "Bienvenido, jefe" << endl;

  do {
    cout << "Menu: " << endl;
    cout << "1.Registrar Empleado" << endl;
    cout << "2.Visualizar Lista" << endl;
    cout << "3.Buscar Empleado" << endl;
    cout << "4.Salir" << endl;
    cout << "Esocga una directiva: ";
    cin >> opcion;
    switch (opcion) {
    case 1:
      registrar_empleado();
      break;
    case 2:
      visualizar_lista();
      break;
    case 3:
      buscar_empleado();
      break;
    case 4:
      cout << "Hasta luego, jefe" << endl;
      destruir_lista();
      break;
    default:
      cout << "Opcion no valida" << endl;
      break;
    }
  } while (opcion != 4);

  return 0;
}
