
#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::ostream;

/** Implementação do TAD Lista Dinâmica, com métodos para:
 *	- Buscar
 *	- Inserir
 *	- Remover
 *	- Retornar uma chave
 *  - Imprimir a lista
 */

class OutOfBoundsException : std::exception {
};

template <class Type> class Node {
public:
    Type record;
    Node * next;

    Node() {
        next = 0;
    }

    Node(Type rec, Node * n = 0) {
        record = rec;
        next = n;
    }
};

template <class Type> class List {
    typedef Node<Type> No;
    /// Nó raiz
    No * head;
    No * previous;
    int prev;
    /// Número de nós
    int length;

public:

    /** Construtor */
    List() {
        head = new No();
        head->next = head;
        head->record = 10e+5;
        length = 0;
        previous = head;
        prev = 0;
    }

    /** Destrutor */
    ~List() {
        No * node = head->next;
        while (node != head) {
            head->next = head->next->next;
            delete node;
            node = head->next;
        }
    }

    /** Retorna o tamanho da lista */
    inline int size() {
        return length;
    }

    /** Verifica se a lista está vazia */
    bool empty() {
        return head->next == head;
    }

    /** Insere um registro, mantendo a lista ordenada */
    bool insert(Type & key) {
        No * node = head;

        // encontra posição a inserir
        while (node->next->record < key)
            node = node->next;

        if (key == node->next->record)
            return false;
//
//        cout << "Vai inserir\n";
        node->next = new No(key, node->next);
        length++;
//        cout << "novo tamanho; " << length << endl;
        return true;

    }

    /** Remove um registro */
    bool remove(Type & key) {
        No * node = head;
        while (true) {
            // Não encontrou registro
            if (node->next == head) return false;
            // Encontrou
            if (node->next->record == key) {
                No * aux = node->next;
                node->next = aux->next;
                delete aux;
                length--;
                return true;
            }
            node = node->next;
        }
        prev = 0;
        previous = head->next;
    }

    /** Busca um registro */
    Type * search(Type & key) {
        No * node = head->next;

        while (node != head) {
            // Passou o valor e não encontrou registro
            if (node->record > key) return NULL;
            // Encontrou
            if (node->record == key) return &(node->record);
            node = node->next;
        }
        return NULL;
    }

    /** Retorna o i-ésimo elemento da lista */
    Type & elementAt(int i) {
        if (prev == i - 1) {
            prev++;
            previous = previous->next;
            if (previous == head) previous = head->next;
        } else {
            previous = head->next;
            for (prev = 0; prev < i; prev++)
                previous = previous->next;
        }
        return previous->record;
    }

    /** Retorna o i-ésimo elemento da lista */
    Type & at(int i) {
        No * node = head->next;
        for (int a = 0; a < i; a++)
            node = node->next;
        return node->record;
    }

    /** Imprime toda a lista */
    void print(ostream & out) {
        No * node = head->next;
        while (node != head) {
            out << node->record << " ";
            node = node->next;
        }
    }

    /** Limpa uma lista */
    void clear() {
        No * node = head->next;
        while (node != head) {
            head->next = head->next->next;
            delete node;
            length--;
            node = head->next;
        }

    }
};

#endif /*LIST_H_*/


//
//#ifndef LIST_H_
//#define LIST_H_
//
//#include <list>
//#include <iostream>
//using namespace std;
//
//template <class Type> class List {
//    list<int> vetor;
//    list<int>::iterator it, iter;
//    int count;
//
//
//public:
//
//    /** Retorna o tamanho da lista */
//    inline int size() {
//        return vetor.size();
//    }
//
//    /** Verifica se a lista está vazia */
//    bool empty() {
//        return vetor.empty();
//    }
//
//    /** Insere um registro, mantendo a lista ordenada */
//    bool insert(const Type & key) {
//        vetor.push_back(key);
//    }
//
//    void sort() {
//        iter = vetor.begin();
//        count = 0;
//        vetor.sort();
//        vetor.unique();
//    }
//
//    /** Remove um registro */
//    bool remove(const Type & key) {
//        iter = vetor.begin();
//        count = 0;
//        vetor.remove(key);
//    }
//
//    /** Retorna o i-ésimo elemento da lista */
//    inline Type elementAt(int i) {
//        if (count == i - 1) {
//            iter++;
//            count++;
//            return *iter;
//        }
//        else {
//            count = 0;
//            for (iter = vetor.begin(); iter != vetor.end(); iter++) {
//                if (count == i) return *iter;
//                count++;
//            }
//        }
//
//    }
//
//    /** Retorna o i-ésimo elemento da lista */
//    Type at(int i) {
//        int a = 0;
//        for (it = vetor.begin(); it != vetor.end(); it++) {
//            if (a == i) return *it;
//            a++;
//        }
//    }
//
//    /** Imprime toda a lista */
//
//    void print(ostream & out) {
//        for (it = vetor.begin(); it != vetor.end(); it++)
//            cout << *it << endl;
//    }
//
//    Type search(const Type & key) {
//        for (it = vetor.begin(); it != vetor.end(); it++)
//            if (*it == key) return *it;
//    }
//
//};
//
//#endif /*LIST_H_*/
//
