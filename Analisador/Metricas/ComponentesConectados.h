#ifndef _COMPONENTESCONECTADOS_H
#define	_COMPONENTESCONECTADOS_H

#include "../Listas/Stack.h"
#include <list>

using namespace std;

struct Pair {
    int vertex, edge, begin, componente;

    Pair() {
        vertex = 0;
        edge = 0;
        begin = 0;
        componente = 0;
    }

    Pair(int v, int e, int b, int c) {
        vertex = v;
        edge = e;
        begin = b;
        componente = c;
    }

    bool operator<(Pair a) {
        return vertex < a.vertex;
    }
};

typedef struct {
    int begin;
    int tam;
} CFC;

static int visitado[668187];
static int visitadoG_T[668187];
static int scc[668187];
static CFC tam_scc[668187];


int visita(Graph *graph, int u, int *visitado);
int visitaNaoRecursiva(Graph * graph, int u, int * visitado, int *visitadoG_T, string tipo_grafo);
int visita2(Graph * graph, int u, int *visitado);

void componentesConectados(Graph * grafo, string nome) {

    Graph *g_t = new Graph(grafo->num_vertices, grafo->num_arestas);
    int vetAux[grafo->num_vertices + 1];

    for (int i = 0; i < grafo->num_vertices + 1; i++)
        vetAux[i] = 0;

    //Cria o grafo transposto
    ofstream transposto;
    transposto.open("_Transposto");
    for (int v = 1; v <= grafo->num_vertices; v++) {
        for (int a = 0; a < grafo->degree(v) ; a++) {
            g_t->insert(grafo->Adj(v, a), v, vetAux);
            transposto << grafo->Adj(v, a) << " " << v << endl;
        }
    }
    transposto.close();

    //Inicializa os vetores de vértices visitados e vetor de SCC
    for (int i = 0; i <= grafo->num_vertices; i++) {
            visitado[i] = 0;
            visitadoG_T[i]= 0;
            scc[i] = 0;
            tam_scc[i].tam = 0;
            tam_scc[i].begin = 0;
    }

    int rotulo = 1;

    for (int u = 1; u <= grafo->num_vertices; u++) {
        if (scc[u] == 0) {

            //Realiza as buscas em profundidade
            visita2(g_t, u, visitadoG_T);
            visita2(grafo, u, visitado);

            tam_scc[rotulo].begin = u;

            //Realiza a interseção
            for (int v = 1; v <= grafo->num_vertices; v++) {
                if ((visitado[v] == 1) && (visitadoG_T[v] == 1)) {
                    scc[v] = rotulo;
                    tam_scc[rotulo].tam++;
                }
                visitado[v] = 0;
                visitadoG_T[v] = 0;
            }
            rotulo++;
        }
    }

    /*cout << endl << "Componentes: ";
    for (int i = 1; i <= grafo->num_vertices; i++) {
        cout << scc[i] << " ";
    }
    cout << endl;*/

    /*Salva o SCC e a quantidade de vértices*/
    ofstream tamanho_scc;
    ofstream tamanho_componente;
    tamanho_scc.open("_TamanhoSCC");
    tamanho_componente.open("_TamanhoComponente");
    for (int i = 1; i < rotulo; i++) {
        if (tam_scc[i].tam > 1)
            tamanho_scc << i << " " << tam_scc[i].begin << " "<< tam_scc[i].tam << endl;
        tamanho_componente << i << " " << tam_scc[i].begin << " "<< tam_scc[i].tam << endl;
    }
    tamanho_componente.close();
    tamanho_scc.close();
}

void separaComponentes(Graph * grafo, int inicial) {

    Graph *g_t = new Graph(grafo->num_vertices, grafo->num_arestas);
    int vetAux[grafo->num_vertices + 1];

    for (int i = 0; i < grafo->num_vertices + 1; i++)
        vetAux[i] = 0;

    //Cria o grafo transposto
    ofstream transposto;
    transposto.open("_Transposto");
    for (int v = 1; v <= grafo->num_vertices; v++) {
        for (int a = 0; a < grafo->degree(v) ; a++) {
            g_t->insert(grafo->Adj(v, a), v, vetAux);
            transposto << grafo->Adj(v, a) << " " << v << endl;
        }
    }
    transposto.close();

    //Inicializa os vetores de vértices visitados e vetor de SCC
    for (int i = 0; i <= grafo->num_vertices; i++) {
            visitado[i] = 0;
            visitadoG_T[i]= 0;
    }

    int u = inicial;

    //Realiza as buscas em profundidade
    visita2(g_t, u, visitadoG_T);
    visitaNaoRecursiva(grafo, u, visitado, visitadoG_T, "G");

}

int visita(Graph *graph, int u, int *visitado) {
    visitado[u] = 1;
    for (int i = 0; i < graph->degree(u); i++) {
        int v = graph->Adj(u, i);
        if (visitado[v] == 0) {
            visita(graph, v, visitado);
        }
    }
}

int visita2(Graph * graph, int u, int *visitado) {
    Stack<int> pilha(graph->max_vertice);
    pilha.push(u);

    do {
        u = pilha.pop();
        for (int i = 0; i < graph->degree(u); i++) {
            int v = graph->Adj(u, i);
            if (visitado[v] == 0) {
                visitado[v] = 1;
                pilha.push(v);
            }
        }
    } while (pilha.size() != 0);
}

int visitaNaoRecursiva(Graph * graph, int u, int *visitado, int *visitadoG_T, string tipo_grafo) {
    Stack<int> pilha(graph->max_vertice);
    pilha.push(u);

    char numstr[50];
    string nome_componente;
    sprintf(numstr, "Componentes/_Componente%d", u);
    nome_componente = numstr + tipo_grafo;

    ofstream comp_forte;
    comp_forte.open(nome_componente.c_str());
    do {
        u = pilha.pop();
        for (int i = 0; i < graph->degree(u); i++) {
            int v = graph->Adj(u, i);
            if (visitado[v] == 0) {
                visitado[v] = 1;
                pilha.push(v);
            }
            if (visitadoG_T[v] == 1)
                comp_forte << u << " " << v << endl;
        }
    } while (pilha.size() != 0);
    comp_forte.close();
}

#endif	/* _COMPONENTESCONECTADOS_H */
