#include "arvore.hpp"
#include <typeinfo>
#include "erro.hpp"
#pragma once
// Estrutura de dados para armazenar a expressão pós-fixada em formato de arvore
template<typename T>
class ArvorePosFixa : public ArvoreBinaria<T> {
    public:
    ArvorePosFixa() : ArvoreBinaria<T>(){};
    void Insere(T item) override {
       InserirPosFixaRecursivo(this->raiz, item);  
    };
    // Método que chama o PosOrdem da ArvoreBinaria
    void ImprimirPosOrdem(){
        this->PosOrdem(this->raiz);
    }
    // Método que pega a arvore e gerá uma string dela em formato Infixa
    std::string TranformarEmInFixa(){
        std::string infixa = "";
        TransformarInfixaRecursivo(this->raiz, infixa);
        return infixa;
    }
    // Método que calcula o resultado da expressão
    long double calcularResultado(){
        Pilha<long double> pilhaPosOrdem;
        CalcularValorRecursivo(this->raiz, pilhaPosOrdem);
        return pilhaPosOrdem.desempilha();
    }
    // Método que verifica se a árvore é válida
    bool arvoreValida(){
        bool valido = true;
        verificaArvoreValidaRecursivo(this->raiz, valido);
        return valido;
    }
    private:
    // Método que insere os valores na árvore PoxFixa de forma recursiva
    // # Parâmetros
    // - raiz: Nó que será analisado
    // - item: Item que será adicionado a um dos nós
    bool InserirPosFixaRecursivo(typename ArvoreBinaria<T>::No* &raiz, T item){
        if(raiz == nullptr){
            raiz = new typename ArvoreBinaria<T>::No();        
            raiz->putItem(item);
            return true;
        } else {
            bool inseriu = false;
            if(raiz->esq == nullptr || isOperador(raiz->esq->getItem())){
                inseriu = InserirPosFixaRecursivo(raiz->esq, item);
            } 
            if((raiz->dir == nullptr || isOperador(raiz->dir->getItem())) && !inseriu){
                inseriu = InserirPosFixaRecursivo(raiz->dir, item);
            }
            return inseriu;
        }
        return false;
    }
    // Método que cria um texto da expressão guardada na árvore em forma Infixa
    // # Parâmetros
    // - raiz: Nó que será analisado
    // - texto: texto que guardará a expressão
    void TransformarInfixaRecursivo(typename ArvoreBinaria<T>::No* &raiz, std::string &texto){
        if(raiz != nullptr){
            texto+= "( ";
            TransformarInfixaRecursivo(raiz->dir, texto); 
            texto+= " ";
            texto+=raiz->getItem();
            texto+= " ";
            TransformarInfixaRecursivo(raiz->esq, texto);    
            texto += " )";
        }
    }
    // Método que calcular o valor de forma recursiva
    // # Parâmetros
    // - raiz: Nó que será analisado
    // - pilha: pilha que guardará o resultado da expressão
    void CalcularValorRecursivo(typename ArvoreBinaria<T>::No* &raiz, Pilha<long double> &pilha){
        if(raiz != nullptr){
            if(isOperador(raiz->getItem())){
                CalcularValorRecursivo(raiz->esq, pilha);
                CalcularValorRecursivo(raiz->dir, pilha);
                double num1 = pilha.desempilha();
                double num2 = pilha.desempilha();
                if(raiz->getItem() == "*"){
                    pilha.empilha(num1 * num2);
                } else if(raiz->getItem() == "+"){
                    pilha.empilha(num1 + num2);
                } else if(raiz->getItem() == "/"){
                    if(num2 == 0){
                        throw Erro("Erro divisão por zero");
                    }
                    pilha.empilha(num1 / num2);
                } else if(raiz->getItem() == "-"){
                    pilha.empilha(num1 - num2);
                }
            } else { 
                pilha.empilha(std::stod(raiz->getItem()));
            }
        }
    }
    // Método que verifica se a árvore é valida de forma recursiva
    // # Parâmetros
    // - raiz: Nó que será analisado
    // - valido: booleano que vai caminhando pela arvore para verificar se é valido
    void verificaArvoreValidaRecursivo(typename ArvoreBinaria<T>::No* &raiz, bool &valido){
        if(raiz != nullptr){
            if(isOperador(raiz->getItem())){
                if(raiz->esq == nullptr){
                    valido = false;
                    return;
                } else {
                    verificaArvoreValidaRecursivo(raiz->esq, valido);
                }
                if(raiz->dir == nullptr){
                    valido = false;
                    return;
                } else {
                    verificaArvoreValidaRecursivo(raiz->dir, valido);
                }
            } else {
                if(raiz->esq != nullptr || raiz->dir != nullptr){
                    valido = false;
                    return;
                }
            }
        }
    }

    public: 
    bool isOperador(std::string value){
        if(value == "*" || value == "+" || value == "/" || value == "-"){
            return true;
        }
        return false;
    }

};