def funcion_1(a,b):
    resultado = a + b
    return resultado

while True:
    a = int(input("Introduzca el valor 1: "))
    b = int(input("Introduzca el valor 2: "))
    resultado = funcion_1(a,b)
    print(f"Resultado suma: {resultado}")