#include <iostream>
#include <string>
using namespace std;

struct registro_civil {
    string nombre;
    int edad;
    string sexo;
};

registro_civil registro;

typedef registro_civil *punteros_registro;
punteros_registro puntero_1_registro = &registro;


int main() {

    int edad_persona;
    string nombre_persona;
    string sexo_persona;

    cout << "Nombre: ";
    cin >> nombre_persona;
    registro.nombre = nombre_persona;

    cout << "Edad: ";
    cin >> edad_persona;
    registro.edad = edad_persona;

    cout << "Sexo: ";
    cin >> sexo_persona;
    registro.sexo = sexo_persona;

    int *puntero_2 = &registro.edad;
    *puntero_2 = 17;

    cout << registro.edad << endl;
    
    puntero_1_registro->edad = 18;

    cout << puntero_1_registro->nombre << "-" << puntero_1_registro->edad << "-" << puntero_1_registro->sexo;

    return 0;

}

