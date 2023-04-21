#include <iostream>
#include "Fila.hpp"

Fila::Fila(){
	inicio = 0;
	prox = 0;
}

bool Fila::filavazia(){	
		return prox == inicio && tamanh() == 0;
	}
void Fila::adiciona(int valor){
		if(tamanh() < MAXTAM){
			vet[prox] = valor;
			prox = (prox + 1) % MAXTAM;
			tamanho++;
		} else {
            std::string erro = "pilha cheia";
            throw erro; 
        }

	}
int Fila::remove(){
	if(!filavazia()){
		int aux = vet[inicio];
		tamanho--;
		inicio = (inicio + 1) % MAXTAM;
		return aux;
	}
	}
	
int Fila::tamanh(){
		return tamanho;
	}

void Fila::limpa(){
		inicio = 0;
		prox = 0; 
		tamanho = 0;
 }
 
void Fila::imprimir(){
	for(int i = inicio;  ; i = (i+1)%MAXTAM){
		cout << vet[i] << " ";
		if(prox != 0? i == prox -1 : i == MAXTAM -1) break;
	}
	cout << endl;
}
 
Fila::~Fila(){
	}
