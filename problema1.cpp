#include <iostream>
using namespace std;
#include <algorithm>

//inversa de una palabra

string inversor_palabras(string palabra_usuario) {
    reverse(palabra_usuario.begin(),palabra_usuario.end());
    return palabra_usuario;
}

int main()
{
    cout << "Juego de la palabra inversa" << endl;

    string palabra;

    int repeticion;

    do{
        cout << "Introduzca su palabra: " << endl;
    cin >> palabra;

    string resultado;
    resultado = inversor_palabras(palabra);
    cout << "La palabra invertida es: " << resultado << endl;

    cout << "Desea volver a jugar?, Presione 1 si es asi, 2 si no es asi" << endl;
    cin >> repeticion;
    }while (repeticion==1);

    cout << "Muchas gracias por usar" << endl;

    return 0;
}