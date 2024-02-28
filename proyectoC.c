#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Función para solicitar los coeficientes de una ecuación cuadrática
void solicitarCoeficientes(float coeficientes[3]) {
    printf("\nCon la forma de una ecuación cuadrática (ax^2 + bx + c):\n");
    for (int i = 0; i < 3; i++) {
        // Definir un mensaje adecuado según el coeficiente que se está solicitando
        char *coeficiente;
        if (i == 0) {
            coeficiente = "a";
        } else if (i == 1) {
            coeficiente = "b";
        } else {
            coeficiente = "c";
        }
        
        char input[100];
        float numero;
        // Solicitar al usuario el coeficiente correspondiente
        while(1) {
            printf("Ingrese el valor de %s: ", coeficiente);
            fgets(input, sizeof(input), stdin);
            
            // Convertir la entrada a un número de punto flotante
            char *endptr;
            numero = strtof(input, &endptr);

            // Verificar si la conversión fue exitosa
            if (endptr == input || *endptr != '\n') {
                printf("Error: Entrada no válida. Por favor, ingrese un número.\n");
            } else if (i == 0 && numero == 0){
                printf("Error: Entrada no válida. La constante A no puede ser cero\n");
            } else {
                coeficientes[i] = numero;
                break;
            }
        }
    }
}

int main() {
    char opcion;
    float coeficientes1[3]; // Lista para almacenar los coeficientes de la ecuación
    float coeficientes2[3]; // Lista para almacenar los coeficientes de la ecuación

    //Titulo para guiar al usuario
    printf("\nFavor ingrese los coefisientes de la ecuacion 1");

    // Llamar a la función para solicitar los coeficientes
    solicitarCoeficientes(coeficientes1);

    // Mostrar los coeficientes ingresados
    printf("\nLos coeficientes De la ecuacion 1 son: ");
    printf("a = %g, b = %g, c = %g\n", coeficientes1[0], coeficientes1[1], coeficientes1[2]);

    //Titulo para guiar al usuario
    printf("\nFavor ingrese los coefisientes de la ecuacion 2");

    // Llamar a la función para solicitar los coeficientes
    solicitarCoeficientes(coeficientes2);

    // Mostrar los coeficientes ingresados
    printf("\nLos coeficientes de la ecuacion 2 son: ");
    printf("a = %g, b = %g, c = %g\n", coeficientes2[0], coeficientes2[1], coeficientes2[2]);

    return 0;
}
