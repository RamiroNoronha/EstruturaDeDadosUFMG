#include "arvore.hpp"
#include <typeinfo>
#include "erro.hpp"
template<typename T> 
class ArvorePosFixa : public ArvoreBinaria<T> {
    public:
    ArvorePosFixa() : ArvoreBinaria<T>(){};
    void Insere(T item) override {
       InserirPosFixaRecursivo(this->raiz, item);  
    };
    void ImprimirPosOrdem(){
        this->PosOrdem(this->raiz);
    }
    std::string TranformarEmInFixa(){
        std::string infixa = "";
        TransformarInfixaRecursivo(this->raiz, infixa);
        return infixa;
    }

    double calcularResultado(){
        Pilha<double> pilhaPosOrdem;
        CalcularValorRecursivo(this->raiz, pilhaPosOrdem);
        return pilhaPosOrdem.desempilha();
    }
    private:
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

    void CalcularValorRecursivo(typename ArvoreBinaria<T>::No* &raiz, Pilha<double> &pilha){
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
    public: 
    bool isOperador(std::string value){
        if(value == "*" || value == "+" || value == "/" || value == "-"){
            return true;
        }
        return false;
    }

};