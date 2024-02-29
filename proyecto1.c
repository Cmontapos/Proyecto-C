#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>

// Universidad de Costa Rica - IE-0117 
// Proyecto de C - Primera parte - Juego de gato
// Integrantes:
// Daniela Muñoz Arroyo - C15362
// Melissa Rodríguez Jiménez - C16634
// Cristopher Montero Campos - C14938

// Se define el tamaño de la matriz
#define tam_tablero 3

// Se define la matriz global
char tablero[tam_tablero][tam_tablero];
// Se definen las variables de jugadores
const gchar *jugador_1 = "cancelar.png"; 
const gchar *jugador_2 = "o.png";
// Variables de turnos
int total_turnos = 9;
int turno = 1;

// Función que configura el mensaje final 
void mensaje_ganador(const gchar *mensaje){
    GtkWidget *dialogo;
    dialogo = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", mensaje);
    // Mostrar el mensaje en pantalla
    gtk_dialog_run(GTK_DIALOG(dialogo));
    // Poder cerrar el mensaje una vez visto
    gtk_widget_destroy(dialogo);
}

// Función booleana que verifica si se ganó el juego
bool verificar_victoria(){
        // Se define columna 0 para empezar en la primera
        int col = 0;
        // Se recorre la matriz fila por fila
        for (int fila = 0; fila < tam_tablero; fila++){
            // Se agarra el primer valor de la fila para comparar
            int valor_inicial = tablero[fila][0];
            // Si el valor es diferente de 0, se hace la comparación
            // Si no se hace esto, agarra desde el inicio que se ganó
            if (valor_inicial != ' '){
                // Se verifica si el valor inicial es igual en toda la fila
                if (tablero[fila][col + 1] == valor_inicial && tablero[fila][col + 2] == valor_inicial){
                    return true;
                }
            } 
            col = 0;
        }
        // Se aplica la misma lógica que para las filas, pero en columnas
        int fila = 0;
        for (int col = 0; col < tam_tablero; col++){
            int valor_inicial = tablero[0][col];
            if (valor_inicial != ' '){
                if (tablero[fila + 1][col] == valor_inicial && tablero[fila + 2][col] == valor_inicial){
                    return true;
                }
            } 
            fila = 0;
        }
        // Se verifica si la casilla en común es diferente de 0
        if (tablero[1][1] != ' '){
            // Si lo es, verifica si las casillas que forman la diagonal son iguales
            if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]){
            return true;
            } else if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]){
            return true;
            } else {
            return false;
            }
        // Si ninguna se cumple, retorna falso
        } else {
            return false;
        }
    }

// Función que maneja el evento de clic en un botón
void en_boton_clickedado(GtkButton *button, gpointer data) {
    // Obtener el ID del botón clickeado
    const gchar *button_id = gtk_widget_get_name(GTK_WIDGET(button));

    // Definir variables
    int pos = atoi(button_id);
    int fila = pos / tam_tablero;
    int columna = pos % tam_tablero;
    
        // Si es el turno del jugador 1
        if (turno % 2 !=0){
            // Se verifica si el espacio está vacio
            if(tablero[fila][columna]== ' '){
                // Si no está se coloca la imagen de X
                GtkWidget *X = gtk_image_new_from_file(jugador_1);
                // Se cambia a la imagen
                gtk_button_set_image(button, X);
                // Y se cambia en la matriz para la lógica
                tablero[fila][columna] = 'X';
            }
        // Si no, se toma como turno del jugador 2
        } else {
            // Se aplica la misma lógica pero colocan O en vez de X
            if(tablero[fila][columna]== ' '){
                GtkWidget *O = gtk_image_new_from_file(jugador_2);
                gtk_button_set_image(button, O);
                tablero[fila][columna] = 'O';
            }
        }

    // Se verifica si la función devolvió verdadero
    if (verificar_victoria() == 1){
        // De ser así, se verifica el ganador y se coloca su mensaje
        if (turno % 2 !=0){
            mensaje_ganador("¡Felicidades! Ha ganado el jugador 1 (X).");
            gtk_main_quit();
        } else {
            mensaje_ganador("¡Felicidades! Ha ganado el jugador 2 (O).");
            gtk_main_quit();
        }
    // Si no se ha devuelto, se recorre la matriz buscando espacios en blanco
    } else {
        int i, j, cont = 0;
        for (i = 0; i < tam_tablero; i++) {
            for (j = 0; j < tam_tablero; j++) {
                if (tablero[i][j] == ' '){
                    // Si encuentra un espacio en blanco se suma al contador
                    cont++;
                }
            }
        }
        // Si el contador llega a 0 ya no hay espacios y nadie ganó
        if (cont == 0){
            // Se declara empate
            mensaje_ganador("Juego terminado, ha ocurrido un empate.");
            gtk_main_quit();
        }
    }
        turno++;
    }

