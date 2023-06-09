 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos   : 2012-2021
 */

#include "grafo.h"
#include <iostream>

#include <limits>

void GRAFO :: destroy()
{
	for (unsigned i=0; i < n; i++)
    {
		LS[i].clear();
		A[i].clear();
		if (dirigido == 1)
        {
            LP[i].clear();
        };
	}
	LS.clear();
	LP.clear();
	A.clear();

}

void GRAFO :: build (char nombrefichero[85], int &errorapertura)
{
    ElementoLista     dummy;
	ifstream textfile;
	textfile.open(nombrefichero);
	if (textfile.is_open())
    {
		unsigned i, j, k;
		// leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
		// los nodos internamente se numeran desde 0 a n-1
		// creamos las n listas de sucesores
		LS.resize(n);
        LP.resize(n);
        // leemos los m arcos
		for (k=0;k<m;k++)
        	{
			textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
			//damos los valores a dummy.j y dummy.c
            dummy.j = j - 1;
			//situamos en la posici�n del nodo i a dummy mediante push_back
			LS[i - 1].push_back(dummy);

            //pendiente de hacer un segundo push_back si es no dirigido. O no.
            if (dirigido == 0 && i != j) {
                dummy.j = i - 1;
                LS[j - 1].push_back(dummy);
            }
			//pendiente la construcci�n de LP, si es dirigido
            else {
                dummy.j = i - 1;
                LP[j - 1].push_back(dummy);
            }
        }
        //pendiente del valor a devolver en errorapertura
        errorapertura = 0;    
	    //...
    }  
    else {
        errorapertura = 1;
    }          
}

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
    if (dirigido == 1) {
        return 1;
    }
    return 0;
}

void GRAFO::Info_Grafo()
{
    if (dirigido == 0) {
        std::cout << "Grafo no dirigido | nodos " << n << " |  aristas " << m << std::endl; 
        std::cout << "\n";
    }
    if (dirigido == 1) {
        std::cout << "Grafo dirigido | nodos " << n << " |  arcos " << m << std::endl; 
        std::cout << "\n";
    }
}

void Mostrar_Lista(vector<LA_nodo> L)
{
    for (int i = 0; i < L.size(); ++i) {
        std::cout << "[" << i + 1 << "] : ";
        if (L[i].size() == 0) {
            std::cout << "null";
        }
        for (int k = 0; k < L[i].size(); ++k) {
            std::cout << L[i][k].j + 1 << " : (" << L[i][k].c << ")  ";

        }
        std::cout << "\n";
    }
}

