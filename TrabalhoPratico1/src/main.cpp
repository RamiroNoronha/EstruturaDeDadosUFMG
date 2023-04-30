#include <iostream>
#include "pilha.hpp"
#include "erro.hpp"
#include <string>
#include "arvoreposfixa.hpp"
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

 void criarArvorePosFixa(std::string texto, ArvorePosFixa<std::string> &arvore){
        std::string meuTexto;
    for(auto itr = texto.end()-1; itr != texto.begin() -1; itr--){
        if(*itr != ' '){
            meuTexto+= *itr;
            if(itr != texto.begin()){
                continue;
            }  
        }
        if(meuTexto != " " && meuTexto != ""){
            if(arvore.isOperador(meuTexto)){
                arvore.Insere(meuTexto);
            } else {
                
                std::string textoCorreto = "";
                for(int i = 1; textoCorreto.size() != meuTexto.size(); i ++){
                    textoCorreto+= (*(meuTexto.end() - i));
                }
                arvore.Insere(textoCorreto);
            }
        meuTexto = "";
        }
    }
 }

int main() {
    // Pilha que guardará a expressão em formato infixo
    Pilha<std::string> pilhaInfixa;
    // Pilha que guardará a quantidade de parenteses, para saber se não tem uma quantidade inválida.
    Pilha<int> qtdPrt;
    std::string texto = "1.627783  2.365861  5.771913  *  +  8.718286  3.609486  +  8.733775  *  /  1.229733  6.687142  9.455672  -  +  *  0.138964  8.688749  /  8.668175  4.996990  *  8.772412  +  +  -  9.200303  /  5.066756  8.889858  9.577672  -  +  1.427157  9.378698  *  +  8.158811  4.938767  +  5.053923  *  7.014099  7.524377  +  1.256127  /  +  +  + ";
    ArvorePosFixa<std::string> minhaArvore;
    criarArvorePosFixa(texto, minhaArvore);

    std::string notacao = minhaArvore.TranformarEmInFixa();
    std::cout << notacao << std::endl;
    try{
        double resultado = minhaArvore.calcularResultado();
        std::cout << "valor resultado: " << resultado << std::endl;
    } catch(Erro erro){
        std::cout << erro.getMessage() << std::endl;
    }
}