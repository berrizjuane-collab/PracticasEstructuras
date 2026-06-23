#include <iostream>
#include <string>
using namespace std;

//practicas con punteros....

struct Escudos {
    int puntos_de_vida;
    Escudos* escudo_siguiente;
};

struct Operativos {
    int id;
    string nombre;
    Operativos* subordinado;
};

int main() {
    Operativos soldado;
    Operativos jefe;

    Escudos *escudo_1 = new Escudos;
    escudo_1->puntos_de_vida = 150;
    escudo_1->escudo_siguiente = nullptr;

    soldado.id = 50;

    jefe.subordinado = &soldado;
    jefe.subordinado->id = 40;

    cout << soldado.id << endl;

    soldado.subordinado = &jefe;
    soldado.subordinado->id = 80;

    cout << "Id del jefe" << jefe.id << endl;

    cout << "Pero ahora quiero cambiarlo" << endl;
    int *puntero_1 = &jefe.id;
    *puntero_1 = 100;

    cout << jefe.id << endl;

    Escudos var_escudo;
    Escudos var_esduo_2;
    var_escudo.escudo_siguiente = &var_esduo_2;
    var_escudo.escudo_siguiente->puntos_de_vida = 50;

    cout << var_esduo_2.puntos_de_vida << endl;

    return 0;
}