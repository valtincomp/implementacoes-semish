#ifndef GRAPH_H_
#define GRAPH_H_

#define MAX_ARESTAS /*271031*/ 233942
#define MAX_VERTICES /*40800*/ 668186
#define SIZE 65536
#include <iostream>
#include <fstream>
#include "List.h"
#include <sys/time.h>
using namespace std;

class Graph {
    // Vetor de nós
    List<int> * adj;

public:
    int num_vertices;
    int num_arestas;
    int max_vertice;

    /** Construtores */
    Graph() {
        num_vertices = 0;
        num_arestas = 0;
        max_vertice = MAX_VERTICES;
        adj = new List<int>[max_vertice];
    }

    Graph(int v, int a) {
        num_vertices = v;
        num_arestas = a;
        max_vertice = v + 1;
        adj = new List<int>[max_vertice];
    }

    /** Destrutor */
    ~Graph() {
        delete [] adj;
    }

    /** Retorna o grau de um vértice */
    inline int degree(int n) const {
        return adj[n].size();
    }

    /** Retorna adjacentes de um vértice */
    int Adj(int v, int n) {
        return adj[v].elementAt(n);
    }

    /** Retorna adjacentes de um vértice */
    int AdjAt(int v, int n) {
        return adj[v].at(n);
    }

    /** Insere uma aresta no grafo.
     * Cada vértice é inserido na lista do outro, significando uma conexão não-direcionada.
     */
    void insert(int v1, int v2, int *in) {
        adj[v1].insert(v2);
        //adj[v2].insert(v1);
        in[v2]++;
    }

    /** Exclui adjacentes de um certo vértice */
    void clear(int v) {
        adj[v].clear();
    }

    /** Verifica se existe uma certa conexão. */
    bool search(int v1, int v2) const {
        return adj[v1].search(v2);
    }

    /** Imprime o grafo no formato formato: vértice + conexões */
    void print(ostream & out) const {

        for (int i = 0; i < max_vertice; i++) {
            if (adj[i].size() == 0) continue;
            out << "\nVertice " << i << " - Grau: " << adj[i].size() << " " << endl;
            adj[i].print(out);
        }
    }

    /** Imprime o grafo no formato formato: lista de links */
    void printLinks(ostream & out) const {
        int vert = 0, arest = 0, contador = 0;
        for (int i = 1; i < max_vertice; i++) {
            if (adj[i].size() != 0) vert++; arest +=adj[i].size();
        }
        out << vert << " " << arest/2 << endl;
        ofstream teste;
        teste.open("Arestas/Proporcao", ostream::app);
        teste << vert << " " << arest/2 << endl;
        for (int i = 0; i < max_vertice; i++) {
            if (adj[i].size() == 0) continue;
            for (int a = 0; a < adj[i].size(); a++) {
                out << i << " " << adj[i].elementAt(a) << endl;
                contador++;
            }
        }
        cout << "Contador: " << contador;
    }

    void remove(int v1, int v2) {
        adj[v1].remove(v2);
        adj[v2].remove(v1);
    }

};

class Cronometro {
    timeval a, b;
public:

    void start() {
        gettimeofday(&a, NULL);
    }

    void finish() {
        gettimeofday(&b, NULL);
    }

    double get() {
        return (b.tv_sec - a.tv_sec) + (b.tv_usec - a.tv_usec) / 1000000.0;
    }
};

#endif
