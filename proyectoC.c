#include <stdio.h>

int main() {
    char opcion;
    
    
    float a1, b1, c1; // Constantes de la primera ecuación
    float a2, b2, c2; // Constantes de la segunda ecuación
    
    // Solicitar al usuario las constantes de la primera ecuación
    printf("Ingrese las constantes de la primera ecuación cuadrática (ax^2 + bx + c):\n");
    printf("Ingrese el valor de a: ");
    scanf("%f", &a1);
    printf("Ingrese el valor de b: ");
    scanf("%f", &b1);
    printf("Ingrese el valor de c: ");
    scanf("%f", &c1);

    // Solicitar al usuario las constantes de la segunda ecuación
    printf("\nIngrese las constantes de la segunda ecuación cuadrática (ax^2 + bx + c):\n");
    printf("Ingrese el valor de a: ");
    scanf("%f", &a2);
    printf("Ingrese el valor de b: ");
    scanf("%f", &b2);
    printf("Ingrese el valor de c: ");
    scanf("%f", &c2);

    // Mostrar las ecuaciones cuadráticas ingresadas por el usuario
    printf("\nLas ecuaciones cuadráticas ingresadas son:\n");
    printf("1ra ecuación: %gx^2 + %gx + %g\n", a1, b1, c1);
    printf("2da ecuación: %gx^2 + %gx + %g\n", a2, b2, c2);

    printf("\n¿Desea ingresar otra pareja de ecuaciones? (s/n): ");
    scanf(" %c", &opcion); // Se deja un espacio antes del %c para consumir el salto de línea pendiente

    return 0;
}
