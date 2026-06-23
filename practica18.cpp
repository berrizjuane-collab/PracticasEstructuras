#include <iostream>
using namespace std;

int *arreglo = new int[15];

void mostrar() {
  for (int i = 0; i < 15; i++) {
    cout << arreglo[i] << endl;
    i++;
  }
}

void llenar() {

  int k;
  for (int i = 0; i < 15; i++) {
    arreglo[i] = k;
    i++;
    k++;
  }
}

int main() {
  llenar();
  mostrar();
  delete[] arreglo;
  return 0;
}