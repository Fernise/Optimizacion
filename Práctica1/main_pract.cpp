 /*
 *  Programa principal.
 *
 *
 *               Autores : Antonio Sedeno Noda, Sergio Alonso.
 *               Cursos  : 2012-2021
 */

#include <string.h>
#include "grafo.h"


void menu (unsigned dirigido, char &opcion)
//Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
{
    cout<<"\nOptimiza!cion en Grafos, 2020-2021 NAHIA"<<endl;
    cout<<"c. [c]argar grafo desde fichero"<<endl;
    if (dirigido == 0) //Grafo no dirigido
            {
            cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
            cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
            cout<<  "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo"<<endl;
	    //Aqui se anaden mas opciones al menu del grafo no dirigido
            }
    else
            {
            cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
            cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
            cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
            cout<<  "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo"<<endl;
            cout<<  "f. Algoritmo de Floyd Warshall"<<endl;
	    //Aqui se anaden mas opciones al menu del grafo dirigido
            };
    cout << "q. Finalizar el programa" << endl;
    cout << "Introduce la letra de la accion a ejecutar  > ";
    cin >> opcion;
};

void clrscr()
{
	system("cls");
}

void pressanykey()
{
    system("pause");
}


// El principal es simplemente un gestor de menu, diferenciando acciones para dirigido y para no dirigido, y un menu inicial si no hay un grafo cargado
int main(int argc, char *argv[])
{
    int error_apertura;
    char nombrefichero[85], opcion;
    clrscr();
    //Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos cargar, si no, lo pedimos desde teclado
    if (argc > 1)
    {
	cout << "Cargando datos desde el fichero dado como argumento" << endl;
        strcpy(nombrefichero, argv[1]);
    }
    else
    {
        cout << "Introduce el nombre completo del fichero de datos" << endl;
        cin >> nombrefichero;
    };
    GRAFO G(nombrefichero, error_apertura);
    if (error_apertura == 1)
    {
        cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
        pressanykey();
        clrscr();
    }
    else
    {
        cout<< "Grafo cargado desde el fichero " << nombrefichero << endl;
        pressanykey();
        clrscr();
        do
        {
            menu(G.Es_dirigido(), opcion);
            switch (opcion)
            {
                case 'c' :
                    clrscr();
         	    cout << "Introduce el nombre completo del fichero de datos" << endl;
                    cin >> nombrefichero;
                    G.actualizar(nombrefichero, error_apertura);
                    if (error_apertura == 1)
                    {
                        cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
                    }
                    else
                    {
                        cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
                    };
                    pressanykey();
                    clrscr();
                    break;

                case 'i' :
                    clrscr();
		    cout << "Grafo cargado desde " << nombrefichero << endl;
                    G.Info_Grafo();
                    pressanykey();
                    clrscr();
                    break;

                case 'a' :
                    clrscr();
		    cout << "Nodos de la lista de adyacentes " << endl;
                    G.Mostrar_Listas(0);
                    pressanykey();
                    clrscr();
                    break;

                case 'p' :
                    clrscr();
		    cout << "Nodos de la lista de predecesores " << endl;
                    G.Mostrar_Listas(-1);
                    pressanykey();
                    clrscr();
                    break;

                case 's' :
                    clrscr();
		    cout << "Nodos de la lista de sucesores " << endl;
                    G.Mostrar_Listas(1);
                    pressanykey();
                    clrscr();
                    break;

                case 'm' :
                    clrscr();
		    cout << "Vamos a construir un recorrido de amplitud\n" << endl;
                    G.RecorridoAmplitud();
                    pressanykey();
                    clrscr();
                    break;
                
                case 'f' :
                    clrscr();
		    cout << "Algoritmo de Floyd y Warshall\n" << endl;
                    // G.FloydWarshall();
                    pressanykey();
                    clrscr();
                    break;

            }
    }
    while (opcion != 'q');
    }
    cout << "Fin del programa" << endl;
	return (0);
};

