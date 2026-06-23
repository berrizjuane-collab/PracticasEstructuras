#include <iostream>
using namespace std;

int suma(int valor_1 , int valor_2) {
        int resultado = valor_1 + valor_2;
        return resultado;
    }

int Resta(int valor_1, int valor_2) {
    int resultado = valor_1 - valor_2;
    return resultado;
}

int Multiplicacion(int valor_1, int valor_2) {
    int resultado = valor_1 * valor_2;
    return resultado;
}

int Division(int valor_1 , int valor_2) {
    int resultado = valor_1 / valor_2;
    return resultado;
}

int main()
{
    int repetir_bucle;

    cout << "Bienvenido a la calculadora" << endl;

    do {
        cout << "Menu de opciones" << endl;
        cout << "1.Suma" << endl;
        cout << "2.Resta" << endl;
        cout << "3.Multiplicacion" << endl;
        cout << "4.Division" << endl;
        cout << "Elija una opcion" << endl;

        int opcion_de_operacion;
        cin >> opcion_de_operacion;

        int valor_1;
        cout << "Elija el valor 1: ";
        cin >> valor_1;

        int valor_2;
        cout << "Elija el valor 2: ";
        cin >> valor_2;

        int resultado;

        switch (opcion_de_operacion) {
            case 1:
                resultado = suma(valor_1,valor_2);
                cout << "El resultado de la suma es: " << resultado << endl;
                break;

            case 2:
                resultado = Resta(valor_1 , valor_2);
                cout << "El resultado de la resta es: " << resultado << endl;
                break;
            
            case 3: 
                resultado = Multiplicacion(valor_1 , valor_2);
                cout << "El resultado de la multiplicacion es: " << resultado << endl;
                break;

            case 4: 
                if (valor_2 != 0) {
                    resultado = Division(valor_1 , valor_2);
                    cout << "El resultado de la division es: " << resultado << endl;
                }
                
                else {
                    cout << "Division por cero" << endl;
                }
                break;

            default:
                cout << "Opcion no valida, intente nuevamente" << endl;
                break;

        }


        cout << "Desea hacer otra operacion? Presione 1 si es asi, 2 si no" << endl;
        cin >> repetir_bucle;
    } while(repetir_bucle == 1);
    cout << "Muchas gracias por usar el programa!" << endl;

    return 0;
}
