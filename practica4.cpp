#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct {
    string n1;
    string n2;
} tupla_edificio_residencia;

tupla_edificio_residencia ed_res;

typedef tupla_edificio_residencia *punteros_edificio_residencia;

typedef struct {
    int edad;
    string sexo;
    double sueldo;
} estructura_registro; //aqui se define UN TIPO DE DATO

estructura_registro registro;

typedef estructura_registro *punteros_registro; //aqui se define otro tipo de dato en base a la estructura anterior (el nuevo serian unicamente punteros)

typedef struct {
    string zona;
    int apartamento;
} ubicacion_de_residencia;

ubicacion_de_residencia residencia;

typedef ubicacion_de_residencia *punteros_residencia;

int main() {
    int edad_persona;
    string sexo_persona;
    double sueldo_persona;
    string zona_residencia;
    string edificio_ocupacion_1;
    string edificio_ocupacion_2;
    int apartamento_ocupacion;
    

    cout << "Introducir datos" << endl;
    cout << "Edad: ";
    cin >> edad_persona;
    cout << "Sexo: ";
    cin >> sexo_persona;
    cout << "Sueldo: ";
    cin >> sueldo_persona;
    cout << "Zona de residencia: ";
    cin >> zona_residencia;
    cout << "Edificio que ocupa (string 1): ";
    cin >> edificio_ocupacion_1;
    cout << "Edificio que ocupa (string 2): ";
    cin >> edificio_ocupacion_2;
    cout << "Departamento que ocupa: ";
    cin >> apartamento_ocupacion;


    registro.edad = edad_persona;
    registro.sexo = sexo_persona;
    registro.sueldo = sueldo_persona;
    residencia.zona = zona_residencia;
    ed_res.n1 = edificio_ocupacion_1;
    ed_res.n2 = edificio_ocupacion_2;
    residencia.apartamento = apartamento_ocupacion;

    punteros_registro puntero_1 = &registro;

    punteros_residencia puntero_2 = &residencia;

    punteros_edificio_residencia puntero_7 = &ed_res;

    cout << "El sueldo es: " << puntero_1->sueldo << endl;
    cout << "La edad es: " << puntero_1->edad << endl;
    cout << "El sexo es: " << puntero_1->sexo << endl;
    cout << "La zona es: " << puntero_2->zona << endl;
    cout << "El edificio es: " << puntero_7->n1 << "-" << puntero_7->n2 << endl;
    cout << "El apartamento es: " << puntero_2->apartamento << endl;

    //direcciones en memoria

    punteros_registro puntero_3 = &registro;
    punteros_residencia puntero_4 = &residencia;
    punteros_edificio_residencia puntero_8 = &ed_res;

    cout << puntero_3 << "-" << puntero_4 << endl;

    punteros_registro* puntero_5 = &puntero_3; // se agrega un asterisco extra para denotar puntero de puntero (equivalente a ** si no tuviera clase)
    punteros_residencia* puntero_6 = &puntero_4;
    punteros_edificio_residencia* puntero_9 = &puntero_8;

    cout << puntero_5 << "-" << puntero_6 << "-" << puntero_9 << endl;
    return 0;

}