void GRAFO :: Mostrar_Listas (int l)
{
    // Grafo no dirigido, se muestra la lista de adyacencia
    if (l == 0) {
        Mostrar_Lista(LS);
    }
    // Grafo dirigido, se muestra la lista de sucesores
    if (l == 1) {
        Mostrar_Lista(LS);
    }    
    // Grafo dirigido, se muestra la lista de predecesores
    if (l == -1) {
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

void GRAFO::RecorridoProfundidad()
{

}
void GRAFO::bfs_num(	unsigned i, //nodo desde el que realizamos el recorrido en amplitud
				vector<LA_nodo>  L, //lista que recorremos, LS o LP; por defecto LS
				vector<unsigned> &pred, //vector de predecesores en el recorrido
				vector<unsigned> &d) //vector de distancias a nodo i+1
//Recorrido en amplitud con la construcci�n de pred y d: usamos la cola
{
    vector<bool> visitado; //creamos e iniciamos el vector visitado
    visitado.resize(n, false);
    visitado[i - 1] = true;

    pred.resize(n, 0); //creamos e inicializamos pred y d
    d.resize(n, 0);
    pred[i - 1] = i;
    d[i - 1] = 0;

    queue<unsigned> cola;   //creamos e inicializamos la cola
    cola.push(i - 1);   //iniciamos el recorrido desde el nodo i - 1

    while (!cola.empty()) //al menos entra una vez al visitar el nodo i+1 y contin�a hasta que la cola se vac�e
    {
        unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
        cola.pop(); //lo sacamos de la cola
        //Hacemos el recorrido sobre L desde el nodo k+1
        for (unsigned j=0;j<L[k].size();j++) {
            //Recorremos todos los nodos u adyacentes al nodo k+1
            //Si el nodo u no est� visitado
            if (visitado[L[k][j].j] == false) {
                //Lo visitamos
                visitado[L[k][j].j] = true;
                //Lo metemos en la cola
                cola.push(L[k][j].j);
                //le asignamos el predecesor
                pred[L[k][j].j] = k + 1; // pred[2] (Nodo 3) = 4 + 1 (Nodo 5) [Nodo 3 es predecesor del nodo 5]
                std::cout << pred[L[k][j].j] << std::endl;
                //le calculamos su etiqueta distancia 
                d[L[k][j].j] = d[k] + 1;      // d[2] (Nodo 3) = 1 (Nodo 3 a distancia 1 del inicial) [Nodo 3 se encuentra a 1 arista del inicial]                       
                std::cout << d[L[k][j].j] << std::endl;
            }  
        }
    //Hemos terminado pues la cola est� vac�a
    }
}


void GRAFO::RecorridoAmplitud() //Construye un recorrido en amplitud desde un nodo inicial
{
    unsigned i = 0;
    unsigned n = LS.size();

    vector<unsigned> d;
    vector<unsigned> pred;

    int distancia = i;
    int max = 0;
    int maxpred = 0;
    
    std::cout << "Vamos a construir un recorrido en amplitud" << std::endl;

    std::cout << "Elige un nodo de partida? [1-" << n << "]: ";
    std::cin >> i;
    
    std::cout << "Nodo inicial: " << i << std::endl;
   
    bfs_num(i, LS, pred, d);
    
    int d_max = 0; // Distancia maxima que existe

    for (int j = 0; j < d.size(); ++j) {
        if (d[j] > d_max) {
            d_max = d[j];
        }
    }

    vector<unsigned int> recorrido;

    std::cout << "Nodos segun distancia al nodo inicial en numero de aristas" << std::endl;
    std::cout << "Distancia 0 aristas: " << i << std::endl;
    recorrido.push_back(i);
    for (int j = 1; j <= d_max; ++j) {
        std::cout << "Distancia " << j << " aristas: ";
        bool flag = true;
        for (unsigned k = 0; k < d.size(); ++k) {
            // Se chequea el vector d hasta encontrar una distancia igual a j 
            if (d[k] == j) { // d[1] / d[2] / d[3]
                if (flag) {
                    flag = !flag;
                }
                else {
                    std::cout << " : ";
                }
                std::cout << k + 1;
                recorrido.push_back(k + 1);
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    std::cout<<"Ramas de conexion en el recorrido" << std::endl;
    vector<unsigned int> v;    

    for (int j = 0; j < recorrido.size(); ++j) {
        std::cout << recorrido[j] << " ";
    }
}

void GRAFO::Prim() {
    unsigned u = 0;
    int coste_total = 0;
    vector<int> T;
    vector<int> coste(n, std::numeric_limits<int>::max());
    vector<bool> M (n, false); // Nodos que voy conectando 
    vector<unsigned> pred(n);

    coste[0] = 0;
    pred[0] = 0;
    M[0] = true;

    int contador = 0;
    while (contador < n - 1) {
        for (LA_nodo::iterator k = LS[u].begin(); k != LS[u].end(); ++k) { // k < 2
            unsigned j = k->j;
            int c = k->c;
            if (M[j] == false && coste[j] > c) { // INF > 4
                coste[j] = c;
                pred[j] = u;
            }
        }
        int aux_coste = std::numeric_limits<int>::max();
        for (int k = 0; k < coste.size(); ++k) {
            if (M[k] == false && coste[k] < aux_coste) {
                u = k;
                aux_coste = coste[k];
            }
        }
        M[u] = true;
        coste_total += coste[u];
        std::cout << "[" << pred[u] + 1 << "," << u + 1 << "] : (" << coste[u] << ")\n"; 
        ++contador;
    }
    std::cout << "\n";
    std::cout << "El peso total del MST es: " << coste_total << "\n";
}

void GRAFO::Dijkstra_(double &comparaciones, unsigned s)
{
cout << "Soluciones:" << endl;
vector<bool> PermanentementeEtiquetado;
vector<int> d;
vector<unsigned> pred;
int min;
unsigned candidato;
//Inicialmente no hay ningun nodo permanentemente etiquetado
PermanentementeEtiquetado.resize(n,false);
//Inicialmente todas las etiquetas distancias son infinito
d.resize(n,maxint);
//Inicialmente el pred es null
pred.resize(n,UERROR);
//La etiqueta distancia del nodo origen es 0, y es su propio pred
d[s]=0; pred[s]=s; comparaciones = 0;
do
{
// - Buscamos un nodo candidato a ser permanentemente etiquetado: aquel
// de entre los no permanentemente etiquetados, es decir, en el almacén con
// menor etiqueta distancia no infinita.    
    min = maxint;
    candidato = UERROR;
    for (unsigned i = 0; i < n; ++i) {
        if (!PermanentementeEtiquetado[i] && d[i] < min) {
            min = d[i];
            candidato = i;
        }
    }
    if (candidato == UERROR) {
        break;
    }
    
    PermanentementeEtiquetado[candidato] = true;

    for (unsigned i = 0; i < LS[candidato].size(); ++i) {
        if (d[LS[candidato][i].j] > d[candidato] + LS[candidato][i].c) {
            d[LS[candidato][i].j] = d[candidato] + LS[candidato][i].c;
            pred[LS[candidato][i].j] = candidato;
        }
        comparaciones++;
    }
// - Si existe ese candidato, lo etiquetamos permanentemente y usamos
// los arcos de la lista de sucesores para buscar atajos. Por cada
// comparación realizada para buscar atajos, incrementamos el contador de
// comparaciones.
// - Esto lo hacemos mientras haya candidatos

} while (candidato != maxint);

// En esta parte del código, mostramos los caminos mínimos para cada nodo si
// los hay.
  for (unsigned i = 0; i < n; ++i) {
    if (d[i] != maxint) {
      cout << "El camino mínimo desde " << s+1 << " hasta " << i+1 << " es: ";
      cout << i + 1 << " <- " << pred[i] + 1;
      cout << " y su longitud es " << d[i] << endl;
    }
  }
}

void GRAFO::BellmanFordEnd_(double &comparaciones, unsigned s) 
{
vector<int> d;
vector<unsigned> pred;
unsigned numeromejoras = 0;
bool mejora;
//Idem que en el algoritmo de Dijkstra
d.resize(n,maxint);
pred.resize(n, UERROR);
d[s]=0; pred[s]=s; comparaciones = 0;
do {
// recorremos todos los arcos, y para cada (i, j), buscamos si d[j] > d[i]
// + cij, y actualizamos d y pred, incrementando el contador comparaciones
// cuando comparamos, independientemente de si mejoramos o no.
//si al menos en una ocasion ha mejorado una etiqueta distancia, no hemos
// terminado; contabilizamos los bucles en los que ha habido mejoras    
    mejora = false;
    for (unsigned i=0; i<n; i++) {
        for (unsigned j=0; j<LS[i].size(); j++) {
            if (d[LS[i][j].j] > d[i] + LS[i][j].c) {
                d[LS[i][j].j] = d[i] + LS[i][j].c;
                pred[LS[i][j].j] = i;
                mejora = true;
            }
            comparaciones++;
        }
    }
    numeromejoras++;
} while ((numeromejoras < n) && (mejora == true));
//para salir del bucle, si mejora es true, pues hay un ciclo, pues hemos
// realizado n+1 veces la relajacion con mejora; si mejora es false, pues
// tenemos solucion
//Mostramos los caminos mínimos que se puedan haber encontrado, o
// advertimos de la existencia de un ciclo de coste negativo.
if (mejora == true) {
    std::cout << "Hay un ciclo de coste negativo" << endl;
} else {
    std::cout << "Soluciones:" << std::endl;
    for (unsigned i=0; i < n; i++) {
        if (d[i] != maxint) {
            std::cout << "El camino mínimo desde " << s + 1 << " hasta " << i + 1 << " es: ";
            std::cout << i + 1 << " <- " << pred[i] + 1;
            std::cout << " y su longitud es " << d[i] << std::endl;
        }
    }
}
}

// Compara los algoritmos de Dijkstra y Bellman-Ford
void GRAFO::ComparativaCM() {
  double comparacionesDijkstra, comparacionesBellmanFord;
  int s;
  std::cout << "Introduce el nodo [1, " << n << "]: ";
  std::cin >> s;
  Dijkstra_(comparacionesDijkstra, s - 1);
  std::cout << "Comparaciones Dijkstra: " << comparacionesDijkstra << std::endl;
  BellmanFordEnd_(comparacionesBellmanFord, s - 1);
  std::cout << "Comparaciones Bellman-Ford: " << comparacionesBellmanFord << "\n" << std::endl;
}