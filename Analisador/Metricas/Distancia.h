#ifndef DISTANCIA_H_
#define DISTANCIA_H_
#include "../Listas/Queue.h"
#include <iostream>
#include <fstream>
using namespace std;


#define max 30

class Distancias {
private:
    short *d;
    unsigned long int contador[max];
    Graph * grafo;
    static const unsigned char NO, YES;
    void visitaBfs(int u, unsigned char *);

public:
    void buscaEmLargura(const char *);

    /* Construtor */
    Distancias(Graph * graph) {
        grafo = graph;
        d = new short[grafo->max_vertice + 1];
        for (int i = 0; i < max; i++) contador[i] = 0;
    }

    /* Destrutor */
    ~Distancias() {
        grafo = NULL;
        delete [] d;
    }
};

const unsigned char Distancias::NO = 0;
const unsigned char Distancias::YES = 1;

void Distancias::visitaBfs(int u, unsigned char *visitado) {

    // distância de u até ele mesmo = 0
    d[u] = 0;

    // Fila de vértices para visita
    Fila<int> fila(grafo->max_vertice + 2);

    // Guarda vértice atual na fila para visita posterior
    fila.enfileira(u);

    while (!fila.vazia()) {
        u = fila.desenfileira();
        int v = grafo->Adj(u, 0);
        for (int i = 1; i <= grafo->degree(u); i++) {
            if (visitado[v] == NO) {
                visitado[v] = YES;
                fila.enfileira(v);
                d[v] = d[u] + 1;
                contador[d[v]]++;
            }
            v = grafo->Adj(u, i);
        }
    }
}

void Distancias::buscaEmLargura(const char * nome) {

    unsigned char * visitado = new unsigned char[grafo->max_vertice + 1];
    for (int i = 0; i < grafo->max_vertice; i++) {
        visitado[i] = NO;
        d[i] = 9999;
        if (grafo->degree(i) != 0) d[i] = -1;
    }

    Cronometro tempo;
    tempo.start();

    /* Para cada vértice no grafo, encontra a distância dele até todos os vértices */
    for (int u = 1; u < grafo->max_vertice; u++) {
        // somente visita se o grau é diferente de 0
        if (grafo->degree(u) != 0) {
            visitado[u] = YES;
            visitaBfs(u, visitado);

            // Se desejar salvar os não conectados
            ofstream nConect;
            nConect.open("nao-conectados");
            for (int i = 1; i < grafo->max_vertice; i++)
                if (d[i] == -1)
                    nConect << u << " " << i << " " << d[i] << endl;
            nConect.close();

            for (int i = 1; i < grafo->max_vertice; i++) {
                visitado[i] = NO;
            }

        }
    }
    tempo.finish();
    cout << "Tempo gasto para distâncias: " << tempo.get() << endl;
    delete [] visitado;

    ofstream file;
    file.open(nome);
    for (int i = 1; i < max; i++) {
        if (contador[i] != 0) {
            file << i << " " << contador[i] << endl;
        }
    }
}


// ---------------------- Distâncias ----------------------- //

void distancias(Graph * grafo, string nome) {
    Distancias dist(grafo);

    dist.buscaEmLargura(nome.c_str());

    cout << "Distâncias salvas com sucesso.\n";
}


#endif

