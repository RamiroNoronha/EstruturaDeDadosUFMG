#include <iostream>
#include <random>
#include "Pilha.hpp"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    Pilha pilha;
    for (int i = 0; i < 10; ++i) {
        pilha.empilha(dis(gen));
    }

    pilha.imprimir();

    for(int i = 0; i < 3; i++){
        pilha.empilha(dis(gen));
    }

    pilha.imprimir();

    for(int i = 0; i < 5; i++){
        pilha.desempilha();
    }
    
    pilha.imprimir();

    for(int i =0; i < 5; i++){
        pilha.empilha(dis(gen));
    }
    
    pilha.imprimir();
    std::cout << std::endl;

    return 0;
}