// Funciónprincipal de juego
int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;
    GObject *button;

    // Se pone la matriz como vacia
    int i, j;
    for (i = 0; i < tam_tablero; i++) {
        for (j = 0; j < tam_tablero; j++) {
            tablero[i][j] = ' ';
        }
    }

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear el GtkBuilder
    builder = gtk_builder_new();

    // Cargar la interfaz gráfica desde el archivo .glade
    gtk_builder_add_from_file(builder, "menuGato.glade", NULL);

    // Obtener la ventana principal desde el archivo .glade
    window = GTK_WIDGET(gtk_builder_get_object(builder, "ventana1"));

    // Boton 0
    GtkButton *boton_0 = GTK_BUTTON(gtk_builder_get_object(builder, "0"));
    g_signal_connect(boton_0, "clicked", G_CALLBACK(en_boton_clickedado), NULL);

    // Boton 1
    GtkButton *boton_1 = GTK_BUTTON(gtk_builder_get_object(builder, "1"));
    g_signal_connect(boton_1, "clicked", G_CALLBACK(en_boton_clickedado),NULL);

    // Boton 2
    GtkButton *boton_2 = GTK_BUTTON(gtk_builder_get_object(builder, "2"));
    g_signal_connect(boton_2, "clicked", G_CALLBACK(en_boton_clickedado), NULL);

    // Boton 3
    GtkButton *boton_3 = GTK_BUTTON(gtk_builder_get_object(builder, "3"));
    g_signal_connect(boton_3, "clicked", G_CALLBACK(en_boton_clickedado), NULL);

    // Boton 4
    GtkButton *boton_4 = GTK_BUTTON(gtk_builder_get_object(builder, "4"));
    g_signal_connect(boton_4, "clicked", G_CALLBACK(en_boton_clickedado), NULL);

    // Boton 5
    GtkButton *boton_5 = GTK_BUTTON(gtk_builder_get_object(builder, "5"));
    g_signal_connect(boton_5, "clicked", G_CALLBACK(en_boton_clickedado), NULL);

    // Boton 6
    GtkButton *boton_6 = GTK_BUTTON(gtk_builder_get_object(builder, "6"));
    g_signal_connect(boton_6, "clicked", G_CALLBACK(en_boton_clickedado), NULL);

    // Boton 7
    GtkButton *boton_7 = GTK_BUTTON(gtk_builder_get_object(builder, "7"));
    g_signal_connect(boton_7, "clicked", G_CALLBACK(en_boton_clickedado), NULL);

    // Boton 8
    GtkButton *boton_8 = GTK_BUTTON(gtk_builder_get_object(builder, "8"));
    g_signal_connect(boton_8, "clicked", G_CALLBACK(en_boton_clickedado), NULL);

    // Conectar la señal "destroy" de la ventana principal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar la ventana principal
    gtk_widget_show(window);

    // Iniciar el bucle principal de eventos
    gtk_main();

    return 0;
}