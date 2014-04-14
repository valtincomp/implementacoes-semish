#ifndef _PILHA_H
#define	_PILHA_H

#include<iostream>
using namespace std;

template <class T> class Stack {
private:
    T * stack;
    int length;
    int top;
public:
    Stack(int n);
    void push(const T& x);
    T pop();
    bool empty() const;
    bool full() const;
    void imprime();
    int size();
    ~Stack();
};

template <class T>
Stack<T>::Stack(int n) {
    length = n + 1;
    stack = new T[length];
    top = 0;
}

template <class T>
Stack<T>::~Stack() {
    delete [] stack;
}

template <class T> bool Stack<T>::empty() const {
    return top == 0;
}

template <class T> bool Stack<T>::full() const {
    return top == length;
}

template <class T>
void Stack<T>::push(const T & n) {
    if (full()) return;
    else stack[++top] = n;
}

template <class T> T Stack<T>::pop() {
    if (empty()) cout << "A pilha está vazia." << endl;
    else {
        T x = stack[top--];
        return x;
    }
}

template <class T> inline int Stack<T>::size() {
    return top;
}

template <class T> void Stack<T>::imprime() {
    for (int i = 0; i < top; i++)
        cout << stack[i] << " ";
}


#endif	/* _PILHA_H */

