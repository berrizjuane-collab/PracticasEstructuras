#include <iostream>
#include <string>
using namespace std;

struct operativo {
    string nombre;
    int id;
    operativo* subordinado;
};
//se define un puntero que viva dentro de la estructura, como un puntero dedicado a eso

//ahora se hace la estructura de los escudos
struct Escudo {
    int puntos_defensa;
    Escudo* escudo_siguiente; //puntero
};
//tiene un int puntos defensa (seria como la vida, creo) y siguiente que seria el escudo siguiente (ya que son escudos cambiables)
//en esta estructura se trabajara con la memoria dinamica (el corazon del proyecto)


int main() {
    cout << "Asignacion de valores" << endl;

    operativo soldado;
    operativo jefe;
    //aqui se conecta la estructura a dos variables
    //dentro de var "jefe" hay una estructura propia, y dentro de var "soldado", lo mismo

    Escudo* mi_escudo = new Escudo; //"new" para que sea una variable dinamica
    //el new Escudo es el programa diciendole al sistema: Ve a la ram y asignale un espacio donde quepa mi estructura Escudo, pero un espacio DINAMICO
    //Luego, dame las coordenadas de ese espacio y yo las guardo en la var "mi_escudo"
    //Que es a su vez un puntero con estructura Escudo
    mi_escudo->puntos_defensa = 100;
    mi_escudo->escudo_siguiente = nullptr; //importante que no apunte a nada, ya que al inciar ese escudo "siguiente" no existe todavia

    string nombre_soldado;
    string nombre_jefe;
    int id_soldado;
    int id_jefe;

    cout << "Nombre del soldado: ";
    cin >> nombre_soldado;
    cout << "Nombre del jefe: ";
    cin >> nombre_jefe;

    cout << "Id del soldado: ";
    cin >> id_soldado;
    cout << "Id del jefe: ";
    cin >> id_jefe;

    soldado.nombre = nombre_soldado;
    soldado.id = id_soldado;
    jefe.nombre = nombre_jefe;
    jefe.id = id_jefe;

    jefe.subordinado = &soldado; // Como en la estructura operativo hay un puntero predefinido, se accede a el mediante jefe.subordinado 
   // (siendo jefe la variable del tipo operativo)
   // en el puntero del jefe se guarda la direccion del soldado, para luego: 

    cout << "El nombre e id del soldado: " << endl;
    cout << "Id: " << jefe.subordinado->id << "-" << "Nombre: " << jefe.subordinado->nombre << endl;
    //con la flechita poder acceder a los datos del soldado desde el puntero del jefe
    //es IMPORTANTISIMO guardar la direccion del soldado primero: El puntero puede buscar datos solo en donde apunta
    cout << "Puntos de defensa: " << endl;
    cout << mi_escudo->puntos_defensa << endl;
    //se accede a los puntos de defensa desde la variable mi_escudo

    delete mi_escudo;
    //se elimina para dejar ese espacio en la ram vacio (la gracia de las var dinamicas)

    return 0;

}