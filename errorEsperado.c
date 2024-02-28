#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <gsl/gsl_math.h>

// Se definen variables globales
double A, B, C; // Constantes de la expresion cuadratica que se forma al igualar fx y gx
double error_usuario; // Error permitido por usuario
double a1, b1, c1; // Constantes de la primera ecuación fx
double a2, b2, c2; // Constantes de la segunda ecuación gx

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
        
        char entrada[100];
        float numero;
        // Solicitar al usuario el coeficiente correspondiente
        while(1) {
            printf("Ingrese el valor de %s: ", coeficiente);
            fgets(entrada, sizeof(entrada), stdin);
            
            // Convertir la entrada a un número de punto flotante
            char *endptr;
            numero = strtof(entrada, &endptr);

            // Verificar si la conversión fue exitosa
            if (endptr == entrada || *endptr != '\n') {
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

// Funcion para hallar subdominios en caso de no tener una interseccion real entre ambas funciones
int casos_especiales(double *x_izquierda, double *x_derecha){
    /*
    Funcion para encontrar el subdominio donde dos funciones son similares respecto a cierto porcentaje
    de error dado por el usuario. Esta funcion es especifica para los casos especiales donde las
    funciones nunca se intersecan.

    :return  *x_izquierda y *x_derecha: devuelve el subdominio de las funciones
    */

    // Se definen e inicializan variables de iteracion
    *x_derecha;
    *x_izquierda;
    double x;
    int contador = 0;

    // Iteracion entre dominio permitido de las funciones
    for (x=-100000.0; x<= 100000.0; x= x + 0.1){

        // Calculo del error real
        double fx = a1 * x*x + b1 * x + c1;
        double gx = a2 * x*x + b2 * x + c2;
        double error_real = 100 * fabs(fx - gx)/fx;

        // Verificacion del error real con el dado por el usuario
        if (error_real <= error_usuario){
            // Guarda primera coincidencia
            if (contador == 0){
                *x_izquierda = x;
                contador = contador + 1;
            }
        }else{
            // Guarda ultima coincidencia
            if (contador == 1){
                *x_derecha = x - 0.1;
            // En caso de no encontrar similitud
            }else{
                printf("No hay subdominio que cumpla con el procentaje de error aceptado");
                break;
            }
        }
    }

}

// Funcion para hallar subdominios a partir de las intersecciones de las funciones
int hallar_subdominio(double x, double *x_izquierda, double *x_derecha){
    /*
    Funcion que encuentra el subdominio donde dos funciones son similares con cierto porcentaje de
    error, esto a partir de la interseccion de ambas.
double a1, b1, c1; // Constantes de la primera ecuación fx
double a2, b2, c2; // Constantes de la segunda ecuación gx
    :param float x: solucion de la ecuacion
    :return float x_izquierda y float x_derecha: devuelve el subdominio de las funciones
    */

    // Se verifica que la solucion este en el dominio de las funciones
    if (x < -100000 || x > 100000) {
        printf("La solucion se sale del dominio de las funciones\n");
        exit(1);
    }

    // Se inicializan las variables de funcion
    double error_calculado = 0;
    double error_anterior_calculado = 0;
    *x_derecha = x;
    *x_izquierda = x;

    /*Mediante un while se controla que las iteraciones de x+0.1 y x-0.1 se
    mantengan hasta alcancar el error del usuario. Dentro del mismo se
    calcula el error tanto por el lado derecho como el izquierdo
    simultanemente y se toma el mayor de ellos como el error calculado.*/
    while (error_calculado <= error_usuario) {
        if (error_calculado < error_anterior_calculado) {
            break;
        }
        // Contador de iteraciones por la derecha y por la izquierda
        *x_derecha += 0.1;
        *x_izquierda -= 0.1;

        // Calculo de error por la derecha de la solucion X encontrada
        double fx = a1 * pow(*x_derecha, 2) + b1 * *x_derecha + c1;
        double gx = a2 * pow(*x_derecha, 2) + b2 * *x_derecha + c2;
        double error_derecha = 100 * fabs((fx - gx)) / fx;

        // Calculo de error por la izquierda de la solucion X encontrada
        fx = a1 * pow(*x_izquierda, 2) + b1 * *x_izquierda + c1;
        gx = a2 * pow(*x_izquierda, 2) + b2 * *x_izquierda + c2;
        double error_izquierda = 100 * fabs((fx - gx)) / fx;

        /*Comparacion mediante if para determinar cual error (el del lado
          derecho o izquierdo) es el mayor*/
        if (error_derecha < error_izquierda) {
            error_anterior_calculado = error_calculado;
            error_calculado = error_izquierda;
        } else {
            error_anterior_calculado = error_calculado;
            error_calculado = error_derecha;
        }
    }

    // Se revisa si x_derecha o x_izquierda se salen del dominio
    if (*x_izquierda < -100000 || *x_derecha > 100000) {
        *x_izquierda = 0;
        *x_derecha = 0;
    } else {
        *x_izquierda += 0.1;
        *x_derecha -= 0.1;
    }
}

// Definir la función cuadrática
double funcionCuadratica(double x, double a, double b, double c) {
    return a * x * x + b * x + c;
}

// Generar datos de las funciones en un archivo para Gnuplot
void generarArchivo(const char *nombreArchivo, double (*func1)(double, double, double, double),
                        double (*func2)(double, double, double, double),
                        double a1, double b1, double c1,
                        double a2, double b2, double c2,
                        double x_min, double x_max, int puntosGraf) {
    FILE *data_file = fopen(nombreArchivo, "w");
    if (data_file == NULL) {
        printf("Error al abrir el archivo de datos.\n");
        exit(1);
    }

    double step = (x_max - x_min) / (puntosGraf - 1);
    for (int i = 0; i < puntosGraf; i++) {
        double x = x_min + i * step;
        double y1 = func1(x, a1, b1, c1);
        double y2 = func2(x, a2, b2, c2);
        fprintf(data_file, "%f %f %f\n", x, y1, y2);
    }
    fclose(data_file);
}

// Graficar los datos utilizando Gnuplot
void graficasGnuplot(const char *nombreArchivo) {
    FILE *gnuplot_pipe = popen("gnuplot -persist 2>/dev/null", "w");
    if (gnuplot_pipe == NULL) {
        printf("Error al abrir la tubería de Gnuplot.\n");
        exit(1);
    }

    fprintf(gnuplot_pipe, "set xlabel 'x'\n");
    fprintf(gnuplot_pipe, "set ylabel 'y'\n");
    fprintf(gnuplot_pipe, "plot '%s' using 1:2 with lines title 'Function 1', \
                            '' using 1:3 with lines title 'Function 2'\n", nombreArchivo);
    fflush(gnuplot_pipe);

    // Esperar a que se cierre Gnuplot
    printf("Presiona Enter para continuar...\n");
    getchar();
    
    pclose(gnuplot_pipe);
    
    // Eliminar el archivo de datos
    if (remove(nombreArchivo) != 0) {
        printf("Error al eliminar el archivo de datos.\n");
    }
}


// Programa Principal
int main() {
    char opcion;
    char entrada[100];
    float coeficientes1[3]; // Lista para almacenar los coeficientes de la ecuación
    float coeficientes2[3]; // Lista para almacenar los coeficientes de la ecuación
    int puntosGraf = 500; // Cantidad de puntos en el domninio

    //Titulo para guiar al usuario
    printf("\nFavor ingrese los coefisientes de la ecuacion 1");

    // Llamar a la función para solicitar los coeficientes
    solicitarCoeficientes(coeficientes1);

    //Titulo para guiar al usuario
    printf("\nFavor ingrese los coefisientes de la ecuacion 2");

    // Llamar a la función para solicitar los coeficientes
    solicitarCoeficientes(coeficientes2);

    // Mostrar las ecuaciones cuadráticas ingresadas por el usuario
    printf("\nLas ecuaciones cuadráticas ingresadas son:\n");
    printf("1ra ecuación: %gx^2 + %gx + %g\n", coeficientes1[0], coeficientes1[1], coeficientes1[2]);
    printf("2da ecuación: %gx^2 + %gx + %g\n", coeficientes2[0], coeficientes2[1], coeficientes2[2]);

    // Solicitar el porcentaje de error
    while(1) {
            printf("Ingrese el valor del error esperado: ");
            fgets(entrada, sizeof(entrada), stdin);
            
            // Convertir la entrada a un número de punto flotante
            char *endptr;
            error_usuario = strtof(entrada, &endptr);

            // Verificar si la conversión fue exitosa
            if (endptr == entrada || *endptr != '\n') {
                printf("Error: Entrada no válida. Por favor, ingrese un número.\n");
            } else if (error_usuario < 0 || error_usuario > 100){
                printf("Error: La entrada sale de los límites [0,100]\n");
            } else {
                break;
            }
        }
    
    // Primero se evalua las intersecciones de las funciones por lo que se deben igualar.
    // Generando la expresion (a1-a2)x^2+(b1-b2)x+(c1-c2)
    // float A, B, C;  // Se definen nuevas constantes para expresion cuadratica
    a1 = coeficientes1[0];
    b1 = coeficientes1[1];
    c1 = coeficientes1[2];
    a2 = coeficientes2[0];
    b2 = coeficientes2[1];
    c2 = coeficientes2[2];
    A = a1 - a2;
    B = b1 - b2;
    C = c1 - c2;

    
    // En algunos casos A=0 convirtiendo la expresion a una ecuacion lineal
    if (A != 0){
        // Se aplica la fórmula general, generando dos posibles resultados
        double discriminante = B *B - 4.0 * A * C;  // Calculo del discriminante

        // Se verifica si el discriminante genera soluciones complejas
        // Caso 1: Dos soluciones reales de ecuacion cuadratica
        if (discriminante >= 0){
            // Calculo de las dos soluciones mediante la formula general
            double x1 = (-B + sqrt(discriminante)) / (2.0 * A);
            double x2 = (-B - sqrt(discriminante)) / (2.0 * A);
            double x_izquierda, x_derecha;
            // Se llama la funcion 'hallar_subdominio' para ambas soluciones
            hallar_subdominio(x1, &x_izquierda, &x_derecha);
            printf("\nUno de los subdominios es: (%lf, %lf)\n", x_izquierda, x_derecha);
            generarArchivo("datos.txt", funcionCuadratica, funcionCuadratica,
                       a1, b1, c1, a2, b2, c2, x_izquierda, x_derecha, puntosGraf);
            graficasGnuplot("datos.txt");
            
            hallar_subdominio(x2, &x_izquierda, &x_derecha);
            printf("\nEl otro subdominio es: (%lf, %lf)\n", x_izquierda, x_derecha);
            generarArchivo("datos.txt", funcionCuadratica, funcionCuadratica,
                       a1, b1, c1, a2, b2, c2, x_izquierda, x_derecha, puntosGraf);
            graficasGnuplot("datos.txt");
        }else{
            // Caso 2: Soluciones Complejas
            double x_izquierda, x_derecha;
            casos_especiales(&x_izquierda, &x_derecha);
            printf("\nEl subdominio es: (%lf, %lf)\n", x_izquierda, x_derecha);
            generarArchivo("datos.txt", funcionCuadratica, funcionCuadratica,
                       a1, b1, c1, a2, b2, c2, x_izquierda, x_derecha, puntosGraf);
            graficasGnuplot("datos.txt");
        }
    // Caso 3: Solucion de ecuacion lineal       
    }else{
        double X = (-C) / B;
        double x_izquierda, x_derecha;
        hallar_subdominio(X, &x_izquierda, &x_derecha);
        printf("\nEl subdominio es: (%lf, %lf)\n", x_izquierda, x_derecha);
        generarArchivo("datos.txt", funcionCuadratica, funcionCuadratica,
                       a1, b1, c1, a2, b2, c2, x_izquierda, x_derecha, puntosGraf);
        graficasGnuplot("datos.txt");
    }
    return 0;
}
