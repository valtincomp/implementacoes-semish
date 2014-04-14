#ifndef _Fila_H
#define	_Fila_H

#include <stdexcept>
using std::logic_error;
#include<iostream>
#include <stdlib.h>
using namespace std;
template <class T> class Fila {
    private:
    T * fila;
    int length;
    int head, tail;
    public:
        Fila (int n);
	void enfileira (const T& x);
	T desenfileira ();
	bool vazia () const;
        bool cheia () const;
	void imprime ();
        int size();
	~Fila ();
};

template <class T>
Fila<T>::Fila (int n) {
    length = n+1;
    fila = new T[length];
    head = tail = 0;
}

template <class T>
Fila<T>::~Fila() {
    delete [] fila;
}

template <class T>
bool Fila<T>::cheia() const {
    return ((tail+1)%length) == head;
}

template <class T> bool Fila<T>::vazia() const {
    return  head == tail;
}

template <class T>
void Fila<T>::enfileira(const T & n) {
    if (cheia()) cout << "A fila está cheia." << endl;
    else fila[tail] = n; tail = ((tail+1) % length);
}


template <class T> T Fila<T>::desenfileira() {
    if (vazia()) cout << "A pilha está vazia." << endl;
    else {
           T x = fila[head];
           if (head == length) head = 1;
           else head++; return x;
    }
}

template <class T> inline int Fila<T>::size() {
    if (head <= tail) return tail - head;
    else return length - abs(head - tail);
}

template <class T> void Fila<T>::imprime() {
    int inicio = head;
    int fim = tail;
    while (inicio != fim) {
        cout << fila[inicio] << endl;
        inicio = ((inicio+1)%(length));
    }
}


#endif	/* _Fila_H */
