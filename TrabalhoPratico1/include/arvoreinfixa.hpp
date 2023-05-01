#include "arvore.hpp"
#include <typeinfo>
#include "erro.hpp"
template<typename T> 
class ArvoreInFixa : public ArvoreBinaria<T> {
    public:
    ArvoreInFixa() : ArvoreBinaria<T>(){};
    void Insere(T item) override {
       InserirInFixaRecursivo(this->raiz, item);  
    };
    // Método que chama o PosOrdem da ArvoreBinaria
    void ImprimirPosOrdem(){
        this->PosOrdem(this->raiz);
    }
    // Método que pega a arvore e gerá uma string dela em formato PosFixa
    std::string TranformarEmPosFixa(){
        std::string infixa = "";
        TransformarPosFixaRecursivo(this->raiz, infixa);
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
    // Método que insere os valores na árvore infixa de forma recursiva
    // # Parâmetros
    // - raiz: Nó que será analisado
    // - item: Item que será adicionado a um dos nós
    bool InserirInFixaRecursivo(typename ArvoreBinaria<T>::No* &raiz, T item){
        if(raiz == nullptr){ // Verifica se o nó analisado é nulo, caso seja, inicializa o nó e insere o item nele
            raiz = new typename ArvoreBinaria<T>::No();        
            raiz->putItem(item);
            return true;
        } else { // Caso o nó não seja nulo, irá verificar onde adicionar ele
            bool inseriu = false; // Variável para verificar se o item já foi adicionado ou não
            if(raiz->dir == nullptr || isOperador(raiz->dir->getItem())){ // Tenta inserir na direita, caso seja nulo, ou se a direita dor um operador
                inseriu = InserirInFixaRecursivo(raiz->dir, item);
            } 
            if((raiz->esq == nullptr || isOperador(raiz->esq->getItem())) && !inseriu){ // Caso não tenha inserido ainda, vai tentar inserir a esquerda, caso seja nulo, ou se a esquerdar for um operador
                inseriu = InserirInFixaRecursivo(raiz->esq, item);
            }
            return inseriu; // retorna a resposta se inseriu com sucesso ou não
        }
        return false; // garantir que algo seja retornado
    }
    // Método que cria um texto da expressão guardada na árvore em forma PosFixa
    // # Parâmetros
    // - raiz: Nó que será analisado
    // - texto: texto que guardará a expressão
    void TransformarPosFixaRecursivo(typename ArvoreBinaria<T>::No* &raiz, std::string &texto){
        if(raiz != nullptr){
            TransformarPosFixaRecursivo(raiz->dir, texto);
            TransformarPosFixaRecursivo(raiz->esq, texto);
            texto+=raiz->getItem();
            texto+=" ";
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
            }  else {
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