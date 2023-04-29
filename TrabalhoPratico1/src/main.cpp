#include <iostream>
#include "pilha.hpp"
#include "erro.hpp"
#include <string>

void lerInfixa(Pilha<std::string>& pilhaInfixa, Pilha<int> parenteses){
    std::string EXP;
    for(auto itr = EXP.begin(); itr != EXP.end(); itr++){
        if(*itr == ' ' || *itr == '\n'){
            continue;
        }
        if(*itr == '('){
            parenteses.empilha(1);
        }
    }
}

int main() {
    // Pilha que guardará a expressão em formato infixo
    Pilha<std::string> pilhaInfixa;
    // Pilha que guardará a expressão em formato posFixo
    Pilha<std::string> pilhaPosFixa;
    // Pilha que guardará a quantidade de parenteses, para saber se não tem uma quantidade inválida.
    Pilha<int> qtdPrt; 


}