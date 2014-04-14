#ifndef _ARQUIVOS_H
#define	_ARQUIVOS_H
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;

// ------------------------ Ler arquivo ----------------------- //
Graph *  read (Graph * grafo, string nome, int *in) {
    FILE *file;
    file = fopen(nome.c_str(), "r");
    int contador = 0;
    int vertices, arestas;

    fscanf(file, "%d %d\n", &vertices, &arestas);
    cout << "\nvertices " << vertices;
    cout << " arestas " << arestas << endl;
    grafo = new Graph(19523, 45304);
    int a, b;
    while (!feof(file)) {
        fscanf(file, "%d %d\n", &a, &b);
        grafo->insert(a, b, in);
        contador++;
    }
    fclose(file);
    cout << "Arquivo lido com sucesso.\n" << contador << " entradas foram adicionados.\n";
    return grafo;
}

void write (Graph * grafo, string nome) {
    ofstream file;
    file.open(nome.c_str());
    grafo->print(file);
    file.close();
    cout << "Grafo " << nome << " salvo com sucesso.\n";
}


// ------------------------ Salvar links do grafo ------------------------- //

void writeLinks(Graph * grafo, string nome) {
    ofstream file;
    file.open(nome.c_str());
    grafo->printLinks(file);
    file.close();
    cout << "Links " << nome << " salvos com sucesso.\n";
}


#endif	/* _ARQUIVOS_H */

