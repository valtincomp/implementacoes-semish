#include <iostream>
#include <stdio_ext.h>

#include "Listas/Graph.h"
#include "Metricas/Distancia.h"
#include "Metricas/Grau.h"
#include "Metricas/ComponentesConectados.h"
#include "Arquivos.h"

#define MAX_VERTICES 519918

int menu();
void combo(int);
void analises();
void arquivos();

int main() {

    Graph * grafo;
    int vetGrausIN[MAX_VERTICES];
    int vetGrausOUT[MAX_VERTICES];
    int x;
    for (x = 0; x < MAX_VERTICES; x++)
    {
	vetGrausIN[x] = 0;
	vetGrausOUT[x] = 0;
    }
    while (true) {
        char opcao = menu();
        if (opcao == 0) break;
        else if (opcao == 1) grafo = read(grafo, "Entradas/_ListaArcos_br", vetGrausIN);
        else if (opcao == 2) write(grafo, "_Arestas");
        else if (opcao == 3) writeLinks(grafo, "_Links");
        else if (opcao == 4) graus_in(grafo, "_GrausIN", vetGrausIN);
        else if (opcao == 5) graus_out(grafo, "_GrausOUT", vetGrausOUT);
        else if (opcao == 6) frequencia_grausIN(grafo, "_FrequenciaGrausIN");
        else if (opcao == 7) frequencia_grausOUT(grafo, "_FrequenciaGrausOUT");
        else if (opcao == 8) distancias(grafo, "_Distancias");
        else if (opcao == 9) componentesConectados(grafo, "_Componentes");
        else if (opcao == 10) {
            system("clear");
            int cfc;
            cout << "Digite o índice do primeiro vértice do CFC: ";
            cin >> cfc;
            separaComponentes(grafo, cfc);
        }
        __fpurge(stdin);
        cout << "Pressione uma tecla...\n";
        getchar();
    }
    return 0;
}

// ------------------------ Menu ----------------------- //

int menu() {
    system("clear");
    cout << "|-------------------------------------------|\n"
            << "| 1. Ler grafo                              |\n"
            << "| 2. Gravar no formato vértice: ligações    |\n"
            << "| 3. Gravar no formato links                |\n"
            << "| 4. Graus de entrada                       |\n"
            << "| 5. Graus de saída                         |\n"
            << "| 6. Frequências dos graus de entrada       |\n"
            << "| 7. Frequências dos graus de saída         |\n"
            << "| 8. Distâncias                             |\n"
            << "| 9. Componentes                           |\n"
            << "| 10. Separa Componentes                    |\n"
            << "| 0. Fim                                    |\n"
            << "|-------------------------------------------|\n"
            << ">> ";
    __fpurge(stdin);
    int n;
    cin >> n;
    return n;
}
