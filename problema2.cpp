#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

string Elegir_palabra() {
    string palabra_adivinar;
    srand(time(0));
    vector <string> lista_palabras = {"Gato", "Perro", "Animal", "Carro"};
    int indice = rand() % lista_palabras.size();
    return lista_palabras[indice];  
}

void Verificar_letra(string palabra_adivinar) {

    char letra_introducida;
    int letras_a_adivinar;
    int intentos_restantes;
    intentos_restantes = 5;

    string palabra_oculta(palabra_adivinar.length(), '_');

    bool acierto = false;

    while(intentos_restantes > 0 and palabra_oculta != palabra_adivinar) {
        
        cout << "Introduzca una letra" << endl;
        cin >> letra_introducida;
        
        for (int i = 0; i < palabra_adivinar.length(); i++) {

        if (palabra_adivinar[i] == letra_introducida){
            palabra_oculta[i] = letra_introducida;
            acierto = true;
        } }

        if (acierto) {
            cout << "Letra adivinada" << endl;
            cout << palabra_oculta << endl;
        }

        else {
            cout << "Letra incorrecta" << endl;
            intentos_restantes = intentos_restantes - 1;
            cout << "Intentos restantes: " << intentos_restantes << endl;
        }
    
    }
    if (palabra_oculta==palabra_adivinar) {
        cout << "Felicidades" << endl;
        cout << "Palabra oculta: " << palabra_oculta << endl;
    }

    else {
    cout << "Intentos acabados, juego fallido" << endl; }
}

int main () {

    cout << "Bienvenido al juego del ahorcado" << endl;

    char letra_introducida;
    string palabra_adivinar;

    palabra_adivinar = Elegir_palabra();

    Verificar_letra(palabra_adivinar);

    return 0;
}