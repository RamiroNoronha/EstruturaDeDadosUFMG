#include "Pilha.hpp"

Pilha::Pilha(){
}

bool Pilha::pilhaVazia(){
    return filaPadrao.filavazia();
}

void Pilha::empilha(int valor){
    int aux = 0;
    try{ 
    while(!filaPadrao.filavazia()){
        filaReferencia.adiciona(filaPadrao.remove());
    }
    filaPadrao.adiciona(valor);
    while(!filaReferencia.filavazia()){
        aux = filaReferencia.remove();
        filaPadrao.adiciona(aux);
    }
    filaReferencia.limpa();
    } catch(std::string ex){
        filaPadrao.remove();
        filaPadrao.adiciona(aux);
    }
}

int Pilha::desempilha(){
    return filaPadrao.remove();
}

void Pilha::imprimir(){
    filaPadrao.imprimir();
}
