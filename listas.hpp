#ifndef LISTAS_HPP_INCLUDED
#define LISTAS_HPP_INCLUDED

template <typename T> struct Nodo {
	T dato; // valor que contiene el nodo
	Nodo<T>* sig; // puntero al siguiente nodo
};

template <typename T> void push(Nodo<T>* &pila, T valor)
{
	Nodo<T>* nuevo = new Nodo<T>;
	nuevo->dato = valor;
	nuevo->sig = pila;
	pila = nuevo;
}

template <typename T> T pop(Nodo<T>* &pila)
{
	if (pila == nullptr) {
		std::cout << "Error: pop en pila vacia" << std::endl;
		exit(EXIT_FAILURE);
		//modo no recomendado de terminar, en particular si uso objetos
	}
	T valor = pila->dato;
	Nodo<T>* aux_elim = pila;
	pila = pila->sig;
	delete aux_elim;
	return valor;
}

template <typename T> void agregar(Nodo<T>*& cola, T valor)
{
	Nodo<T>* nuevo = new Nodo<T>;
	nuevo->dato = valor;
	nuevo->sig = nullptr;
	if (cola == nullptr) {
		cola = nuevo;
	} else {
		Nodo<T>* aux = cola;
		while (aux->sig != nullptr) //mientras que no sea el último
			aux = aux->sig;  //avanzo al siguiente
		aux->sig = nuevo;
	}
}

template <typename T> void dup (Nodo <T>* &pila) {
    T primero;
    pop (pila);
    push (pila, primero);
    push (pila, primero);
};

template <typename T> void swap (Nodo <T>* &pila) {
	Nodo <T>* cola (nullptr);
		if (pila != nullptr && pila->sig != nullptr) {
			agregar (cola, pop (pila));
			agregar (cola, pop (pila));
			push (pila, cola);
			push (pila, cola);
		}
	}

template <typename T> void rot (Nodo <T>* &pila, int n) {

    Nodo <T>* paux = pila;
    for (int i = 0; paux != nullptr && i < n; i++){
        paux = paux -> sig;
		if (i < n)
        	return;}

    T T1 = pop(pila); 
    T T2 = pop(pila); 
    T T3 = pop(pila); 

    push(pila, T2); 
    push(pila, T1);
    push(pila, T3); 
	
}

#endif // LISTAS_HPP_INCLUDED
