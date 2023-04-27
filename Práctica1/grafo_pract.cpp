 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos   : 2012-2021
 */

#include "grafo.h"

void GRAFO :: destroy()
{
	for (unsigned i=0; i< n; i++)
    {
		LS[i].clear();
		if (dirigido == 1)
        {
            LP[i].clear();
        };
	}
	LS.clear();
	LP.clear();

}

void GRAFO :: build (char nombrefichero[85], int &errorapertura)
{
    //constructor del grafo. 
    ElementoLista     dummy;
    //c coste, j, numero de nodo.
	ifstream textfile; //para abrir fichero de texto
	textfile.open(nombrefichero);
	if (textfile.is_open())
    {
		unsigned i, j, k; 
		// leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;//son los 3 primeros numeros --> nodos n, arcos m, dirigido es 0 = no dirigido, k = 1, dirigido.
		// los nodos internamente se numeran desde 0 a n-1
		// creamos las n listas de sucesores
		LS.resize(n);   //LS lista de adyacencia de los sucesores
        LP.resize(n);   //LP lista de adyacencia de los predecesores
	        // leemos los m arcos
		for (k=0;k<m;k++)
        	{
			textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c; //i nodo de origen, j nodo de destino, 
            if(Es_dirigido() == 1) {     //Si es dirigido tiene sucesores y predecesores.
                dummy.j = j-1;
                LS[i-1].push_back(dummy);
                dummy.j = i-1;
                LP[j-1].push_back(dummy); 
            } else {    //Sino, solo tiene sucesores
                dummy.j = j-1;
                LS[i-1].push_back(dummy);
                dummy.j = i-1;
                LS[j-1].push_back(dummy); 
            }
            
			//damos los valores a dummy.j y dummy.c
			//situamos en la posici�n del nodo i a dummy mediante push_backM
			//pendiente de hacer un segundo push_back si es no dirigido. O no.
			//pendiente la construcci�n de LP, si es dirigido
			//pendiente del valor a devolver en errorapertura
        }
    }else {
        errorapertura = 1; //Si hay un error de apertura, se cambia su valor a 1.
    }

}

/*void GRAFO::ListaPredecesores()
{

}*/

GRAFO::~GRAFO()
{
	destroy();
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
	build (nombrefichero, errorapertura);
}

void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
{
    //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
    destroy();
    //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
    build(nombrefichero, errorapertura);
}

unsigned GRAFO::Es_dirigido()
{
    return dirigido;
}

void GRAFO::Info_Grafo()
{
    if(dirigido == 1) {
        cout<<"Grafo dirigido";
        cout<<"\nNumero de nodos: "<<n;
        cout<<"\nNumero de arcos: "<<m<<endl;
    } else {
        cout<<"Grafo no dirigido";
        cout<<"\nNumero de nodos: "<<n;
        cout<<"\nNumero de aristas: "<<m<<endl;
    }
}

void Mostrar_Lista(vector<LA_nodo> L)
{
    for(int i = 0; i < L.size(); i++) {
        cout<<"["<<i+1<<"] : "; 
        for(int j = 0; j < L[i].size();j++) {
            cout<<L[i][j].j +1<<" : ("<<L[i][j].c<<")";
        }
        if(!L[i].size()) {
            cout<<"null";
        }
        cout<<"\n";
    }
}

void GRAFO :: Mostrar_Listas (int l)
{
    if(l == 0 || l == 1) {
        Mostrar_Lista(LS);
    } else if(l == -1){
        Mostrar_Lista(LP);
    }
}

void GRAFO::Mostrar_Matriz() //Muestra la matriz de adyacencia, tanto los nodos adyacentes como sus costes
{

}

