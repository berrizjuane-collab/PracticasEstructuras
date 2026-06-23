#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct tupla_informacion {
    string id_maquina;
    string fichero_imprimible;
};

vector <tupla_informacion> cola_impresion = {};

void Acc_request () {
    string id_impresora;
    string fichero_imprimible;
    
    cout << "Porfavor, introduzca el id de su impresora: " ;
    cin >> id_impresora;

    cout << "Porfavor, introduzca el fichero a imprimir: " ;
    cin >> fichero_imprimible;

    cola_impresion.push_back({id_impresora, fichero_imprimible});
}

void Acc_printwork () {
    cout << "Imprimiendo primer elemento en cola" << endl;
    cout << cola_impresion[0].id_maquina << cola_impresion[0].fichero_imprimible << endl;

    cola_impresion.erase(cola_impresion.begin());
}

void Acc_getnumrequest () {
    int i;
    i = cola_impresion.size();
    cout << "El numero de peticiones en cola es: " << i << endl;
}

void Acc_showall () {
    cout << "Todos los elementos en cola" << endl;
    for (tupla_informacion item : cola_impresion) {
        cout << item.fichero_imprimible << item.id_maquina << endl;
    }
}

int main () {

    int resultado_eleccion;

    do {cout << "Bienvenido a las impresiones" << endl;
    cout << "Elija una accion del menu: " << endl;
    cout << "1.Agregar peticion" << endl;
    cout << "2.Imprimir primera peticion" << endl;
    cout << "3.Mostrar numero de peticiones" << endl;
    cout << "4.Mostrar todas las peticiones" << endl;
    cout << "5.Salir del programa" << endl;

    cin >> resultado_eleccion;

    switch (resultado_eleccion) {
        case 1: 
            Acc_request();
            break;
        case 2:
            Acc_printwork();
            break;
        case 3:
            Acc_getnumrequest();
            break;
         case 4:
            Acc_showall();
            break;
    } }while(resultado_eleccion != 5);

    cout << "Muchas gracias por usar" << endl;
    return 0;
}



