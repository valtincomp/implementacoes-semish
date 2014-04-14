#ifndef _GRAU_H
#define	_GRAU_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../Listas/Graph.h"
#include <list>
using namespace std;

int max_degreeIN = 100000;
int max_degreeOUT = 100000;
int contador[100000];
ofstream file;
FILE *entrada;

// ------------------------ Graus ------------------------- //

void escreveGrausFile(Graph * grafo, int *vet, string text) {
    string titulo = "testeGraus" + text;
    file.open(titulo.c_str());

    for (int i = 1; i < grafo->max_vertice; i++)
        file << i << " " << vet[i] << endl;

    file.close();
}

void graus_out(Graph * grafo, string nome, int *vetGrausOUT) {

    file.open(nome.c_str());

    for (int i = 1; i <= grafo->num_vertices; i++) {
        int grau = grafo->degree(i);

        if (grau != 0) {
            vetGrausOUT[i] = grau;
        }
        else vetGrausOUT[i] = 0;
        file << i << " " << grau << endl;
    }

    file.close();

    //escreveGrausFile(grafo, vetGrausOUT, "OUT");
    cout << "Graus de saída gravados em arquivo com sucesso.\n";
}

void graus_in(Graph * grafo, string nome, int *vetGrausIN) {
    int grau = 0;
    file.open(nome.c_str());

    ofstream grautotal;
    grautotal.open("_GrauTotal");

    for (int i = 1; i <= grafo->num_vertices; i++) {
	file << i << " " << vetGrausIN[i] << endl;
	if ((vetGrausIN[i] != 0) || (grafo->degree(i) != 0))
    	    grautotal << i << " "<< vetGrausIN[i] << " " << grafo->degree(i) << endl;
    }
    grautotal.close();
    file.close();
    //escreveGrausFile(grafo, vetGrausIN, "IN");
    cout << "Graus de entrada gravados em arquivo com sucesso.\n";
}

// ---------------------- Frequência de graus ----------------------- //

void frequencia_grausOUT(Graph * grafo, string nome) {

    file.open(nome.c_str());

    for (int i = 0; i < max_degreeOUT; i++)
        contador[i] = 0;

    for (int i = 1; i < grafo->max_vertice; i++)
        contador[grafo->degree(i)]++;

    for (int i = 0; i < max_degreeOUT; i++) {
        if (contador[i] != 0)
            file << i << " " << contador[i] << endl;
    }

    file.close();
    cout << "Frequências salvas com sucesso.\n";

}

void frequencia_grausIN(Graph * grafo, string nome) {
    int v, g;

    file.open(nome.c_str());
    entrada = fopen("_GrausIN", "r");

    for (int i = 0; i < max_degreeIN; i++)
        contador[i] = 0;

    while (!feof(entrada)) {
        fscanf(entrada, "%d %d\n", &v, &g);
        contador[g]++;
    }

    for (int i = 0; i < max_degreeIN; i++) {
        if (contador[i] > 0)
            file << i << " " << contador[i] << endl;
    }

    file.close();
    fclose(entrada);
    cout << "Frequências salvas com sucesso.\n";

}

#endif	/* _GRAU_H */