void GRAFO::dfs_num(unsigned i, vector<LA_nodo>  L, vector<bool> &visitado, vector<unsigned> &prenum, unsigned &prenum_ind, vector<unsigned> &postnum, unsigned &postnum_ind) //Recorrido en profundidad recursivo con recorridos enum y postnum
{
	visitado[i] = true;
    prenum[prenum_ind++]=i;//asignamos el orden de visita prenum que corresponde el nodo i
    for (unsigned j=0;j<L[i].size();j++)
             if (!visitado[L[i][j].j])
                {
                dfs_num(L[i][j].j, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
                };
    postnum[postnum_ind++]=i;//asignamos el orden de visita posnum que corresponde al nodo i
}

/*void GRAFO::RecorridoProfundidad()
{

}*/

void GRAFO::bfs_num(	unsigned i, //nodo desde el que realizamos el recorrido en amplitud
				vector<LA_nodo>  L, //lista que recorremos, LS o LP; por defecto LS
				vector<unsigned> &pred, //vector de predecesores en el recorrido
				vector<unsigned> &d) //vector de distancias a nodo i+1
//Recorrido en amplitud con la construcci�n de pred y d: usamos la cola
{
    vector<bool> visitado; //creamos e iniciamos el vector visitado
    visitado.resize(n, false);  
    visitado[i-1] = true;
 
    pred.resize(n, 0); //creamos e inicializamos pred y d
    d.resize(n, 0);
    pred[i-1] = i;
    d[i-1] = 0;

    queue<unsigned> cola; //creamos e inicializamos la cola
    cola.push(i-1);//iniciamos el recorrido desde el nodo i+1
 
    while (!cola.empty()) //al menos entra una vez al visitar el nodo i+1 y contin�a hasta que la cola se vac�e
    {   unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
        cola.pop(); //lo sacamos de la cola
        //Hacemos el recorrido sobre L desde el nodo k+1
        for (unsigned j=0;j<L[k].size();j++)
            //Recorremos todos los nodos u adyacentes al nodo k+1
            //Si el nodo u no est� visitado
            {
                if (visitado[L[k][j].j] == false) {
                    visitado[L[k][j].j] = true;
                    cola.push(L[k][j].j);
                    pred[L[k][j].j] = k + 1;
                    d[L[k][j].j] = d[k] + 1;
                }
            //Lo visitamos
            //Lo metemos en la cola
            //le asignamos el predecesor
            //le calculamos su etiqueta distancia
            };
        //Hemos terminado pues la cola est� vac�a
    };
}


void GRAFO::RecorridoAmplitud() //Construye un recorrido en amplitud desde un nodo inicial
{
    unsigned i;
    unsigned n = LS.size();
    vector<unsigned> pred;
    vector<unsigned> d;
    
    int distancia = i;
    int max = 0;
    int maxpred = 0;


    cout<<"Elija nodo de partida? [1-"<< n <<"]: ";
    cin>>i;
    cout<<"Nodo Inicial: "<<i<<endl;

    bfs_num(i, LS, pred, d);

    for(int r = 0; r < d.size(); r++) {
        if(d[r] > max) {
            max = d[r];
        }
    }
    cout<<"\nNodos segun distancia al nodo inicial en numero de aristas";
    cout<<"\nDistancia 0 aristas : "<<i;
    for(int j = 1; j <= max; j++) {
        cout<<"\nDistancia "<<j<<" aristas : ";
        bool primero = true;
        for(unsigned k = 0; k < d.size(); k++) {
            if(d[k] == j) {
                if(primero) {
                    primero = !primero;
                } else {
                    cout<<" : ";
                }
                cout<< k+1;
            }
        }

    }
   
   
    std::cout << "\n";
    std::cout << "d: " << std::endl;
    for (int j = 0; j < d.size(); ++j) {
        std::cout << d[j] << " ";
    }
    std::cout << "\n";

    std::cout << "Pause" << std::endl;

    std::cout << "pred: " << std::endl;
    for (int j = 0; j < pred.size(); ++j) {
        std::cout << pred[j] << " ";
    }

   
    cout<<"\n\nRamas de conexion en el recorrido";
   
    for (unsigned int l = 1; l < pred.size(); l++) {
        for (unsigned int h = 0; h < d.size(); h++) {   
            if (d[h] == l && pred[h] != 0) {
                vector<unsigned int> v;
                unsigned int temp = h+1;
                v.push_back(temp);
                while (pred[(temp-1)] > i) {
                    temp = pred[(temp-1)];
                    v.push_back(temp); 
                }
                cout <<"\n"<< i ;
                for (unsigned int x{v.size()}; x > 0; --x ) {
                    cout << " - " << v[x-1];
                }
            }
        }
    }
    cout<<"\n";
}

// void GRAFO::FloydWarshall() //Algoritmo de FW para caminos mínimos entre cualquier par de nodos;
// {
//     vector <LA_nodo> P; //Usaremos la misma estructura de datos de LS para guardar P y D
//     //Inicializamos P y D en P
//     //Creamos P
//     P.resize(n); //Ya tenemos las posiciones P[0] a P[n-1]
//         for (unsigned i=0; i<n; i++) { 
//             P[i].resize(n);
//         } //Ya tenemos la matriz cuadrada
//             for (unsigned i=0;i<n;i++) {
//                 for (unsigned j=0;j<n;j++) {
//                     if (i != j) { //Inicialización base
//                         P[i][j].c = maxint; //en el campo .j ponemos el predecesor
//                         P[i][j].j = 0; // en el campo .c ponemos el coste
//                     } else {//Inicializamos los bucles
//                         P[i][j].c = 0; //El coste en el caso de un bucle
//                         P[i][j].j = i+1; //El predecesor en el caso de un bucle
//                     } 
//                 };
//             }
//         //Recorremos LS para inicializar P, su predecesor en .j y su distancia en .c
//             for (unsigned i=0;i<n;i++) {
//                 for (unsigned j=0;j<LS[i].size();j++) {
//                     P[i][LS[i][j].j].j = i+1;
//                     P[i][LS[i][j].j].c= LS[i][j].c;
//                 };
//             }
//     //Con las matrices ya inicializadas, vamos ahora a realizar las k comparativas...
//     for(int k = 0; k < n; k++) {
//         for(int i = 0; i < n; i++) {
//             if(i != k) {
//                 for(int j = 0; j < n; j++) {
//                     if(j != k) {
//                         if(P[i][j].c > (P[i][k].c + P[k][j].c)) {
//                             P[i][j].c = P[i][k].c + P[k][j].c;
//                             P[i][j].j = P[k][j].j;
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     //Bien, ya tenemos D y P, mostremos las matrices y los caminos mínimos...
//     cout<<"\nMatriz de distancias finales: \n";
//     for(int i = 0; i < n; i++) {
//         for(int k = 0; k < n; k++) {
//             if(P[i][k].c > 0 && P[i][k].c < 10000) {
//                 cout<<" "<<P[i][k].c<<"  |";
//             } else if(P[i][k].c >= 10000){
//                 cout<<" Inf |";
//             } else if(P[i][k].c == 0) {
//                 cout<<" "<<P[i][k].c<<"   |";
//             }
            
//         }
//         cout<<"\n";
//     }
    
//     cout<<"\nMatriz de predecesores: \n";
//     for(int i = 0; i < n; i++) {
//         for(int k = 0; k < n; k++) {
//             if(P[i][k].j != 0) {
//                 cout<<P[i][k].j<<" | ";
                
//             } else {
//                 cout<<"- | ";
//             }
//         }
//         cout<<"\n";
//     }

//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < n; j++) {
//             if(P[i][j].c < 10000 && i != j) { //si es mayor de 10000 significa que el coste es infinito, y en la diagonal, los predecesores son los mismos nodos
//                 vector<int> predecesores;
//                 int aux = j;
//                 cout<<"Camino minimo de "<<i+1<<" a "<<j+1<<" coste "<<P[i][j].c<<" : ";
//                 while(aux != i) {
//                     predecesores.push_back(P[i][aux].j);
//                     aux = P[i][aux].j-1; //salta a la columna del predecesor
//                     if(aux == j) break;
//                 }
//                 for(int i = predecesores.size()-1; i >= 0; i--) {
//                     cout<<predecesores[i]<<" - ";
//                 }
//                 cout<<j+1<<"\n";
//             }
//         }
//     }

// }